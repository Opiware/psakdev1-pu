/* Copyright Statement:
 *
 */
#include <stdio.h>

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


