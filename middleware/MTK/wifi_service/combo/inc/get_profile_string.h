/* Copyright Statement:
 *
 */

#ifndef __GET_PROFILE_STRING_H__
#define __GET_PROFILE_STRING_H__

#ifdef __cplusplus
extern "C" {
#endif

#define ETH_LENGTH_OF_ADDRESS   6
#ifdef MTK_SINGLE_SKU_SUPPORT
#define PROFILE_BUF_LEN (800)
#else
#define PROFILE_BUF_LEN (256) // FIXME
#endif

/**
 * strpbrk - Find the first occurrence of a set of characters
 * @cs: The string to be searched
 * @ct: The characters to search for */
char *strpbrk(const char *cs, const char *ct);

/**
 * rstrtok - Split a string into tokens
 * @s: The string to be searched
 * @ct: The characters to search for
 * * WARNING: strtok is deprecated, use strsep instead. However strsep is not compatible with old architecture. */
char *rstrtok(char *s, const char *ct);

void wifi_conf_get_mac_from_str(char *mac_dst, const char *mac_src);

void wifi_conf_get_ip_from_str(unsigned char *ip_dst, const char *ip_src);

int wifi_conf_get_ch_table_from_str(ch_desc_t *ch_list, char ch_list_num, const char *ch_str, unsigned int ch_str_len);

void wifi_conf_get_pwr_from_str(uint16_t ret_len, void * single, const char *pwr_src);

#ifdef __cplusplus
}
#endif

#endif // #ifndef __GET_PROFILE_STRING_H__

