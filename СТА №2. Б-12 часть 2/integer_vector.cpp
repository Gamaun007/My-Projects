#define _CRT_SECURE_NO_WARNINGS
#include "integer_vector.h"
#include <fstream>
#include <cstring>
#include <iostream>
#include <cassert>


void IntegerVectorInit(IntegerVector & _vector, int _allocatedSize)
{
	_vector.m_pData = new char*[_allocatedSize];
	_vector.m_nAllocated = _allocatedSize;
	_vector.m_nUsed = 0;
}


void IntegerVectorDestroy(IntegerVector & _vector)
{
	for (int i = 0; i < _vector.m_nUsed; i++)
	{
		delete[] _vector.m_pData[i];
	}
	delete[] _vector.m_pData;

}


void IntegerVectorClear(IntegerVector & _vector)
{
	_vector.m_nUsed = 0;
}


bool IntegerVectorIsEmpty(const IntegerVector & _vector)
{
	return _vector.m_nUsed == 0;
}


void IntegerVectorGrow(IntegerVector & _vector,char *_data)
{
	int nAllocatedNew = _vector.m_nAllocated * 2;
	char ** pNewData = new char*[nAllocatedNew];
	for (int i = 0; i < nAllocatedNew; i++)
	{
		pNewData[i] = new char[50];
	}
	for (int i = 0; i < _vector.m_nAllocated; i++)
	{
		pNewData[i] = CStringElementCopy(_data);
	}

//	memcpy(pNewData, _vector.m_pData, sizeof(int)* _vector.m_nAllocated);
	for (int i = 0; i < _vector.m_nAllocated; i++)
	{
		delete[] _vector.m_pData[i];
	}
	delete[] _vector.m_pData;
	_vector.m_pData = pNewData;

	_vector.m_nAllocated = nAllocatedNew;
}


void IntegerVectorPushBack(IntegerVector & _vector, char *_data)
{
	if (_vector.m_nUsed == _vector.m_nAllocated)
	{
		IntegerVectorGrow(_vector,_data);
	}
		

	_vector.m_pData[_vector.m_nUsed++] = CStringElementCopy(_data);
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

void IntegerVectorPopBack(IntegerVector & _vector)
{
	assert(!IntegerVectorIsEmpty(_vector));

	--_vector.m_nUsed;
}


void IntegerVectorRead(IntegerVector & _vector, std::istream & _stream)
{
	std::ifstream textfile("lab2chast2.txt");
	while (!textfile.eof())
	{
		char temp[50];
		textfile >> temp;
		IntegerVectorPushBack(_vector, temp);
		temp[0] = '/0';
		
	}
	textfile.close();
}


void IntegerVectorReadTillZero(IntegerVector & _vector, std::istream & _stream)
{
	while (true)
	{
		char temp[50];
		_stream >> temp;
		if (_stream && temp != 0)
			IntegerVectorPushBack(_vector, temp);
		else
			break;
	}
}


void IntegerVectorPrint(const IntegerVector & _vector, std::ostream & _stream, char _sep)
{
	for (int i = 0; i < _vector.m_nUsed; i++)
		_stream << _vector.m_pData[i] << _sep;
	std::cout << std::endl;
}


void IntegerVectorInsertAt(IntegerVector & _vector, int _position, char * _data)
{
	assert(_position >= 0 && _position < _vector.m_nUsed);

	int newUsed = _vector.m_nUsed + 1;
	if (newUsed > _vector.m_nAllocated)
		IntegerVectorGrow(_vector,_data);

	for (int i = _vector.m_nUsed; i > _position; i--)
		_vector.m_pData[i] = _vector.m_pData[i - 1];

	strncpy(_vector.m_pData[_position], _data, 50);

	_vector.m_nUsed = newUsed;
}


void IntegerVectorDeleteAt(IntegerVector & _vector, int _position)
{
	assert(_position >= 0 && _position < _vector.m_nUsed);

	for (int i = _position + 1; i < _vector.m_nUsed; i++)
		_vector.m_pData[i - 1] = _vector.m_pData[i];

	--_vector.m_nUsed;
}