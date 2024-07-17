#including Parent Makefile
.PHONY: clean all $(NEW_PAM_MODULE_NAME)

#For use in Child makefile
CC = gcc
CFLAGS = -fPIC -Wall
LDFLAGS = -shared -lpam

# For using the common folders or names
RULES_MAKE := ../Rules.Make
include $(RULES_MAKE)

#main target
all: $(NEW_PAM_MODULE_NAME)
	@echo "Completed Build Procedure .."

#Creating the lib
$(NEW_PAM_MODULE_NAME): mypam.c
	@echo "Doing build $@"
	@$(CC) $(CFLAGS) -o $(LIB_DIR)/$@ $^ $(LDFLAGS)

#removing the lib created in the repo
clean:
	@rm -f $(LIB_DIR)/$(NEW_PAM_MODULE_NAME)

