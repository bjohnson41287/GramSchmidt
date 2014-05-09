################################################################################
# File: Makefile
#
# Author: Benjamin Johnson
#
# Version: 1.0
#
# Date Created: Sunday March 23, 2014
# Date Revised: N/A
#
# Description: A general Makefile that allows make to descend into the
#              directories from the current directory and continue execution if
#              another Makefile is found.
################################################################################

# Standard definitions
include ${PROG_ROOT_PATH}/Build/StdMake/MakeDefs.std

# Recursively descend the directory structure
include ${PROG_ROOT_PATH}/Build/StdMake/MakeDescend.std

# End Makefile -> More comments
