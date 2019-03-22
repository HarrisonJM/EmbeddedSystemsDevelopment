/*!
 * @brief Simple linked list structy boy
 * 
 * @author harrison marcks
 * 
 * @date 4/3/19
 */

#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__

#include <helpers/boollint.h>
#include <stddef.h>

/*!
 * @brief ListElement struct
 * @{
 */
typedef struct LINKEDLISTITEM linkedListItem_T;
struct LINKEDLISTITEM {
    linkedListItem_T* _nextItem;        /*! < Next item in list */
    linkedListItem_T* _previousItem;    /*! < Previous item in the list */
};
/*! @} */

/*!
 * @brief LinkedList itself
 * @{
 */
typedef struct LINKEDLIST {
    linkedListItem_T _HEAD; /*! < Holds first Item */
    linkedListItem_T _TAIL; /*! < Points to just after last item */
} linkedList_T;
/*! @} */

/*!
 * @brief Returns a pointer to the structure that the list is embedded inside
 * 
 * @param LIST_ELEM The list element of the item we want
 * @param STRUCT The name of the OUTER structure we're embedded in
 * @param MEMBER THE NAME of the list as given/defined within the outer structure
 */ 
#define LISTENTRY(LIST_ELEM, STRUCT, MEMBER)           \
        ((STRUCT *) ((uint8_t *) &(LIST_ELEM)->_nextItem     \
                     - offsetof (STRUCT, MEMBER._nextItem)))

void ListInit(linkedList_T* list);
linkedListItem_T* ListHead (linkedList_T* list);
linkedListItem_T* ListTail (linkedList_T* list);

linkedListItem_T* ListItemNext (linkedListItem_T * listItem);
linkedListItem_T* ListItemPrev (linkedListItem_T * listItem);

void ListItemInsert (linkedListItem_T* before
                     , linkedListItem_T* newItem);
linkedListItem_T* ListRemoveItem (linkedListItem_T* removeItem);



#endif /* __LINKEDLIST_H__ */
