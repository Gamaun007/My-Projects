#include "string_list.h"
#include <cassert>
#include <cstring>
void StringListInit(StringList & _list)
{
	_list.m_pFirst = _list.m_pLast = nullptr;
}


void StringListDestroy(StringList & _list)
{
	StringListClear(_list);
}


void StringListClear(StringList & _list)
{
	StringList::Node * pCurrent = _list.m_pFirst;
	while (pCurrent)
	{
		StringList::Node * pTemp = pCurrent->m_pNext;
		delete pCurrent;
		pCurrent = pTemp;
	}

	_list.m_pFirst = _list.m_pLast = nullptr;
}


void StringListPushBack(StringList & _list, char *_data)
{
	StringList::Node * pNewNode = new StringList::Node;
	pNewNode->m_value = CStringElementCopy(_data);
	pNewNode->m_pNext = nullptr;
	if (!_list.m_pFirst)
	{
		assert(!_list.m_pLast);
		_list.m_pFirst = pNewNode;
	}
	else
		_list.m_pLast->m_pNext = pNewNode;

	_list.m_pLast = pNewNode;
	
}
char * CStringElementCopy(const char * _data)
{
	int length = strlen(_data);

	char * pResult = new char[length + 1];

	strcpy(pResult, _data);

	// Возвращаем адрес выделенного блока с заполненной строкой
	return pResult;
	delete[] pResult;
}

void StringListDeleteNode(StringList & _list, StringList::Node * _pNode)
{
	if (_list.m_pFirst == _pNode)
		StringListPopFront(_list);

	else if (_list.m_pLast == _pNode)
		StringListPopBack(_list);

	else
		StringListDeleteBefore(_list, _pNode->m_pNext);
}

void StringListDeleteBefore(StringList & _list, StringList::Node * _pNextNode)
{
	assert(!StringListIsEmpty(_list));

	assert(_list.m_pFirst != _pNextNode);

	StringList::Node * pPrevNode = _list.m_pFirst, *pCurrentNode = _list.m_pFirst->m_pNext;
	if (pCurrentNode == _pNextNode)
	{
		delete _list.m_pFirst;
		_list.m_pFirst = _pNextNode;
	}

	else
	{
		while (pCurrentNode->m_pNext != _pNextNode)
		{
			pPrevNode = pCurrentNode;
			pCurrentNode = pCurrentNode->m_pNext;
		}

		pPrevNode->m_pNext = _pNextNode;
		delete pCurrentNode;
	}
}

void StringListDeleteAfter(StringList & _list, StringList::Node * _pPrevNode)
{
	assert(!StringListIsEmpty(_list));

	assert(_list.m_pLast != _pPrevNode);

	StringList::Node * pDyingNode = _pPrevNode->m_pNext;
	_pPrevNode->m_pNext = pDyingNode->m_pNext;

	if (_list.m_pLast == pDyingNode)
		_list.m_pLast = _pPrevNode;

	delete pDyingNode;
}

void StringListPopBack(StringList & _list)
{
	assert(!StringListIsEmpty(_list));

	StringList::Node * pLast = _list.m_pLast;

	if (_list.m_pFirst == _list.m_pLast)
		_list.m_pFirst = _list.m_pLast = nullptr;

	else
	{
		StringList::Node * pCurrent = _list.m_pFirst;
		while (pCurrent->m_pNext != _list.m_pLast)
			pCurrent = pCurrent->m_pNext;

		_list.m_pLast = pCurrent;
		pCurrent->m_pNext = nullptr;
	}

	delete pLast;
}

void StringListPopFront(StringList & _list)
{
	assert(!StringListIsEmpty(_list));

	StringList::Node * pFirst = _list.m_pFirst;

	if (_list.m_pFirst == _list.m_pLast)
		_list.m_pFirst = _list.m_pLast = nullptr;

	else
		_list.m_pFirst = pFirst->m_pNext;

	delete pFirst;
}


void StringListInsertBefore(StringList & _list, StringList::Node * _pNextNode, char * _data)
{
	assert(!StringListIsEmpty(_list));

	if (_pNextNode == _list.m_pFirst)
		StringListPushFront(_list, _data);

	else
	{
		StringList::Node * pCurrent = _list.m_pFirst;
		while (pCurrent && pCurrent->m_pNext != _pNextNode)
			pCurrent = pCurrent->m_pNext;

		assert(pCurrent);

		StringList::Node * pNewNode = new StringList::Node;
		pNewNode->m_value = CStringElementCopy(_data);

		pNewNode->m_pNext = _pNextNode;

		pCurrent->m_pNext = pNewNode;

	}
}

void StringListInsertAfter(StringList & _list, StringList::Node * _pPrevNode, char * _data)
{
	assert(!StringListIsEmpty(_list));

	if (_pPrevNode == _list.m_pLast)
		StringListPushBack(_list, _data);

	else
	{
		StringList::Node * pNewNode = new StringList::Node;
		pNewNode->m_value = _data;

		pNewNode->m_pNext = _pPrevNode->m_pNext;

		_pPrevNode->m_pNext = pNewNode;
	}
}

void StringListPushFront(StringList & _list, char * _data)
{
	StringList::Node * pNewNode = new StringList::Node;
	pNewNode->m_value = _data;
	pNewNode->m_pNext = _list.m_pFirst;

	_list.m_pFirst = pNewNode;

	if (!_list.m_pLast)
		_list.m_pLast = pNewNode;
}

int StringListSize(const StringList & _list)
{
	int nElements = 0;
	const StringList::Node * pNode = _list.m_pFirst;
	while (pNode)
	{
		++nElements;
		pNode = pNode->m_pNext;
	}

	return nElements;
}

bool StringListIsEmpty(const StringList & _list)
{
	return _list.m_pFirst == nullptr;
}

