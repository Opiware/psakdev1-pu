/* Copyright Statement:
 *
 */

#ifndef __CGI_H__
#define __CGI_H__

typedef int (*CGI_SEND)(int sd, const char *buff, size_t len);

struct cgi_para
{
    int sd; // socket id
    CGI_SEND func; // send function
    char *cmd; // cmd
    int cmd_len;   // cmd length
};

typedef int (*CGI_FUNC)(struct cgi_para *para);

struct cgi
{
	char *name;
    CGI_FUNC func;
} ;

CGI_FUNC cgi_filename_match(char *path_info);

#endif /* __CGI_H__ */
