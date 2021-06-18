/* Copyright Statement:
 *
 */

#ifndef __PORT_H__
#define __PORT_H__


/***************************************************************************
 *
 * C Library Functions.
 *
 ***************************************************************************/


#include <stdint.h>


#ifdef __linux__
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif /* __linux__ */

#include <stdlib.h>
#include <os.h>
#include <os_util.h>
#include "lwip/sockets.h"


typedef struct tftp_sock_s {
    int                 s;
    struct sockaddr_in  sa_raddr;
} tftp_sock_t;


void *tftp_sock_open(const char      *raddr,
                     unsigned short  rport,
                     unsigned short  lport);



void        tftp_sock_close(void *sock);


int16_t     tftp_sock_send(void *sock, const uint8_t *buf, uint16_t len);


int16_t     tftp_sock_recv(void *sock, uint8_t *buf, uint16_t len);


/***************************************************************************
 *
 * C Library Functions.
 *
 ***************************************************************************/


#ifdef __linux__
#include <stdlib.h>
#include <string.h>

#define os_malloc   malloc
#define os_free     free
#define os_memcpy   memcpy
#define os_memset   memset
#define os_strlen   strlen
#endif /* __linux__ */

/* FreeRTOS */
#include "FreeRTOS.h"

#endif /* __PORT_H__ */

