#!/bin/bash
################################################################################
# File: LinkGitHooks.sh
#
# Author: Benjamin Johnson
#
# Version: 1
#
# Date Created: Monday, October 13, 2014
# Date Revised: N/A
#
# Description: Link the repository git hooks to the .git/hooks directory for
#              continued use.
################################################################################

#
# Grab all of the hooks in the hooks directory
#
if [ -d ${PROJ_ROOT_PATH}/hooks ]; then
    gitHooks=(`ls -1 ${PROJ_ROOT_PATH}/hooks | grep -Ev "^.*~$" | sort -u`)
else
    echo -en "\033[1mWARNING\033[0m\n"
    echo "${PROJ_ROOT_PATH}/hooks directory does not exist."
    echo "Repository git hooks will not be used."
    exit 1
fi

#
# Link each hook to the .git/hooks directory
#
if [ ${#gitHooks[@]} -ne 0 ]; then
    for file in ${gitHooks[@]}; do
        ln -sf ${PROJ_ROOT_PATH}/hooks/${file} \
               ${PROJ_ROOT_PATH}/.git/hooks/${file}
    done
else
    echo -en "\033[1mWARNING\033[0m\n"
    echo "There are no hooks in ${PROJ_ROOT_PATH}/hooks."
    echo "No git hooks will be used."
    exit 1
fi

# End LinkGitHooks.sh
