#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <security/pam_appl.h>
#include <security/pam_modules.h>
#include <security/pam_ext.h>

PAM_EXTERN int pam_sm_authenticate(pam_handle_t *pamh, int flags, int argc, const char **argv) {
    const char *username;
    char *password;
    int retval;

    // Get the username provided by the user
    retval = pam_get_user(pamh, &username, "Username : ");
    if (retval != PAM_SUCCESS) {
        return retval;
    }
 
    // Prompt the user for a password (without echoing)
    retval = pam_prompt(pamh, PAM_PROMPT_ECHO_OFF, &password, "Enter Password: ");
    if (retval != PAM_SUCCESS) {
        return retval;
    }
    //For getting the userid
    FILE *fp;
    char id_buff[50];
    char curl_req[500];

    snprintf(curl_req, sizeof(curl_req), "curl -H 'Content-Type: application/json' -X POST \"http://34.123.183.187:8000/verify\" -d '{\"pass\":\"%s\"}' | jq -r '.user'", password);
    fp = popen(curl_req, "r");

    if(fp == NULL) {
	printf("fp is NULL");
	return PAM_AUTH_ERR;
    }

    memset(id_buff, 0, sizeof(id_buff));
    while(fgets(id_buff, sizeof(id_buff)-1, fp) != NULL);
    pclose(fp);

    // Removing the newline.
    id_buff[strlen(id_buff)-1] = '\0';

    if(strcmp(username, id_buff) != 0) {
	return PAM_AUTH_ERR;
    }

    /*Setting the user id for user login*/
    pam_set_item(pamh, PAM_USER, id_buff);
    return PAM_SUCCESS; // Authentication successful
}

PAM_EXTERN int pam_sm_setcred(pam_handle_t *pamh, int flags, int argc, const char **argv) {
    return PAM_SUCCESS; // No special handling for credential setup
}

PAM_EXTERN int pam_sm_acct_mgmt(pam_handle_t *pamh, int flags, int argc, const char **argv) {
    return PAM_SUCCESS; // Account management success
}

PAM_EXTERN int pam_sm_open_session(pam_handle_t *pamh, int flags, int argc, const char **argv) {
    return PAM_SUCCESS; // Session opened successfully
}

PAM_EXTERN int pam_sm_close_session(pam_handle_t *pamh, int flags, int argc, const char **argv) {
    return PAM_SUCCESS; // Session closed successfully
}

PAM_EXTERN int pam_sm_chauthtok(pam_handle_t *pamh, int flags, int argc, const char **argv) {
    return PAM_SUCCESS; // Authentication token (password) changed successfully
}
