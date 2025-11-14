#include "SList.h"

#ifdef __cplusplus
extern "C"
{
#endif
void SLinkListInit(SLinkList_t* sllist)
{
    sllist->head = NULL;
    sllist->tail = NULL;
    sllist->SListSize = 0;
}
bool SLinkListIsEmpty(SLinkList_t* sllist)
{
    return (NULL == sllist->head);
}

SLinkListElement_t* SLinkListIteratorGetNext(SLinkListElement_t* element)
{
    return element->next;
}


OperationResult_t SLinkListAdd(SLinkList_t* sllist, SLinkListElement_t* element)
{
    sllist->SListSize++;
    
    
    if(SLinkListIsEmpty(sllist))
    {
        sllist->head = element;
    }
    else
    {
        sllist->tail->next = element;
    }
    element->next = NULL;
    sllist->tail = element;

    return SUCCESS;
}

SLinkListElement_t* SLinkListPop(SLinkList_t* sllist)
{
    SLinkListElement_t* head = sllist->head;
    if(SLinkListIsEmpty(sllist))
    {
        return NULL;
    }
    
    sllist->SListSize--;
    if(sllist->head == sllist->tail)        
    {
        sllist->tail = NULL;
        sllist->head = NULL;
        return head;
    }

    if(sllist->head->next == sllist->tail)
    {
       sllist->head = sllist->tail; 
    }
    else
    {
        sllist->head = sllist->head->next;
    }

    head->next = NULL;

    return head;
}


OperationResult_t SLinkListInsertToIndex(SLinkList_t* sllist, SLinkListElement_t* element, uint32_t index)
{
    if(SLinkListIsEmpty(sllist))
    {
        SLinkListAdd(sllist,element);
        return SUCCESS;
    }

    if(index > sllist->SListSize)
    {
        return FAIL;
    }

    sllist->SListSize++;
    SLinkListElement_t* iter = sllist->head;
    SLinkListElement_t* prev = NULL;
    while(index>0)
    {
        prev = iter;
        iter = SLinkListIteratorGetNext(iter);
        index--;
    }
    
    element->next = iter;

    if(iter == sllist->head)
    {
        sllist->head = element;
    }
    else if (NULL == iter)
    {
        prev->next = element; 
        sllist->tail = element;
    }
    else
    {
        prev->next = element;
    }

    return SUCCESS;
}

SLinkListElement_t* SLinkListReturnIndex(SLinkList_t* sllist, uint32_t index)
{
  
  if(index > sllist->SListSize-1)
  {
    return NULL;
  }

  SLinkListElement_t* iter = sllist->head;

  while(index > 0)
  {
    iter = SLinkListIteratorGetNext(iter);
    index--;
  }

  return iter;

}

OperationResult_t SLinkListDeleteToIndex(SLinkList_t* sllist, uint32_t index)
{
    if(SLinkListIsEmpty(sllist))
    {
        return FAIL;
    }

    if(index > sllist->SListSize-1)
    {
        return FAIL;
    }
    
    sllist->SListSize--;
    SLinkListElement_t* iter = sllist->head;
    SLinkListElement_t* prev = NULL;
    while(index>0)
    {
        prev = iter;
        iter = SLinkListIteratorGetNext(iter);
        index--;
    }
    
    if(iter == sllist->head)
    {
        sllist->head = iter->next;
    }
    else if (sllist->tail == iter)
    { 
        sllist->tail = prev;
        prev->next=NULL;
    }
    else
    {
        prev->next = iter->next;
    }
    iter->next=NULL;

    return SUCCESS;
}
//OperationResult_t SLinkListModifyToIndex(SLinkList_t* sllist,ModifyFuncPtr_t func, uint32_t modifvalue, uint32_t index);

#ifdef __cplusplus
}
#endif