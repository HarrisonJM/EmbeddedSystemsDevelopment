
#include <helpers/linkedlist/linkedList.h>

void ListInit(linkedList_T* list)
{
    if(list != NULL)
    {
        list->_HEAD._previousItem = NULL;
        list->_HEAD._nextItem = &list->_TAIL;

        list->_TAIL._previousItem = &list->_HEAD;
        list->_TAIL._nextItem = NULL;
    }
}

linkedListItem_T* ListHead (linkedList_T* list)
{
    if(list != NULL)
    {
        return &list->_HEAD;
    }
    return NULL;
}

linkedListItem_T* ListTail (linkedList_T* list)
{
    if(list != NULL)
    {
        return &list->_TAIL;
    }
    return NULL;
}

linkedListItem_T *ListItemNext (linkedListItem_T * listItem)
{
    if(listItem != NULL)
    {
        return listItem->_nextItem;
    }
    return NULL;
}

linkedListItem_T *ListItemPrev (linkedListItem_T * listItem)
{
    if(listItem != NULL)
    {
        return listItem->_previousItem;
    }
    return NULL;
}

void ListItemInsert (linkedListItem_T* before
                     , linkedListItem_T* newItem)
{
    if(newItem == NULL || before == NULL)
    {
        return;
    }

    newItem->_previousItem = before->_previousItem;
    newItem->_nextItem = before;
    before->_previousItem->_nextItem = newItem;
    before->_previousItem = newItem;
}

linkedListItem_T* ListRemoveItem (linkedListItem_T* removeItem)
{
    if(removeItem == NULL)
    {
        return NULL;
    }

    removeItem->_previousItem->_nextItem = removeItem->_nextItem;
    removeItem->_nextItem->_previousItem = removeItem->_previousItem;
    return removeItem->_nextItem;
}
