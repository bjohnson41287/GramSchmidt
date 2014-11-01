################################################################################
# File: Makefile
#
# Author: Benjamin Johnson
#
# Date Created: Saturday October 25, 2014
# Date Revised: Monday October 27, 2014
#
# Description: Makefile to link header files to the top level header directory
################################################################################

#
# Standard definitions for Makefiles
#
include $(PROJ_ROOT_PATH)/$(STD_MAKE_PATH)/defs.std

#
# List of local directories
#
LOCAL_HEADER_DIR := $(abspath ../header)
LOCAL_OBJ_DIR    := $(abspath ../obj)

#
# Ensure the default target is "all"
#
default: all

include $(PROJ_ROOT_PATH)/$(STD_MAKE_PATH)/Makefile.libs

#
# Local targets
#
.PHONY: local_all local_configure

local_all: ;

local_configure: $(DEST_HEADER_PATH)

# End Makefile
