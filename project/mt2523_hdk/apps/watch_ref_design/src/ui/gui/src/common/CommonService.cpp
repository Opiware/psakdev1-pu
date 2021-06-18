/* Copyright Statement:
 *
 */

#include <gui/common/CommonService.hpp>

bool CommonService::hrStatus = true;
CommonService::TimeoutType CommonService::screenTimeoutType = CommonService::TIMEOUT_30S;
#ifndef SIMULATOR
bool CommonService::backlight = false;
TimerHandle_t CommonService::timer = NULL;
QueueHandle_t CommonService::queue = NULL;
#endif
