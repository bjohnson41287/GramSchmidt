#!/bin/bash
################################################################################
# File: GramSchmidt.sh
#
# Author: $Format:%an$
#
# Date: $Format:%cD$
# Date Created: Monday September 29, 2014
#
# Description: Bash script used to compile the GramSchmidt program
################################################################################

#
# Variable definitions
#
configOutLog=configure_stdout.log
buildOutLog=build_stdout.log

configErrLog=configure_stderr.log
buildErrLog=build_stderr.log

#
# Manual pages for usage instructions
#
build_man ()
{
    echo ""
    echo -e "\033[1mSYNOPSIS\033[0m"
    echo -e "\tGramSchmidt.sh [OPTIONS] [TAG]"
    echo ""
    echo -e "\tconfigure"
    echo -en "\t    Prepare the project directories for compilation of the "
    echo "project source code."
    echo ""
    echo -e "\tbuild"
    echo -e "\t    Configure and compile the project source code."
    echo ""
    echo -e "\tdistclean"
    echo -en "\t    Delete all files and directories created by the "
    echo -e "\033[4mconfigure\033[0m and \033[4mbuild\033[0m steps."
    echo ""
    echo -e "\trelease"
    echo -en "\t    Create a release tarball of the commit pointed to by "
    echo -en "\033[4mTAG\033[0m. \033[4mTAG\033[0m must be the name of an "
    echo "annotated tag. If a lightweight tag is given,"
    echo -en "\t    an error will be generated saying the SHA-1 of the tag and "
    echo -en "commit are the same. If \033[4mTAG\033[0m is not specified, then "
    echo "the most current"
    echo -en "\t    annotated tag is found in the local repository and the "
    echo -n "user is prompted for whether or not they would like to create a "
    echo "release"
    echo -e "\t    tarball for this tag version."
    echo ""
    echo -en "\t    A remote repository must also exist and will be searched "
    echo -en "for the same \033[4mTAG\033[0m value. If a remote is not found "
    echo "or the specified"
    echo -en "\t    tag is not found in the remote repository, then the "
    echo -n "release process will generate an error and the tarball will not "
    echo "be created."
    echo ""
}

#
# Ensure the correct number of input arguments were given
#
checkInputs ()
{
    if [ ${noOfArgs} -gt $2 ]; then
        echo "Incorrect number of arguments for '$1'"
        echo "Run this script without any inputs for appropriate use."
        exit 1
    fi
}

#
# Ensure the environment variables are set
#
checkProjEnv ()
{
    if [ -z "${PROJ_ROOT_PATH}" ] ||
       [ -z "${STD_MAKE_PATH}" ]; then
        echo "Environment is not yet set"
        echo "Source the setenv.sh script to set the environment"
        exit 1
    fi
}

