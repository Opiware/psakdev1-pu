/* Copyright Statement:
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "misc.h"

static char *__rstrtok;

// TODO:  NOT Thread Safe (__rstrtok static variable) so far ...Michael
char *rstrtok(char *s, const char *ct)
{
    char *sbegin, *send;

    sbegin  = s ? s : __rstrtok;
    if (!sbegin) {
        return NULL;
    }

    sbegin += strspn(sbegin, ct);
    if (*sbegin == '\0') {
        __rstrtok = NULL;
        return (NULL);
    }

    send = strpbrk(sbegin, ct);
    if (send && *send != '\0') {
        *send++ = '\0';
    }

    __rstrtok = send;

    return (sbegin);
}

void convert_string_to_hex_array(char *string, unsigned char *hex)
{
    char *ptr, *keys = string;
    int index = 0;
    unsigned char hb, lb;
    ptr = rstrtok((char *)keys, ",");
    if (NULL == ptr) {
        return;
    }
    printf("[%d] token=%s\n", index, ptr);
    for (int i = 0; i < strlen(ptr); i++) {
        hb = ptr[i];
        if (hb >= 'A' && hb <= 'F') {
            hb = hb - 'A' + 10;
        } else if (hb >= '0' && hb <= '9') {
            hb = hb - '0';
        } else if(hb >= 'a' && hb <= 'f') {
            hb = hb - 'a' + 10;
        }
        i++;
        lb = ptr[i];
        if (lb >= 'A' && lb <= 'F') {
            lb = lb - 'A' + 10;
        } else if (lb >= '0' && lb <= '9') {
            lb = lb - '0';
        } else if (lb >= 'a' && lb <= 'f') {
            lb = lb - 'a' + 10;
        }
        hex[index++] = (hb << 4) | (lb);
    }
}


void hex_dump(char *str, unsigned char *pSrcBufVA, unsigned int SrcBufLen)
{
    unsigned char *pt;
    int x;

    pt = pSrcBufVA;
    printf("%s: %p, len = %d\n\r", str, pSrcBufVA, SrcBufLen);
    for (x = 0; x < SrcBufLen; x++) {
        if (x % 16 == 0) {
            printf("0x%04x : ", x);
        }
        printf("%02x ", ((unsigned char)pt[x]));
        if (x % 16 == 15) {
            printf("\n\r");
        }
    }
    printf("\n\r");
}

void hex_dump_limit_len(char *str, unsigned char *pSrcBufVA, unsigned int SrcBufLen, unsigned int limit_len)
{
    unsigned char *pt;
    int x;
    unsigned int print_len = SrcBufLen;

    pt = pSrcBufVA;

    if (print_len > limit_len) {
        print_len = limit_len;
    }

    printf("%s: %p, len = %d, dump lenght is limited to %u\n\r",
           str,
           pSrcBufVA,
           SrcBufLen,
           limit_len);

    for (x = 0; x < print_len; x++) {
        if (x % 16 == 0) {
            printf("0x%04x : ", x);
        }
        printf("%02x ", ((unsigned char)pt[x]));
        if (x % 16 == 15) {
            printf("\n\r");
        }
    }

    printf("\n\r");
}


static char strbuf[20 + 1];

char *uint64ToDecStr(uint64_t value)
{

    char *p = strbuf + sizeof(strbuf);
    bool first;

    *(--p) = '\0';

    for (first = true; value || first; first = false) {
        const uint32_t digit = value % 10;
        const char c = '0' + digit;
        *(--p) = c;
        value = value / 10;
    }

    return p;
}

void ignore_spaces_dash(char *pin_src, char *pin_dst)
{
    int i, j = 0;
    int len = 0;

    if (pin_src) {
        len = strlen(pin_src);
        for (i = 0; i < len; i++) {
            if (pin_src[i] == 0x20) { // ' '
                continue;
            }
            if (pin_src[i] == 0x2d) { // '-'
                continue;
            }
            pin_dst[j++] = pin_src[i];
        }
    }
}

uint8_t BtoH(char ch)
{
    if (ch >= '0' && ch <= '9') {
        return (ch - '0');    /* Handle numerals*/
    }
    if (ch >= 'A' && ch <= 'F') {
        return (ch - 'A' + 0xA);    /* Handle capitol hex digits*/
    }
    if (ch >= 'a' && ch <= 'f') {
        return (ch - 'a' + 0xA);    /* Handle small hex digits*/
    }
    return (255);
}

void AtoH(char *src, char *dest, int destlen)
{
    char *srcptr;
    char *destTemp;

    srcptr = src;
    destTemp = (char *) dest;

    while (destlen--) {
        *destTemp = BtoH(*srcptr++) << 4;    /* Put 1st ascii byte in upper nibble.*/
        *destTemp += BtoH(*srcptr++);      /* Add 2nd ascii byte to above.*/
        destTemp++;
    }
}


int wifi_is_dhcpd_dhcp_coexist_enabled(void)
{
#ifdef MTK_WIFI_DHCPD_DHCP_COEXIST_ENABLE
    return 1;
#else
    return 0;
#endif
}
