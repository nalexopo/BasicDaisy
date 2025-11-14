#include <gtest/gtest.h>
#include "SList.h"
#include <iostream>

using namespace std;


namespace
{

class SLinkListTest : public testing::Test {
 protected: 
  void SetUp() override {

  }
  
  void TearDown() override{

  }
  
};


TEST_F(SLinkListTest, A_Test) 
{

  SLinkListElement_t element,element1,element2,element3;
  SLinkList_t list;
  SLinkListInit(&list);

  EXPECT_EQ(list.head,(void*)NULL);
  EXPECT_EQ(list.tail,(void*)NULL);
  EXPECT_EQ(list.SListSize,0);

  EXPECT_TRUE(SLinkListIsEmpty(&list));

  SLinkListAdd(&list, &element);

  EXPECT_EQ(list.SListSize,1);

  EXPECT_FALSE(SLinkListIsEmpty(&list));

  EXPECT_EQ(list.head,&element);
  EXPECT_EQ(list.tail,&element);

  SLinkListAdd(&list, &element1);

  EXPECT_EQ(list.SListSize,2);

  EXPECT_EQ(list.head,&element);
  EXPECT_EQ(list.tail,&element1);

  
  EXPECT_EQ(element.next,&element1);
  EXPECT_EQ(element1.next,(void*)NULL);
  
  SLinkListAdd(&list, &element2);

  EXPECT_EQ(list.SListSize,3);

  EXPECT_EQ(list.head,&element);
  EXPECT_EQ(list.tail,&element2);
  
  EXPECT_EQ(element.next,&element1);

  EXPECT_EQ(element1.next,&element2);

  EXPECT_EQ(element2.next,(void*)NULL);

  SLinkListAdd(&list, &element3);

  EXPECT_EQ(list.SListSize,4);

  EXPECT_EQ(list.head,&element);
  EXPECT_EQ(list.tail,&element3);
  
  EXPECT_EQ(element.next,&element1);

  EXPECT_EQ(element1.next,&element2);

  EXPECT_EQ(element2.next,&element3);

  EXPECT_EQ(element3.next,(void*)NULL);

}

TEST_F(SLinkListTest, B_Test) 
{
  SLinkListElement_t element,element1,element2,element3;
  SLinkList_t list;
  SLinkListInit(&list);

  EXPECT_EQ(SLinkListPop(&list), (void*)NULL);

  SLinkListAdd(&list, &element);
  SLinkListAdd(&list, &element1);
  SLinkListAdd(&list, &element2);
  SLinkListAdd(&list, &element3);

  EXPECT_EQ(list.SListSize,4);

  EXPECT_EQ(SLinkListPop(&list), &element);
  
  EXPECT_EQ(list.SListSize,3);

  EXPECT_EQ(list.head,&element1);
  EXPECT_EQ(list.tail,&element3);


  EXPECT_EQ(element1.next,&element2);

  EXPECT_EQ(element2.next,&element3);

  EXPECT_EQ(element3.next,(void*)NULL);
  
  EXPECT_EQ(SLinkListPop(&list), &element1);
  
  EXPECT_EQ(list.SListSize,2);

  EXPECT_EQ(list.head,&element2);
  EXPECT_EQ(list.tail,&element3);

  EXPECT_EQ(element2.next,&element3);

  EXPECT_EQ(element3.next,(void*)NULL);

  EXPECT_EQ(SLinkListPop(&list), &element2);

  EXPECT_EQ(list.SListSize,1);

  EXPECT_EQ(list.head,&element3);
  EXPECT_EQ(list.tail,&element3);

  EXPECT_EQ(element3.next,(void*)NULL);

  EXPECT_EQ(SLinkListPop(&list), &element3);

  EXPECT_EQ(list.SListSize,0);

  EXPECT_EQ(list.head,(void*)NULL);
  EXPECT_EQ(list.tail,(void*)NULL);


}


TEST_F(SLinkListTest, C_Test) 
{
  SLinkListElement_t element, element1, element2, element3;
  SLinkListElement_t element4, element5, element6, element7;
  SLinkList_t list;
  SLinkListInit(&list);


  //equal to SLinkListAdd(&list, &element);
  EXPECT_EQ(SLinkListInsertToIndex(&list, &element,0),SUCCESS);
  
  SLinkListAdd(&list, &element1);
  SLinkListAdd(&list, &element2);
  SLinkListAdd(&list, &element3);

  EXPECT_EQ(SLinkListIteratorGetNext(&element),&element1);
  EXPECT_EQ(SLinkListIteratorGetNext(&element1),&element2);
  EXPECT_EQ(SLinkListIteratorGetNext(&element2),&element3);
  EXPECT_EQ(SLinkListIteratorGetNext(&element3),(void*)NULL);

  EXPECT_EQ(SLinkListInsertToIndex(&list, &element4,4),SUCCESS);

  EXPECT_EQ(list.SListSize,5);
    
  EXPECT_EQ(list.head,&element);
  EXPECT_EQ(list.tail,&element4);
  
  EXPECT_EQ(element.next,&element1);

  EXPECT_EQ(element1.next,&element2);

  EXPECT_EQ(element2.next,&element3);

  EXPECT_EQ(element3.next,&element4);

  EXPECT_EQ(element4.next,(void*)NULL); 

  EXPECT_EQ(SLinkListInsertToIndex(&list, &element5,0),SUCCESS);

  EXPECT_EQ(list.SListSize,6);
    
  EXPECT_EQ(list.head,&element5);
  EXPECT_EQ(list.tail,&element4);

  EXPECT_EQ(element5.next,&element);
  
  EXPECT_EQ(element.next,&element1);

  EXPECT_EQ(element1.next,&element2);

  EXPECT_EQ(element2.next,&element3);

  EXPECT_EQ(element3.next,&element4);

  EXPECT_EQ(element4.next,(void*)NULL);

  EXPECT_EQ(SLinkListInsertToIndex(&list, &element6,2),SUCCESS);

  EXPECT_EQ(list.SListSize,7);
    
  EXPECT_EQ(list.head,&element5);
  EXPECT_EQ(list.tail,&element4);

  EXPECT_EQ(element5.next,&element);
  
  EXPECT_EQ(element.next,&element6);
  
  EXPECT_EQ(element6.next,&element1);

  EXPECT_EQ(element1.next,&element2);

  EXPECT_EQ(element2.next,&element3);

  EXPECT_EQ(element3.next,&element4);

  EXPECT_EQ(element4.next,(void*)NULL);

  EXPECT_EQ(SLinkListInsertToIndex(&list, &element7,8),FAIL);

  EXPECT_EQ(list.SListSize,7);
  
  EXPECT_EQ(SLinkListInsertToIndex(&list, &element7,6),SUCCESS);

  EXPECT_EQ(list.SListSize,8);
    
  EXPECT_EQ(list.head,&element5);
  EXPECT_EQ(list.tail,&element4);

  EXPECT_EQ(element5.next,&element);
  
  EXPECT_EQ(element.next,&element6);
  
  EXPECT_EQ(element6.next,&element1);

  EXPECT_EQ(element1.next,&element2);

  EXPECT_EQ(element2.next,&element3);

  EXPECT_EQ(element3.next,&element7);

  EXPECT_EQ(element7.next,&element4);

  EXPECT_EQ(element4.next,(void*)NULL);

}


TEST_F(SLinkListTest, D_Test) 
{
  SLinkListElement_t element, element1, element2, element3;
  SLinkListElement_t element4, element5, element6, element7;
  SLinkList_t list;
  SLinkListInit(&list);

  SLinkListAdd(&list, &element);
  SLinkListAdd(&list, &element1);
  SLinkListAdd(&list, &element2);
  SLinkListAdd(&list, &element3);
  SLinkListAdd(&list, &element4);
  SLinkListAdd(&list, &element5);
  SLinkListAdd(&list, &element6);
  SLinkListAdd(&list, &element7);

  EXPECT_EQ(list.SListSize,8);

  EXPECT_EQ(SLinkListReturnIndex(&list,0), &element);
  EXPECT_EQ(SLinkListReturnIndex(&list,1), &element1);
  EXPECT_EQ(SLinkListReturnIndex(&list,2), &element2);
  EXPECT_EQ(SLinkListReturnIndex(&list,3), &element3);
  EXPECT_EQ(SLinkListReturnIndex(&list,4), &element4);
  EXPECT_EQ(SLinkListReturnIndex(&list,5), &element5);
  EXPECT_EQ(SLinkListReturnIndex(&list,6), &element6);
  EXPECT_EQ(SLinkListReturnIndex(&list,7), &element7);

  EXPECT_EQ(SLinkListReturnIndex(&list,8), (void*)NULL);
  EXPECT_EQ(SLinkListReturnIndex(&list,9), (void*)NULL);
    


}

// TEST_F(SLinkListTest, E_Test) 
// {

//   SLinkListElement_t element, element1, element2, element3;
//   SLinkListElement_t element4, element5, element6, element7;
//   SLinkList_t list;

//   SLinkListInit(&list);


//   SLinkListAdd(&list, &element);
//   SLinkListAdd(&list, &element1);
//   SLinkListAdd(&list, &element2);
//   SLinkListAdd(&list, &element3);
//   SLinkListAdd(&list, &element4);
//   SLinkListAdd(&list, &element5);
//   SLinkListAdd(&list, &element6);
//   SLinkListAdd(&list, &element7);

//   EXPECT_EQ(list.SListSize,8);

//   EXPECT_EQ(SLinkListDeleteToIndex(&list, 1), SUCCESS);

//   EXPECT_EQ(list.SListSize,7);
  

//   EXPECT_EQ(list.head,&element);
//   EXPECT_EQ(list.tail,&element7);
  
  
//   EXPECT_EQ(element.next,&element2);


//   EXPECT_EQ(element2.next,&element3);

//   EXPECT_EQ(element3.next,&element4);

//   EXPECT_EQ(element4.next,&element5);

//   EXPECT_EQ(element5.next,&element6);

//   EXPECT_EQ(element6.next,&element7);

//   EXPECT_EQ(element7.next,(void*)NULL);

//   EXPECT_EQ(SLinkListDeleteToIndex(&list, 1), SUCCESS);

//   EXPECT_EQ(list.SListSize,6);

//   EXPECT_EQ(list.head,&element);
//   EXPECT_EQ(list.tail,&element7);
  
  
//   EXPECT_EQ(element.next,&element3);

//   EXPECT_EQ(element3.next,&element4);

//   EXPECT_EQ(element4.next,&element5);

//   EXPECT_EQ(element5.next,&element6);

//   EXPECT_EQ(element6.next,&element7);

//   EXPECT_EQ(element7.next,(void*)NULL);

//   EXPECT_EQ(SLinkListDeleteToIndex(&list, 4), SUCCESS);

//   EXPECT_EQ(list.SListSize,5);

//   EXPECT_EQ(list.head,&element);
//   EXPECT_EQ(list.tail,&element7);
  
  
//   EXPECT_EQ(element.next,&element3);

//   EXPECT_EQ(element3.next,&element4);

//   EXPECT_EQ(element4.next,&element5);

//   EXPECT_EQ(element5.next,&element7);

//   EXPECT_EQ(element7.next,(void*)NULL);

//   EXPECT_EQ(SLinkListDeleteToIndex(&list, 4), SUCCESS);

//   EXPECT_EQ(list.SListSize,4);

//   EXPECT_EQ(list.head,&element);
//   EXPECT_EQ(list.tail,&element5);
  
  
//   EXPECT_EQ(element.next,&element3);

//   EXPECT_EQ(element3.next,&element4);


//   EXPECT_EQ(element4.next,&element5);

//   EXPECT_EQ(element5.next,(void*)NULL);


//   EXPECT_EQ(SLinkListDeleteToIndex(&list, 0), SUCCESS);

//   EXPECT_EQ(list.SListSize,3);

//   EXPECT_EQ(list.head,&element3);
//   EXPECT_EQ(list.tail,&element5);
  

//   EXPECT_EQ(element3.next,&element4);

//   EXPECT_EQ(element4.next,&element5);

//   EXPECT_EQ(element5.next,(void*)NULL);

//   EXPECT_EQ(SLinkListDeleteToIndex(&list, 0), SUCCESS);

//   EXPECT_EQ(list.SListSize,2);

//   EXPECT_EQ(list.head,&element4);
//   EXPECT_EQ(list.tail,&element5);

//   EXPECT_EQ(element4.next,&element5);

 
//   EXPECT_EQ(element5.next,(void*)NULL);

//   EXPECT_EQ(SLinkListDeleteToIndex(&list, 0), SUCCESS);

//   EXPECT_EQ(list.SListSize,1);

//   EXPECT_EQ(list.head,&element5);
//   EXPECT_EQ(list.tail,&element5);

//   EXPECT_EQ(element5.next,(void*)NULL);

//   EXPECT_EQ(SLinkListDeleteToIndex(&list, 0), SUCCESS);


//   EXPECT_EQ(list.head,(void*)NULL);
//   EXPECT_EQ(list.tail,(void*)NULL);

//   EXPECT_EQ(SLinkListDeleteToIndex(&list, 0), FAIL);

// }


}