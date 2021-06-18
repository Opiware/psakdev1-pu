/* Copyright Statement:
 *
 */

#ifndef __AUTH_CHECK_H__
#define __AUTH_CHECK_H__

#define HTTP_UNAUTHORIZED	401

#ifndef	CONFIG_HTTPD_MAX_USERS
	#define USER_NUM_MAX	1
#else
	#if	((CONFIG_HTTPD_MAX_USERS < 1) || (CONFIG_HTTPD_MAX_USERS>4))
		#define USER_NUM_MAX	1
	#else
		#define	USER_NUM_MAX CONFIG_HTTPD_MAX_USERS
	#endif
#endif

struct userinfo_t{
	char username[16];
	char passwd[16];
	int admin_addr;
	int logout_time;
	unsigned char listenif;
};

int auth_check(struct connstruct *cn);
void user_config(int lan_updated, int wan_updated);

#endif /* __AUTH_CHECK_H__ */

