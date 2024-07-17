# Makefile
.PHONY: all config-info install uninstall pam_mod_build pam_mod_clean clean install_deps

# File where pam module name and built lib path defined 
RULES_MAKE := ./Rules.Make
include $(RULES_MAKE)

# Read configuration from ini file
INI_FILE := mypam-cfg.ini
SERVER_URL := $(shell awk -F '=' '/server_url/ {print $$2}' $(INI_FILE))
REPLACE_LOGINS := $(shell awk -F '=' '/replace_logins/ {print $$2}' $(INI_FILE))

# Split the REPLACE_LOGINS into an array
space := ,
REPLACE_LOGINS_ARRAY := $(subst $(space), ,$(REPLACE_LOGINS))

# Function to check if a value is in a list
define check_value_list
$(if $(filter $(2),$(1)),true,false)
endef

# Possible logins which we can replace.
ALLOWED_LOGINS_TO_REPLACE_ARRAY := login root user gdm

# check login in user config array
CHECK_LOGIN := $(call check_value_list,$(REPLACE_LOGINS_ARRAY),login)
DEF_PATH_TO_LOGIN := /etc/pam.d/login

# check gdm in user config array
CHECK_GDM := $(call check_value_list,$(REPLACE_LOGINS_ARRAY),gdm)
DEF_PATH_TO_GDM := /etc/pam.d/gdm-password


# check root in user config array
CHECK_ROOT := $(call check_value_list,$(REPLACE_LOGINS_ARRAY),root)
# Find and place the root login pam.d file
DEF_PATH_TO_ROOT := ""

# check user in user config array
CHECK_USER := $(call check_value_list,$(REPLACE_LOGINS_ARRAY),user)
# Find and place the user login pam.d file
DEF_PATH_TO_USER := ""

PATH_TO_PLACE_NEW_PAM_MODULE := /lib/x86_64-linux-gnu/security/
TEMP_PATH_TO_LOGIN_FILES := /tmp/pam_modification/
TEMP_PATH = $(TEMP_PATH_TO_LOGIN_FILES)$(NEW_PAM_MODULE_NAME).tmp 

# Define a function to modify the PAM login file
define modify_pam_login_file
	if grep -q "^auth sufficient $(NEW_PAM_MODULE_NAME)$$" $(1); then \
		echo "Error: 'auth sufficient $(NEW_PAM_MODULE_NAME)' already exists in $(1)"; \
		exit 1; \
	fi; \
	echo "Modifying $(1)"; \
	awk 'NR==1 {print "# Adding new Auth scheme refer this link for more details"; print "auth sufficient $(NEW_PAM_MODULE_NAME)"; print $$0; next} 1' $(1) > $(TEMP_PATH); \
	sudo cp $(TEMP_PATH) $(1); \
	echo "Modified $(1) successfully" 
endef


# Default target
all: config-info pam_mod_build help


help:
	@echo "To install this pam module"
	@echo "	1. make install_deps	: to install Dependecies"
	@echo "	2. make 		: to build the pam module"
	@echo "	3. make install		: to install the build module to host pc "
	@echo "\n\nFor changing the server / config"
	@echo "	Please check the mypam-cfg.ini"



# Print configuration information
# TODO : remove the else cases and only print texts if replacing that perticular login
#        also print a warning if we haven't placed any valid login or
#        an invaid login.

config-info:
	@if [ "$(CHECK_LOGIN)" = "true" ]; then \
		echo "Updating login config"; \
	fi

	@if [ "$(CHECK_GDM)" = "true" ]; then \
		echo "Updating gdm login config"; \
	fi

	@if [ "$(CHECK_ROOT)" = "true" ]; then \
		echo "Updating root login config"; \
	fi

	@if [ "$(CHECK_USER)" = "true" ]; then \
		echo "Updating user login config"; \
	fi

	@echo "\n\n"
	@echo "Logins which we can Replace:"
	@for login in $(ALLOWED_LOGINS_TO_REPLACE_ARRAY); do \
		echo "    $$login"; \
	done

install:
	@if [ ! -d $(TEMP_PATH_TO_LOGIN_FILES) ]; then \
		mkdir $(TEMP_PATH_TO_LOGIN_FILES); \
	fi
	@sudo cp $(LIB_DIR)/$(NEW_PAM_MODULE_NAME) $(PATH_TO_PLACE_NEW_PAM_MODULE);
	@if [ "$(CHECK_LOGIN)" = "true" ]; then  \
		$(call modify_pam_login_file,$(DEF_PATH_TO_LOGIN)); \
		echo "login auth file updated"; \
	fi
	@if [ "$(CHECK_GDM)" = "true" ]; then  \
		$(call modify_pam_login_file,$(DEF_PATH_TO_GDM)); \
		echo "gdm auth file updated"; \
	fi
	@if [ "$(CHECK_ROOT)" = "true" ]; then  \
		$(call modify_pam_login_file,$(DEF_PATH_TO_ROOT)); \
		echo "root auth file updated"; \
	fi
	@if [ "$(CHECK_USER)" = "true" ]; then  \
		$(call modify_pam_login_file,$(DEF_PATH_TO_USER)); \
		echo "user auth file updated"; \
	fi
	@if [ -d $(PAM_FILE) ]; then \
		rm -rf $(TEMP_PATH_TO_LOGIN_FILES); \
	fi

uninstall:
	@sudo rm $(PATH_TO_PLACE_NEW_PAM_MODULE)$(NEW_PAM_MODULE_NAME)
#TODO : Remove the lines added to the respoective pam modules.

pam_mod_build:
	@$(MAKE) -C src all --no-print-directory

pam_mod_clean:
	@$(MAKE) -C src clean --no-print-directory

# Clean temporary files
clean:
	@rm -f config-info

# Install Dependecies for building and 
#                running the pam module
install_deps:
	sudo apt install \
	   make \
	   git \
	   build-essential \
	   libpam0g-dev \
	   curl jq;