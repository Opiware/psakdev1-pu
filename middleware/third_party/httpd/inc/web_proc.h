/* Copyright Statement:
 *
 */

#ifndef __WEB_PROC_H__
#define __WEB_PROC_H__
//==============================================================================
//                                INCLUDE FILES
//==============================================================================
#include <stdio.h>
#include <time.h>

#define	WEBP_COMPRESS		0x0001
#define	WEBP_NORMAL			0x0000
#define NO_AUTH				0x0002
#define CACHE				0x0004
#define	WEBP_LOCKED			0x0008

#define NUM_QUERYVAR	    255
#define MAXREQUESTLENGTH    256

/* record environmental variables */

typedef struct
{
	char* name;
	char* value;
}query_var;

struct connstruct
{
    struct connstruct *next;
    int state;
    int reqtype;
    int networkdesc;
    int filedesc; // MT7687 do not support FS, this paramter is not used
    char actualfile[MAXREQUESTLENGTH];
    char filereq[MAXREQUESTLENGTH];
    char dirname[MAXREQUESTLENGTH];
    char server_name[MAXREQUESTLENGTH];
    int numbytes;
    unsigned char is_v1_0;
    unsigned char close_when_done;
    time_t if_modified_since;
    char authorization[MAXREQUESTLENGTH];
    int post_read;
    int post_state;
    char *post_data;
    char *query;
    int query_len;
    int content_length;
	query_var *query_tbl;
    unsigned char is_cgi;
};

typedef struct
{
	char *path;						/* Web page URL path */
	int (*fileFunc)(struct connstruct *, char *);		/* web page function call */
	unsigned long size;			/* storage size */
	short flag;						/* flag */
	void *param;					/* parameter to fileFunc() */
	char *(*cgiFunc)(struct connstruct *);		/* cgi function call */
	unsigned long offset;		/* the start offset of file*/
}webpage_entry;

typedef struct
{
	int code;
	char *filename;
}err_page;

void query_init(struct connstruct *req);
char *query_getvar(struct connstruct *req, char *name);

#define WEB_getvar(req, var, default)	( query_getvar(req, var) ? : default )
#define WEB_query(req, var) query_getvar(req, var)

int WEB_write_blk(struct connstruct *req, char* startp, int offset, int len);
int WEB_printf(struct connstruct *req, const char *format, ...);

#endif /* __WEB_PROC_H__ */
