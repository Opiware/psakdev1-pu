/* Copyright Statement:
 *
 */

#ifndef _KAL_PUBLIC_DEFS_H
#define _KAL_PUBLIC_DEFS_H


/*******************************************************************************
 * Type Definitions
 *******************************************************************************/

/* opaque type for task identity */
typedef struct {
    uint8_t unused;
} *kal_taskid;

/* opaque type for hisr identity */
typedef struct {
    uint8_t unused;
} *kal_hisrid;

/* opaque type for semaphore identity */
typedef struct {
    uint8_t unused;
} *kal_semid;

/* opaque type for message queue identity */
typedef struct {
    uint8_t unused;
} *kal_msgqid;

/* contain message queue information */
typedef struct {
    /* current number of pending messages in message queue */
    uint32_t pending_msgs;
    /* maximum number of pending messages in message queue */
    uint32_t max_msgs;
} kal_msgq_info;

/* opaque type for mutex identity */
typedef struct {
    uint8_t unused;
} *kal_mutexid;

/* opaque type for event group identity */
typedef struct {
    uint8_t unused;
} *kal_eventgrpid;

/* opaque type for partition memory pool identity */
typedef struct {
    uint8_t unused;
} *kal_poolid;

/* opaque type for Application Dynamic Memory identity */
typedef struct {
    uint8_t unused;
} *KAL_ADM_ID;

/* opaque type for Application Fix Memory identity */
typedef struct {
    uint8_t unused;
} *KAL_AFM_ID;

/* opaque type for First Level Memory Manager identity */
typedef struct {
    uint8_t unused;
} *KAL_FLMM_ID;

/* opaque type for Second Level Memory Manager identity */
typedef struct {
    uint8_t unused;
} *KAL_SLMM_ID;

/* opaque type for enhance mutex identity */
typedef struct {
    uint8_t unused;
} *kal_enhmutexid;

/* opaque type for kal timer identity */
typedef struct {
    uint8_t unused;
} *kal_timerid;

#endif  /* _KAL_PUBLIC_DEFS_H */
