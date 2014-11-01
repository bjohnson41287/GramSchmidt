################################################################################
# File: Makefile
#
# Author: Benjamin Johnson
#
# Date Created: Saturday October 25, 2014
# Date Revised: Monday October 27, 2014
#
# Description: Library source directory Makefile to compile source code into,
#              and generate an archive of, the library object files
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
LOCAL_LIB_DIR    := $(abspath ../lib)

#
# Library name
#
LIB_NAME := libutlmath.a

#
# Library suffix, definition, and target path
#
LIB_SUFFIX := $(suffix $(LIB_NAME))
LIB_BASE   := $(basename $(LIB_NAME))
LIB_NAME_PATH := $(LOCAL_LIB_DIR)/$(LIB_NAME)

#
# Ensure the default target is "all"
#
default: all

include $(PROJ_ROOT_PATH)/$(STD_MAKE_PATH)/Makefile.libs

#
# Local targets
#
.PHONY: local_all local_configure

local_all: $(DEST_LIB_PATH) $(LIB_NAME_PATH)

local_configure: $(DEST_HEADER_PATH) $(LIB_TGTS_PATH)

# End Makefile
