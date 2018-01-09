#include "integer_vector.h"

#include <cstring>
#include <iostream>
#include <cassert>


void IntegerVectorInit(IntegerVector & _vector, int _allocatedSize)
{
	_vector.m_pData = new int[_allocatedSize];
	_vector.m_nAllocated = _allocatedSize;
	_vector.m_nUsed = 0;
}


void IntegerVectorDestroy(IntegerVector & _vector, IntegerVector & _position)
{
	delete[] _vector.m_pData;
}


void IntegerVectorGrow(IntegerVector & _vector)
{
	int nAllocatedNew = _vector.m_nAllocated * 2;
	int * pNewData = new int[nAllocatedNew];

	memcpy(pNewData, _vector.m_pData, sizeof(int)* _vector.m_nAllocated);

	delete[] _vector.m_pData;
	_vector.m_pData = pNewData;

	_vector.m_nAllocated = nAllocatedNew;
}


void IntegerVectorPushBack(IntegerVector & _vector, int _data)
{
	if (_vector.m_nUsed == _vector.m_nAllocated)
		IntegerVectorGrow(_vector);

	_vector.m_pData[_vector.m_nUsed++] = _data;
}



void IntegerVectorPopBack(IntegerVector & _vector)
{
	assert(!IntegerVectorIsEmpty(_vector));

	--_vector.m_nUsed;
}


void IntegerVectorRead(IntegerVector & _vector, std::istream & _stream)
{
	while (true)
	{
		int temp;
		_stream >> temp;
		if (_stream)
			IntegerVectorPushBack(_vector, temp);
		else
			break;
	}
}


void IntegerVectorReadTillZero(IntegerVector & _vector, std::istream & _stream)
{
	while (true)
	{
		int temp;
		_stream >> temp;
		if (_stream && temp > 0)
			IntegerVectorPushBack(_vector, temp);
		else
			break;
	}
}


void IntegerPosPrint(const IntegerVector & _vector, const IntegerVector & _position, std::ostream & _stream, char _sep)
{
	int temp = 0;
	for (int i = 0; i < _position.m_nUsed; i++)
	{
		temp = _position.m_pData[i];
		_stream << _vector.m_pData[temp] << _sep;
	}
}


void IntegerPosRead(IntegerVector & _vector,IntegerVector & _position, std::istream & _stream)
{
	bool flag = true;
	
	while (flag)
	{
		
			int position;
			_stream >> position;
			if (!_stream)
			{
				flag = false;
				break;
			}
			else
			{
			if (position < 0 || position >= _vector.m_nUsed)
			{
				std::cout << "Error: last position were invalid." << std::endl;
				continue;
			}

			else

			if (_stream)
				IntegerVectorPushBack(_position, position);
			else
				break;
		}		
	}
}


bool IntegerVectorIsEmpty(const IntegerVector & _vector)
{
	return _vector.m_nUsed == 0;
}
