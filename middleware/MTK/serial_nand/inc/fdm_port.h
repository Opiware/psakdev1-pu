/* Copyright Statement:
 *
 */

#ifndef __FDM_PORT_H__
#define __FDM_PORT_H__

#ifdef __cplusplus
extern "C" {
#endif

/* FDM lock relative functions need implemented by user. */
void init_FDM_lock(void);
void NANDFDM_Lock(void);
void NANDFDM_Unlock(void);
uint32_t NANDFDM_QueryExceptionStatus(void);
uint32_t NANDFDM_get_rand(uint32_t *rand_number);


#ifdef __cplusplus
}
#endif

#endif

