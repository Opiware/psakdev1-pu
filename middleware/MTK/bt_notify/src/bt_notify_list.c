/* Copyright Statement:
 *
 */

 

#include "bt_notify_list.h"
#include <FreeRTOS.h>

/**
 * @brief          This function is for create a list.
 * @param[in]  void.
 * @return       the head of the list. */

Lnode *createList(void)
{
    Lnode *head;
    head = (Lnode *)pvPortMalloc(sizeof(Lnode));
    
    head->packet = NULL;
    head->packet_length = 0;
    head->next = NULL;
 
    return head;
}

/**
 * @brief          This function is for add a node into list.
 * @param[in]  head      is the head of the list.
 * @param[in]  packet   is the data point.
 * @param[in]  packet_length       is the data length.
 * @return       void. */

void addNode(Lnode *head, uint8_t *packet, uint16_t packet_length) 
{//insert start
    Lnode *p = (Lnode*)pvPortMalloc(sizeof(Lnode));
    p->packet = packet;
    p->packet_length = packet_length;
    p->next = head->next;
    head->next = p;
}

/**
 * @brief          This function is for get the list length.
 * @param[in]  head      is the head of the list.
 * @return       the length of the list. */

uint32_t Length(Lnode *head)//get list length
{
    uint32_t n=0;
    Lnode *p;
    p=head->next;
    while(p)
    {
       n++;
       p=p->next;
    }
    return n;
}

/**
 * @brief          This function is for delete a node into list.
 * @param[in]  head      is the head of the list.
 * @param[in]  packet   is the data point.
 * @param[in]  packet_length       is the data length.
 * @return       delete success or not. */

uint32_t deleteElem(Lnode * head, uint8_t *packet, uint16_t packet_length) 
{
    Lnode * p;
    Lnode * q;
    for(p = head; p != NULL; p = p->next) {
        if(p->next->packet == packet) {
            q = p->next;
            p->next = q->next;
            vPortFree(q);
            return 1; 
        }
    }
    return 0; 
}

/**
 * @brief          This function is for find a node into list.
 * @param[in]  head      is the head of the list.
 * @param[in]  packet   is the data point.
 * @param[in]  packet_length       is the data length.
 * @return       the exit node or not. */

uint32_t FindNode(Lnode *head, uint8_t *packet, uint16_t packet_length) 
{
    Lnode *p;
    for(p = head->next; p != NULL; p = p->next) {
        if(p->packet == packet) 
            return 1; 
    }
    return 0; 
}

/**
 * @brief          This function is for add a node by the index of the list.
 * @param[in]  head      is the head of the list.
 * @param[in]  packet   is the data point.
 * @param[in]  packet_length       is the data length.
 * @return       the node. */

Lnode *FindNodeByIndex(Lnode * head, int index)
{
	int i;
    Lnode * p;
    p = head->next;
	for(i = 0;i < index - 1;i ++)
	{
		
		if(NULL == p)
		{
			break;
		}
                 p = p->next;
	}

	if(NULL == p)
	{
		return NULL;
	}

	return p;
}


