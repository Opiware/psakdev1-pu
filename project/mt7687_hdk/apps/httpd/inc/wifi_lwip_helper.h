/* Copyright Statement:
 *
 */

#ifndef __WIFI_LWIP_H__
#define __WIFI_LWIP_H__

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
  * @brief  network init function. initial wifi and lwip config
  * @param None
  * @retval None
  */

void lwip_network_init(uint8_t opmode);


void lwip_net_start(uint8_t opmode);


void lwip_net_stop(uint8_t opmode);


/**
  * @brief  when wifi and ip ready will return.
  * @param None
  * @retval None
  */
void lwip_net_ready(void);

/**
* @note This api is only for internal use
*/
uint8_t wifi_set_opmode(uint8_t target_mode);

#ifdef __cplusplus
}
#endif

#endif /* __WIFI_LWIP_H__ */
