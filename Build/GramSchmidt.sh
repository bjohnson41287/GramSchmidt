#!/bin/bash
################################################################################
# File: GramSchmidt.sh
#
# Author: Benjamin Johnson
#
# Date Created: Monday September 29, 2014
# Date Revised: Saturday October 25, 2014
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
    echo "Valid Input Arguments:"
    echo "    setenv    - Set needed environment variables"
    echo "    configure - Prepare the project directories for compilation"
    echo "    build     - Configure and compile the project"
    echo "    distclean - Delete all files created by the configure and/or"
    echo "                build steps"
    echo ""
}

#
# Check to ensure the environment variables are set
#
checkProjEnv ()
{
    projEnvSet=true
    if [ -z "${PROJ_ROOT_PATH}" ] ||
       [ -z "${STD_MAKE_PATH}" ]; then
        echo "Environment is not yet set"
        echo "Use the 'setenv' argument to set the environment"
        projEnvSet=false
    fi
}

#
# Check the number of input arguments
#
if [ $# -ne 1 ]; then
    echo "Invalid number of arguments"
    return 1
fi

#
# Set the necessary environment variables
#
if [ "$1" = "setenv" ]; then
    echo "Setting environment"

    #
    # Set PROJ_ROOT_PATH as the project root directory and STD_MAKE_PATH
    # as the directory where the standard files used by "make" reside
    #
    export PROJ_ROOT_PATH=$(cd `dirname ${BASH_SOURCE[0]}`/.. && pwd)
    export STD_MAKE_PATH=Build/StdMake

    #
    # Link the repository git hooks to the .git/hooks directory
    #
    echo -en "\n  Linking git hooks to the .git/hooks directory\n"
    ${PROJ_ROOT_PATH}/Tools/Scripts/LinkGitHooks.sh

    #
    # Let the user know what PROJ_ROOT_PATH is defined as
    #
    echo "  PROJ_ROOT_PATH: ${PROJ_ROOT_PATH}"

#
# Configure the source code for compilation
#
elif [ "$1" = "configure" ]; then
    #
    # Ensure the environment variables are set
    #
    checkProjEnv
    if [ ${projEnvSet} = false ]; then
        return 1
    fi

    echo "Configuring GramSchmidt..."
    make -C ${PROJ_ROOT_PATH} configure

#
# Build the project
#
elif [ "$1" = "build" ]; then
    #
    # Ensure the environment variables are set
    #
    checkProjEnv
    if [ ${projEnvSet} = false ]; then
        return 1
    fi
    
    #
    # Configure and build the project. This ensures everything is up to date for
    # make.
    #
    echo "Configuring GramSchmidt..."
    make -C ${PROJ_ROOT_PATH} configure

    echo "Building GramSchmidt..."
    make -C ${PROJ_ROOT_PATH} all

#
# Delete all files created by the configure and/or build steps
#
elif [ "$1" = "distclean" ]; then
    #
    # Ensure the environment variables are set
    #
    checkProjEnv
    if [ ${projEnvSet} = false ]; then
        return 1
    fi

    make -C ${PROJ_ROOT_PATH} distclean

else
    #
    # An invalid argument has been input. Print the manual pages and exit.
    #
    echo "Invalid argument: $1"
    build_man
    return 1
fi














# End GramSchmidt.sh
