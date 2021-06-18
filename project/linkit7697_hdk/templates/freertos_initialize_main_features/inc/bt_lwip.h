/* Copyright Statement:
 *
 */

 #ifndef __BT_LWIP_H__
#define __BT_LWIP_H__

#ifdef __cplusplus
extern "C" {
#endif

#if defined(MTK_BT_LWIP_ENABLE)

void bt_lwip_init(void);

void bt_lwip_send(const void *data, size_t size);
#endif

#ifdef __cplusplus
}
#endif

#endif // #ifndef __BT_LWIP_H__


