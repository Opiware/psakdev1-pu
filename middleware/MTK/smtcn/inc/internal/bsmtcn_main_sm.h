/* Copyright Statement:
 *
 */
 

#ifndef BSMTCN_MAIN_SM_H
#define BSMTCN_MAIN_SM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>


typedef enum _BSMTCN_STATE {
		BSMTCN_MAIN_INITIALIZE = 0,
		BSMTCN_MAIN_IDLE,
		BSMTCN_MAIN_LOCK_START,
		BSMTCN_MAIN_LOCK_STOP,
		BSMTCN_MAIN_CHANNEL_DECIDE,
		BSMTCN_MAIN_NORMAL_RECV_START,
		BSMTCN_MAIN_NORMAL_RECV_STOP,
		BSMTCN_MAIN_FINISH
} BSMTCN_MAIN_STATE, *P_BSMTCN_MAIN_STATE;

struct bsmtcn_main_state_machine {
    uint8_t addr[ETH_ALEN];
	BSMTCN_MAIN_STATE bsmtcn_main_state;
	bool start_block_check;
	bool channel_decide;
	bool lock_succ;
	bool complete_all_blocks;
	bool reset;
	bool changed;
};

#define STATE_MACHINE_DATA struct bsmtcn_main_state_machine

void bsmtcn_main_sm_step(struct bsmtcn_main_state_machine *sm);

struct bsmtcn_main_state_machine *bsmtcn_main_sm_init(void *adapter);

void bsmtcn_main_sm_deinit(void *adapter);

#ifdef __cplusplus
}
#endif

#endif /* BSMTCN_MAIN_SM_H */