#
# Check the number of input arguments
#
noOfArgs=$#
if [ $# -eq 0 ]; then
    build_man
    exit 1
fi

#
# Configure the source code for compilation
#
if [ "$1" = "configure" ]; then
    #
    # Ensure the inputs are correct and the environment variables are set
    #
    checkInputs $1 1
    checkProjEnv

    #
    # Create the build logs directory if it does not exist and configure the
    # project
    #
    if [ ! -d ${BUILD_LOG_PATH} ]; then
        mkdir ${BUILD_LOG_PATH}
    fi

    echo "Configuring GramSchmidt"
    (make -C ${PROJ_ROOT_PATH} configure > ${BUILD_LOG_PATH}/${configOutLog}) \
        |& tee ${BUILD_LOG_PATH}/${configErrLog}

#
# Build the project
#
elif [ "$1" = "build" ]; then
    #
    # Ensure the inputs are correct and the environment variables are set
    #
    checkInputs $1 1
    checkProjEnv

    #
    # Create the build logs directory if it does not exist
    #
    if [ ! -d ${BUILD_LOG_PATH} ]; then
        mkdir ${BUILD_LOG_PATH}
    fi

    #
    # Configure and compile the project. This ensures everything is up to date
    # for make.
    #
    echo "Configuring GramSchmidt"
    (make -C ${PROJ_ROOT_PATH} configure > ${BUILD_LOG_PATH}/${configOutLog}) \
        |& tee ${BUILD_LOG_PATH}/${configErrLog}

    echo "Building GramSchmidt"
    (make -C ${PROJ_ROOT_PATH} all > ${BUILD_LOG_PATH}/${buildOutLog}) \
        |& tee ${BUILD_LOG_PATH}/${buildErrLog}

#
# Delete all files created by the configure and/or build steps
#
elif [ "$1" = "distclean" ]; then
    #
    # Ensure the inputs are correct and the environment variables are set
    #
    checkInputs $1 1
    checkProjEnv

    #
    # Remove directories created by this script and have 'make' remove
    # everthing created by the 'configure' and 'all' targets in the Makefiles.
    #
    rm -rf ${BUILD_LOG_PATH}
    rm -rf ${DOC_PATH}
    rm -rf ${RELEASE_PATH}

    make -C ${PROJ_ROOT_PATH} distclean

#
# Generate a release tarball of the commit snapshot pointed to by the specified
# annotated tag name
#
elif [ "$1" = "release" ]; then
    #
    # Ensure the inputs are correct and the environment variables are set
    #
    checkInputs $1 2
    checkProjEnv

    #
    # Check the tag name argument to ensure it is a valid annotated tag name
    #
    if [ ! -d ${PROJ_ROOT_PATH}/.git ]; then
        echo "ERROR"
        echo "${PROJ_ROOT_PATH}/.git directory not found."
        echo "Use the 'tar' command instead to generate an archive."
        exit 1
    fi

    if [ -z "$2" ]; then
        echo -e "Tag name not specified."
        tagName=`git describe --abbrev=0`
        echo -n "Use the most current annotated tag ${tagName}? (y/n): "
        read useTagAns

        case "${useTagAns}" in
            y | yes)
                ;;
            n | no)
                echo -e "Aborting release"
                exit 1
                ;;
            *)
                echo -e "ERROR: Unknown input \"${useTagAns}\""
                echo "Aborting release"
                exit 1
                ;;
        esac

    else
        tagName="$2"
    fi

    if [ -z ${tagName} ]; then
        echo "ERROR: No annotated tags found in the local project. You must"
        echo "       create one and push it to the remote repository before a"
        echo "       release tarball can be created."
    fi

    #
    # Grab the unique remote URLs to the current repository and ask the user
    # which remote should be selected. If only one remote is found, do not
    # prompt the user.
    #
    remoteURL=(`git remote | git ls-remote --get-url`)
    if [ ${#remoteURL[@]} -eq 0 ]; then
        echo "ERROR: No remote repository found. A remote repository must exist"
        echo "to validate release versions."
        exit 1

    elif [ ${#remoteURL[@]} -gt 1 ]; then
        echo -e "\nRemote Repositories"
        echo "-------------------"

        for ((i=0; i<${#remoteURL[@]}; i++)); do
            echo -e "$(($i+1)))\t${remoteURL[$i]}"
        done

        echo -en "\nRepository to read annotated tags: "
        read URLnum

        #
        # Check for a valid input. Bash complains if the input is not an
        # integer, since it expects it in the comparison below.
        #
        if [[ ! ${URLnum} =~ ^[0-9]+$ ]] || \
           [ ${URLnum} -lt 1 ] || \
           [ ${URLnum} -gt ${#remoteURL[@]} ]; then
            echo "ERROR: Input ${URLnum} is not a valid option"
            exit 1
        else
            repoURL=${remoteURL[$((${URLnum}-1))]}
        fi
    else
        repoURL=${remoteURL[0]}
    fi

    #
    # Check the local repository for the same tag and commit hash values
    # as the remote repository
    #
    localTagHash=`git show-ref --tags ${tagName} | awk '{print $1}'`
    if [ -z ${localTagHash} ]; then
        echo "ERROR: Tag ${tagName} does not exist in the local repository."
        exit 1
    fi

    echo -e "Accessing annotated tags from repository: ${repoURL}\n"

    tagRegExp="${tagName}$|${tagName}\^\{\}$"
    rmtTagRefs=(`git ls-remote --tags ${repoURL} | \
                 grep -E "${tagRegExp}" | awk '{print $1}'`)
    rmtTagHash=${rmtTagRefs[0]}
    rmtCmtHash=${rmtTagRefs[1]}

    if [ "${rmtTagHash}" = "${rmtCmtHash}" ]; then
        echo "ERROR: Specified tag ${tagName} is not an annotated tag in the"
        echo "       remote repository."
        exit 1
    fi

    if [ "${localTagHash}" != "${rmtTagHash}" ]; then
        echo "ERROR: Local tag ${tagName} SHA-1 hash does not match the"
        echo "       repository tag ${tagName} SHA-1 hash. Either update the"
        echo "       remote or local repository or specify another tag."
        exit 1
    fi

    localCmtHash=`git log --format=%H -1 ${localTagHash}`

    if [ "${localTagHash}" = "${localCmtHash}" ]; then
        echo "ERROR: Specified tag ${tagName} is not an annotated tag in the"
        echo "       local repository."
        exit 1
    fi

    if [ "${rmtCmtHash}" != "${localCmtHash}" ]; then
        echo "ERROR: Specified tag ${tagName} points to different commit"
        echo "       snapshots in remote and local repositories. Either update"
        echo "       the remote or local repository or specify another tag."
        exit 1
    fi

    #
    # Create the release tarball
    #
    tagDir=`echo ${tagName} | sed "s|\.|_|g"`
    relDir="${RELEASE_PATH}/${tagDir}"
    currDir=`pwd`
    archPrefix="`basename ${PROJ_ROOT_PATH}`/"
    archName="`basename ${PROJ_ROOT_PATH}`_${tagDir}.tar.gz"

    if [ ! -d ${relDir} ]; then
        mkdir -p ${relDir}
    fi

    cd ${PROJ_ROOT_PATH}
    git archive ${localTagHash} --prefix="${archPrefix}" ${PROJ_ROOT_PATH} | \
        gzip > "${relDir}/${archName}"
    cd ${currDir}

    echo "Generated release tarball:"
    echo "${relDir}/${archName}"

else
    #
    # An invalid argument has been input. Print the manual pages and exit.
    #
    echo "Invalid argument: $1"
    echo "Run this script without any inputs for appropriate use."
    exit 1
fi

# End GramSchmidt.sh
