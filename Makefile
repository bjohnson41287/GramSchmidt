################################################################################
# File: Makefile
#
# Author: $Format:%an$
#
# Date Created: Monday September 29, 2014
# Date Revised: $Format:%cD$
#
# Description: A general Makefile that allows make to descend into the
#              directories from the current directory and continue execution if
#              another Makefile is found.
################################################################################

#
# Standard definitions
#
include ${PROJ_ROOT_PATH}/${STD_MAKE_PATH}/defs.std

#
# Recursively descend the directory structure
#
include ${PROJ_ROOT_PATH}/${STD_MAKE_PATH}/Makefile.std

# End Makefile
