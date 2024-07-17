#Name of the pam module creating
NEW_PAM_MODULE_NAME := Mypam.so

#To get the git repo home directory for releative paths
REPO_ROOT_DIR=$(shell git rev-parse --show-toplevel)

#Path to the Lib directory.
LIB_DIR = $(REPO_ROOT_DIR)/custom_pam_mod/lib