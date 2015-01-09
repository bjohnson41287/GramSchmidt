#!/bin/bash
################################################################################
# File: setenv.sh
#
# Author: $Format:%an$
#
# Date: $Format:%cD$
# Date Created: Sunday December 21, 2014
#
# Description: Sourced bash script for setting project environment variables and
#              linking git hooks to the .git/hooks directory
################################################################################

echo "Setting environment"

#
# Set PROJ_ROOT_PATH as the project root directory and STD_MAKE_PATH as the
# directory where the standard files used by 'make' reside. Also set other
# needed environment variables.
#
export PROJ_ROOT_PATH=$(cd `dirname ${BASH_SOURCE[0]}`/.. && pwd)
export STD_MAKE_PATH=Build/StdMake

export BUILD_LOG_PATH=${PROJ_ROOT_PATH}/Build/Logs
export DOC_PATH=${PROJ_ROOT_PATH}/doc
export RELEASE_PATH=${PROJ_ROOT_PATH}/release

#
# Link the repository git hooks to the .git/hooks directory, if it exists
#
if [ -d ${PROJ_ROOT_PATH}/.git ]; then
    echo -en "\n  Linking git hooks to the .git/hooks directory\n"
    ${PROJ_ROOT_PATH}/Tools/Scripts/LinkGitHooks.sh
fi

#
# Let the user know what PROJ_ROOT_PATH is defined as
#
echo "  PROJ_ROOT_PATH: ${PROJ_ROOT_PATH}"

# End setenv.sh
