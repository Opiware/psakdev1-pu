/* Copyright Statement:
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// HTTPD
#include "os_port.h"
#include "axhttp.h"
#include "auth_check.h"

struct userinfo_t userinfo[USER_NUM_MAX];

static void send_authenticate(struct connstruct *cn, char* realm );

void user_config(int lan_updated, int wan_updated)
{
	int i;
	char username[50], passwd[50];

    HTTPD_DEBUGF((httpd, "[HTTPD] user_config() - lan_updated = %d, wan_updated = %d \n", lan_updated, wan_updated));

	for (i=0; i < USER_NUM_MAX; i++)
	{
		username[0] = '\0';
		passwd[0] = '\0';

    #if 0
		CFG_get(CFG_SYS_USERS+i, username);
		CFG_get(CFG_SYS_ADMPASS+i, passwd);
	#endif

        // TODO: NVRAM
        memset(username, 0, 50);
        memset(passwd, 0, 50);
        memcpy(username, "admin", 5);
        memcpy(passwd, "admin", 5);

        HTTPD_DEBUGF((httpd, "[HTTPD] user_config() - NVRAM username= %s, passwd = %s\n", username, passwd));

		if (strcmp(username, userinfo[i].username) || strcmp(passwd, userinfo[i].passwd) ||
			(lan_updated && userinfo[i].listenif ==0)||(wan_updated && userinfo[i].listenif == 1))
		{
			memset(&(userinfo[i]), 0, sizeof(struct userinfo_t));
			strcpy(userinfo[i].username, username);
			strcpy(userinfo[i].passwd, passwd);
		}
	}
}

int auth_check(struct connstruct *cn)
{
    char* authpass;
    int i;
    char authinfo[MAXREQUESTLENGTH];

    HTTPD_DEBUGF((httpd, "[HTTPD] auth_check() - cn = %p, cn->authorization = %s\n", cn, cn->authorization));

    /* Split into user and password. */
    memcpy(authinfo, cn->authorization, MAXREQUESTLENGTH);
    authpass = strchr(authinfo, ':' );

    if ( authpass == (char*) 0 )
	/* No colon?  Bogus auth info. */
		goto send_auth;
    *authpass++ = '\0';

    /* Is this the right user? */
	for(i=0; i < USER_NUM_MAX; i++)
	{
        HTTPD_DEBUGF((
            httpd, "[HTTPD] auth_check() - (authinfo = %s, authpass = %s), (username = %s, passwd = %s)\n",
            authinfo, authpass, userinfo[i].username, userinfo[i].passwd));
        if((strcmp( authinfo, userinfo[i].username) == 0 ) &&
			( strcmp( authpass, userinfo[i].passwd) == 0 ))
			break;
	}

	/* no match username and password */
	if(i == USER_NUM_MAX)
	{
        HTTPD_DEBUGF((httpd, "[HTTPD] auth_check() - no match username and password\n"));
		goto send_auth;
	}

	return 0;

send_auth:
    send_authenticate(cn, cn->server_name);
	return HTTP_UNAUTHORIZED;
}

static void send_authenticate(struct connstruct *cn, char *realm)
{
    char buf[1024];

    HTTPD_DEBUGF((httpd, "[HTTPD] send_authenticate() - cn = %p, realm = %s\n", cn, realm));

    snprintf(buf, sizeof(buf), HTTP_VERSION" 401 Unauthorized\n"
         "WWW-Authenticate: Basic\n"
                 "realm=\"%s\"\n", realm);

    // no matter special_write result, also need to removeconnection
    special_write(cn->networkdesc, buf, strlen(buf));
    removeconnection(cn);
}

