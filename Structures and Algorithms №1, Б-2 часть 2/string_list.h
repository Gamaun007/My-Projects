#ifndef _INTEGER_LIST_HPP_
#define _INTEGER_LIST_HPP_
#include <cstring>
#include <iostream>

struct StringList
{
	struct Node
	{
		const char * m_value;

		Node * m_pNext;
	};

	Node * m_pFirst, *m_pLast;
};


void StringListInit(StringList & _list);

void StringListPushBack(StringList & _list,char *_data);

void StringListDestroy(StringList & _list);

void StringListClear(StringList & _list);

char * CStringElementCopy(const char * _data);

void StringListDeleteNode(StringList & _list, StringList::Node * _pNode);

void StringListDeleteBefore(StringList & _list, StringList::Node * _pNextNode);

void StringListDeleteAfter(StringList & _list, StringList::Node * _pPrevNode);

void StringListPopBack(StringList & _list);

void StringListPopFront(StringList & _list);

void StringListInsertBefore(StringList & _list, StringList::Node * _pNextNode, char* _data);

void StringListInsertAfter(StringList & _list, StringList::Node * _pPrevNode, char* _data);

void StringListPushFront(StringList & _list, char* _data);

int StringListSize(const StringList & _list);

bool StringListIsEmpty(const StringList & _list);

#endif //  _INTEGER_FORWARD_LIST_HPP;