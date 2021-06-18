/* Copyright Statement:
 *
 */

int ostimer_init( void );
int ostimer_set_frame_duration( uint16_t frm_dur );
int ostimer_enable( uint32_t ufn );
int ostimer_disable( void );
int ostimer_get_frame_num( uint32_t *frm_dur );

int test_ostimer( void );


