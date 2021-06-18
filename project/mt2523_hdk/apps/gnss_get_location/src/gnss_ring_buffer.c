/* Copyright Statement:
 *
 */



#include "gnss_ring_buffer.h"
#include <string.h>
#include "gnss_app.h"

// this implementation can not be used by multi-task. if you want, you need use mutex.
// but this implementation can be read by one task, and write by the other task.

/**
* @brief       This function used to init ring_buf_struct_t
* @param[in]   ring_buf: Pointer to a struct which will be initialized
* @param[in]   buf: Pointer to a buffer 
* @param[in]   buf_size: size of the buf
* @return      None.
*/
void ring_buf_init(ring_buf_struct_t *ring_buf, int8_t* buf, int16_t buf_size)
{
    ring_buf->buf_size = buf_size;
    ring_buf->buf = buf;
    ring_buf->start_ind = ring_buf->end_ind = 0;
}


/**
* @brief       This function used to check the ring buffer is empty or not
* @param[in]   ring_buf: Pointer to a ring buffer
* @return      int32_t: 1 is empty, 0 is not empty
*/
int32_t is_empty(ring_buf_struct_t *ring_buf)
{
    return ring_buf->end_ind == ring_buf->start_ind;
} 

/**
* @brief       This function used to put data to ring buffer
* @param[in]   ring_buf: Pointer to a ring buffer
* @param[in]   buf: Pointer to data buffer
* @param[in]   ring_buf: data size
* @return      int32_t: the putted data size
*/
int32_t put_data(ring_buf_struct_t *ring_buf, int8_t* buf, int32_t buf_len)
{
    //GNSSLOGD("ring_buf putBB start[%d],end[%d], add len:%d\r\n", ring_buf->start_ind, ring_buf->end_ind, buf_len);
    if ((ring_buf->start_ind > ring_buf->end_ind && ring_buf->end_ind + buf_len >= ring_buf->start_ind) 
        || (ring_buf->start_ind <= ring_buf->end_ind && ring_buf->end_ind + buf_len - ring_buf->buf_size >= ring_buf->start_ind) ) {
        GNSSLOGD("ring_buf overflow!!");
    }
    
    if (buf_len + ring_buf->end_ind >= ring_buf->buf_size){
        memcpy(ring_buf->buf + ring_buf->end_ind, buf, ring_buf->buf_size - ring_buf->end_ind);
        memcpy(ring_buf->buf, buf + ring_buf->buf_size - ring_buf->end_ind, buf_len - (ring_buf->buf_size - ring_buf->end_ind));
        ring_buf->end_ind = ring_buf->end_ind + buf_len - ring_buf->buf_size;
    } else {
        memcpy(ring_buf->buf + ring_buf->end_ind, buf, buf_len);
        ring_buf->end_ind += buf_len;
    }
    //GNSSLOGD("ring_buf putEE start[%d],end[%d], add len:%d\r\n", ring_buf->start_ind, ring_buf->end_ind, buf_len);
    return buf_len;
}

/**
* @brief       This function used to read data from ring buffer
* @param[in]   ring_buf: Pointer to a ring buffer
* @param[in/out]   buf: Pointer to buffer
* @param[in]   buf_len: buffer size
* @return      int32_t: the read data size
*/
int32_t consume_data(ring_buf_struct_t *ring_buf, int8_t* buf, int32_t buf_len)
{
    int32_t consume_len;
    int32_t end_ind  = ring_buf->end_ind;
    
    if (end_ind == ring_buf->start_ind) {
        return 0;
    }
    //GNSSLOGD("ring_buf consBB, start[%d],end[%d], cons len:%d\r\n", ring_buf->start_ind, ring_buf->end_ind, buf_len);
    if (ring_buf->start_ind < end_ind) {
        if (end_ind - ring_buf->start_ind > buf_len) {
            consume_len = buf_len;
            memcpy(buf, ring_buf->buf + ring_buf->start_ind, buf_len);
            ring_buf->start_ind += buf_len;
        } else {
            consume_len = end_ind - ring_buf->start_ind;
            memcpy(buf, ring_buf->buf + ring_buf->start_ind, consume_len);
            ring_buf->start_ind = end_ind;
        }
    } else {
        if (ring_buf->buf_size - ring_buf->start_ind > buf_len) {
            consume_len = buf_len;
            memcpy(buf, ring_buf->buf + ring_buf->start_ind, buf_len);
            ring_buf->start_ind += buf_len;
        } else {
            int32_t copyed_len = ring_buf->buf_size - ring_buf->start_ind;
            memcpy(buf, ring_buf->buf + ring_buf->start_ind, copyed_len);
            ring_buf->start_ind = 0;
            if (end_ind > buf_len - copyed_len) {
                consume_len = buf_len;
                memcpy(buf + copyed_len, ring_buf->buf, buf_len - copyed_len);
                ring_buf->start_ind += buf_len - copyed_len;
            } else {
                consume_len = copyed_len + end_ind;
                memcpy(buf + copyed_len, ring_buf->buf, end_ind);
                ring_buf->start_ind = end_ind;
            }
        }
    }
     return consume_len;
}

