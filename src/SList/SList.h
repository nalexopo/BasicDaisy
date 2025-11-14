#ifndef SLINKLIST_H
#define SLINKLIST_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include "SharedTypes.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct SLinkListElement
{
  struct SLinkListElement * next;
}SLinkListElement_t;


typedef struct SLinkList
{
  size_t SListSize;
  SLinkListElement_t * head;
  SLinkListElement_t * tail;
}SLinkList_t;


void SLinkListInit(SLinkList_t* sllist);
bool SLinkListIsEmpty(SLinkList_t* sllist);
SLinkListElement_t* SLinkListIteratorGetNext(SLinkListElement_t* element);


OperationResult_t SLinkListAdd(SLinkList_t* sllist, SLinkListElement_t* element);
SLinkListElement_t* SLinkListPop(SLinkList_t* sllist);


OperationResult_t SLinkListInsertToIndex(SLinkList_t* sllist, SLinkListElement_t* element, uint32_t index);
OperationResult_t SLinkListDeleteToIndex(SLinkList_t* sllist, uint32_t index);
SLinkListElement_t* SLinkListReturnIndex(SLinkList_t* sllist, uint32_t index);
//OperationResult_t SLinkListModifyToIndex(SLinkList_t* sllist,ModifyFuncPtr_t func, uint32_t modifvalue, uint32_t index);

#ifdef __cplusplus
}
#endif

#endif //SLINKLIST_H