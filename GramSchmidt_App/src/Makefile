################################################################################
# File: Makefile
#
# Author: $Format:%an$
#
# Date: $Format:%cD$
# Date Created: Monday September 29, 2014
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

#
# Application name
#
APP_NAME := GramSchmidt

#
# Libraries the application depends on
#
DEP_LIBS := libutlmath

#
# Ensure the default target is "all"
#
default: all

include $(PROJ_ROOT_PATH)/$(STD_MAKE_PATH)/Makefile.app

#
# Target to compile the GramSchmidt execuatable
#
$(DEST_EXEC_PATH)/$(APP_NAME): $(OBJS) $(DEP_LIBS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) \
	$(patsubst %,-L%,$(INC_LIB_DIRS)) $(patsubst lib%,-l%,$(DEP_LIBS))

#
# Local targets
#
.PHONY: local_all local_configure

local_all: $(DEST_EXEC_PATH) $(DEST_EXEC_PATH)/$(APP_NAME)

local_configure: $(DEST_HEADER_PATH)

# End Makefile
