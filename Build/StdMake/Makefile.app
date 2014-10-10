################################################################################
# File: Makefile.app
#
# Author: Benjamin Johnson
#
# Version: 1.0
#
# Date Created: Monday September 29, 2014
# Date Revised: N/A
#
# Description: Generic Makefile for application code
################################################################################

#
# Define the MAKEFLAGS variable
#
# See the GNU Make Manual for a full description of these flags
#
MAKEFLAGS += -r --no-print-directory

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
		if [ -z `$(LS) $(DEST_EXEC_PATH)` ]; then \
			$(RM) $(DEST_EXEC_PATH); \
		fi \
	fi

distclean: clean
	@if [ -d $(DEST_HEADER_PATH) ]; then \
		for file in $(HEADERS); do \
			$(RM) $(DEST_HEADER_PATH)/$(notdir $$file); \
		done; \
		if [ -z `$(LS) $(DEST_HEADER_PATH)` ]; then \
			$(RM) $(DEST_HEADER_PATH); \
		fi \
	fi




#
# Generic Makefile targets
#
include $(PROJ_ROOT_PATH)/$(STD_MAKE_PATH)/targets.std


# End Makefile.app
