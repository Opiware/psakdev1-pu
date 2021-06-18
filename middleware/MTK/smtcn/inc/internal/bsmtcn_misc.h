/* Copyright Statement:
 *
 */

#ifndef BSMTCN_MISC_H
#define BSMTCN_MISC_H

#ifdef __cplusplus
extern "C" {
#endif
#include <stdint.h>
#include <stdbool.h>

#define ENCRYTION 1

#ifndef ETH_ALEN
#define ETH_ALEN 6
#endif

#undef TRUE
#define TRUE true

#ifdef __GNUC__
#define PRINTF_FORMAT(a,b) __attribute__ ((format (printf, (a), (b))))
#define STRUCT_PACKED __attribute__ ((packed))
#else
#define PRINTF_FORMAT(a,b)
#define STRUCT_PACKED
#endif

#if 1
#define sm_printf(level,...) \
	         do { } while (0)
#else 
#define sm_printf(level,...) \
	     printf(__VA_ARGS__);\
	            printf("\r\n")
#endif

#define bsmtcn_printf(level,...) \
	    do {\
            printf(__VA_ARGS__);\
	        printf("\r\n");\
        } while(0)

enum {
	MSG_EXCESSIVE, MSG_MSGDUMP, MSG_DEBUG, MSG_INFO, MSG_WARNING, MSG_ERROR, MSG_BOOTON
};

void bsmtcn_hex_dump(char *str, uint8_t *pSrcBufVA, uint32_t SrcBufLen);

#ifndef MAC2STR
#define MAC2STR(a) (a)[0], (a)[1], (a)[2], (a)[3], (a)[4], (a)[5]
#define MACSTR "%02x:%02x:%02x:%02x:%02x:%02x"
/*
 * Compact form for string representation of MAC address
 * To be used, e.g., for constructing dbus paths for P2P Devices */
#define COMPACT_MACSTR "%02x%02x%02x%02x%02x%02x"
#endif

#define BASE_LEN 92

uint8_t CRC8_Table(uint8_t *p, char counter) ;

unsigned short crc16_ccitt(const void *buf, int32_t len);


uint8_t byte_scramble_operation(uint8_t ulReflect);

uint8_t atomic_read_smtcn_flag(void);


#ifndef BIT
#define BIT(n)                  ((uint32_t) 1 << (n))
#define BITS(m,n)                       (~(BIT(m)-1) & ((BIT(n) - 1) | BIT(n)))
#endif /* BIT */

#ifdef __cplusplus
}
#endif
#endif /* BSMTCN_MISC_H */
