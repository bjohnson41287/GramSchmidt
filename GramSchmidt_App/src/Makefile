################################################################################
# File: Makefile
#
# Author: Benjamin Johnson
#
# Version: 1.0
#
# Date Created: Monday September 29, 2014
# Date Revised: N/A
#
# Description: GramSchmidt source directory Makefile to compile the GramSchmidt
#              application
################################################################################

#
# Standard definitions for Makefiles
#
include ${PROJ_ROOT_PATH}/${STD_MAKE_PATH}/defs.std

#
# List of local files and directories
#
LOCAL_HEADER_DIR := $(abspath ../header)
LOCAL_OBJ_DIR    := $(abspath ../obj)

HEADERS  := $(call headerFiles,$(LOCAL_HEADER_DIR))
CCSOURCE := $(strip $(wildcard *.cc))
OBJS := $(addprefix $(LOCAL_OBJ_DIR)/,$(call objNames,$(CCSOURCE)))

#
# Application name
#
APP_NAME := GramSchmidt

#
# Ensure the default target is "all"
#
default: all

include $(PROJ_ROOT_PATH)/$(STD_MAKE_PATH)/Makefile.app

#
# THE PREREQUISITES AND RECIPE WILL CHANGE LATER AS LIBRARIES ARE INCLUDED!!!!
#
$(DEST_EXEC_PATH)/$(APP_NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@





# End Makefile
