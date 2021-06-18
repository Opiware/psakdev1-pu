/* Copyright Statement:
 *
 */

#ifndef _EINT_KEY_CUSTOM_H_
#define _EINT_KEY_CUSTOM_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <stdbool.h>
#include "eint_key.h"

/*user could modify for your keydata*/
#define BSP_EINT_KEY_NUMBER             1    /*supported key numbers*/
#define BSP_EINT_KEY_DATA0              126  /*keyad defined by user, must be 125<key_data<254*/

/*extern declaration*/
extern bsp_eint_key_mapping_t const eint_key_mapping[BSP_EINT_KEY_NUMBER];


void eint_key_custom_init(void);

#ifdef __cplusplus
}
#endif

#endif /* _EINT_KEY_CUSTOM_H_ */

