/* Copyright Statement:
 *
 */

#ifndef ____MTK_LL_H___H__
#define ____MTK_LL_H___H__

typedef struct _DL_LIST
{
	struct _DL_LIST *Next;
	struct _DL_LIST *Prev;
	struct _DL_LIST *CurrentList;
} DL_LIST, *PDL_LIST;

static inline void DlListInit(struct _DL_LIST *List)
{
	List->Next = List;
	List->Prev = List;
}

static inline void DlListAdd(struct _DL_LIST *List, struct _DL_LIST *Item)
{
	Item->Next = List->Next;
	Item->Prev = List;
	List->Next->Prev = Item;
	List->Next = Item;
}

static inline void DlListAddTail(struct _DL_LIST *List, struct _DL_LIST *Item)
{
	DlListAdd(List->Prev, Item);
    Item->CurrentList = List;
}

static inline void DlListDel(struct _DL_LIST *Item)
{
	Item->Next->Prev = Item->Prev;
	Item->Prev->Next = Item->Next;
	Item->Next = NULL;
	Item->Prev = NULL;
    Item->CurrentList = NULL;
}

static inline int DlListEmpty(struct _DL_LIST *List)
{
	return List->Next == List;
}

static inline unsigned int DlListLen(struct _DL_LIST *List)
{
	struct _DL_LIST *Item;
	unsigned int Count = 0;

	for (Item = List->Next; Item != List; Item = Item->Next)
		Count++;

	return Count;
}

#define DlListEntry(item, type, member) \
    ((type *) ((char *) item - offsetof(type, member)))

#define DlListFirst(list, type, member) \
    (DlListEmpty((list)) ? NULL : \
     DlListEntry((list)->Next, type, member))

#define DlListForEach(item, list, type, member) \
    for (item = DlListEntry((list)->Next, type, member); \
         &item->member != (list); \
         item = DlListEntry(item->member.Next, type, member))

#define DlListForEachSafe(item, n, list, type, member) \
    for (item = DlListEntry((list)->Next, type, member), \
             n = DlListEntry(item->member.Next, type, member); \
        &item->member != (list); \
        item = n, n = DlListEntry(n->member.Next, type, member))

#endif /* __MTK_LL_H__ */

