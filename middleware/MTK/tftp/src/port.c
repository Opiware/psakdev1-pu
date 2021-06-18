/* Copyright Statement:
 *
 */

#include <stdio.h>
//#include <unistd.h>
#include <errno.h>

#include "port.h"

//#define I_O_DEBUG

#ifdef I_O_DEBUG
#define I   printf("enter: %s %d\n", __FUNCTION__, __LINE__)
#define O   printf("exit: %s %d\n", __FUNCTION__, __LINE__)
#else
#define I
#define O
#endif

#define SA_TYPE struct sockaddr
#define IN_TYPE struct sockaddr_in

/****************************************************************************
 *
 * Static Functions.
 *
 ****************************************************************************/


static int32_t to_saddr(IN_TYPE *saddr, const char *addr, unsigned short port)
{
    I;

    os_memset(saddr, 0, sizeof(*saddr));

    /* family */
    saddr->sin_family = AF_INET;

    /* IP address */
    if (addr) {
        if (inet_aton(addr, &saddr->sin_addr) == 0) {
            printf("%s %s\n", addr, strerror(errno));
            O;
            return -1;
        }
    } else {
        saddr->sin_addr.s_addr = INADDR_ANY;
    }

    /* port */
    saddr->sin_port = htons(port);

    O;
    return 0;
}


/****************************************************************************
 *
 * API Functions.
 *
 ****************************************************************************/


/**
 * convert local and remote addresses.
 * create udp socket.
 * bind udp socket. */
void *tftp_sock_open(const char      *raddr,
                     unsigned short  rport,
                     unsigned short  lport)
{
    tftp_sock_t *tsock = NULL;
    IN_TYPE     sa_laddr;

    I;

    tsock = os_malloc(sizeof(*tsock));
    if (!tsock) {
        goto tftp_sock_open_err;
    }

    os_memset(tsock, 0, sizeof(*tsock));

    if ((to_saddr(&tsock->sa_raddr, raddr, rport) < 0) ||
        (to_saddr(&sa_laddr,       NULL,  lport) < 0)) {
        goto tftp_sock_open_err;
    }

    tsock->s = socket(AF_INET, SOCK_DGRAM, 0);

    if (tsock->s < 0) {
        printf("%s %s\n", __FUNCTION__, strerror(errno));
        goto tftp_sock_open_err;
    }

    if (bind(tsock->s, (SA_TYPE *)&sa_laddr, sizeof(SA_TYPE)) < 0)
    {
        printf("%s:%u %s %d %d\n", __FUNCTION__, __LINE__, strerror(errno), tsock->s, lport);
        goto tftp_sock_open_err;
    }

    goto tftp_sock_open_end;

tftp_sock_open_err:
	if (tsock)
	{
		tftp_sock_close(tsock);
	    tsock = NULL;
	}    

tftp_sock_open_end:
    O;
    return tsock;
}


void tftp_sock_close(void *sock)
{
    I;
	if (!sock)
	{
		return;
	}
	
    tftp_sock_t *tsock = (tftp_sock_t *)sock;
    close(tsock->s);
    os_free(tsock);
    O;
}


int16_t tftp_sock_send(void *sock, const uint8_t *buf, uint16_t len)
{
    tftp_sock_t *tsock = sock;

    I;

    if (sendto(tsock->s, buf, len, 0, (const SA_TYPE *)&tsock->sa_raddr, sizeof(tsock->sa_raddr)) < 0) {
        printf("%s %s\n", __FUNCTION__, strerror(errno));

        O;

        return -1;
    }

    O;

    return len;
}


int16_t tftp_sock_recv(void *sock, uint8_t *buf, uint16_t len)
{
    int     size;
    tftp_sock_t *tsock = sock;
    socklen_t   sock_len = sizeof(tsock->sa_raddr);

    I;

    size = recvfrom(tsock->s, buf, len, 0,
                    (SA_TYPE *)&tsock->sa_raddr, &sock_len);

    O;

    return (int16_t)size;
}
