/* Copyright Statement:
 *
 */

/*****************************************************************************
 *
 * Description:
 * ------------
 * The header file for users.
 *
 ****************************************************************************/



#ifndef __BT_NOTIFY_LIST_H__
#define __BT_NOTIFY_LIST_H__
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef struct Node
{
    uint8_t *packet;
    uint16_t packet_length;
    struct Node *next;
}Lnode;

Lnode *createList(void);
void addNode(Lnode *head, uint8_t *packet, uint16_t packet_length);
uint32_t Length(Lnode *head);
uint32_t deleteElem(Lnode * head, uint8_t *packet, uint16_t packet_length);
uint32_t FindNode(Lnode *head, uint8_t *packet, uint16_t packet_length);
Lnode *FindNodeByIndex(Lnode * head, int index);



#endif/*__BT_NOTIFY_LIST_H__*/

