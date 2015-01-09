################################################################################
# File: Makefile.app
#
# Author: $Format:%an$
#
# Date: $Format:%cD$
# Date Created: Monday September 29, 2014
#
# Description: Generic Makefile for application code
################################################################################

#
# Define "make" system variables
#
# See the GNU Make Manual for a full description of these variables
#
MAKEFLAGS += -r

#
# Local source, header, and object file names
#
CCSOURCE := $(strip $(wildcard *.cc))
HEADERS  := $(call headerFiles,$(LOCAL_HEADER_DIR))
OBJS := $(addprefix $(LOCAL_OBJ_DIR)/,$(call objNames,$(CCSOURCE)))

#
# Application targets
#
.PHONY: all configure clobber clean distclean

all: $(DEST_EXEC_PATH)
ifneq ($(OBJS),)
	@if [ ! -d $(LOCAL_OBJ_DIR) ]; then \
		$(MKDIR) $(LOCAL_OBJ_DIR); \
	fi
	@$(MAKE) $(DEST_EXEC_PATH)/$(APP_NAME)
endif

configure: $(DEST_HEADER_PATH)
ifneq ($(HEADERS),)
	@for file in $(HEADERS); do \
		$(LN) $(LOCAL_HEADER_DIR)/$$file $(DEST_HEADER_PATH)/$$file; \
	done
endif

clobber:
	@if [ -d $(LOCAL_OBJ_DIR) ]; then \
		$(RM) $(LOCAL_OBJ_DIR); \
	fi

clean: clobber
	@if [ -d $(DEST_EXEC_PATH) ]; then \
		$(RM) $(DEST_EXEC_PATH)/$(APP_NAME); \
		if [ `$(LS) -1 $(DEST_EXEC_PATH) | wc -w` -eq 0 ]; then \
			$(RM) $(DEST_EXEC_PATH); \
		fi \
	fi

distclean: clean
	@if [ -d $(DEST_HEADER_PATH) ]; then \
		for file in $(HEADERS); do \
			$(RM) $(DEST_HEADER_PATH)/$(notdir $$file); \
		done; \
		if [ `$(LS) -1 $(DEST_HEADER_PATH) | wc -w` -eq 0 ]; then \
			$(RM) $(DEST_HEADER_PATH); \
		fi \
	fi

#
# Generic Makefile targets
#
include $(PROJ_ROOT_PATH)/$(STD_MAKE_PATH)/targets.std

#
# Library targets
#
-include $(LIB_TGTS_FILE)

# End Makefile.app
