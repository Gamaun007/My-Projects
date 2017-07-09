#ifndef _INTEGER_VECTOR_HPP_
#define _INTEGER_VECTOR_HPP_

#include <iostream>


struct IntegerVector
{
	int * m_pData;
	int m_nUsed;
	int m_nAllocated;
};


void IntegerVectorInit(IntegerVector & _vector, int _allocatedSize = 10);

void IntegerVectorDestroy(IntegerVector & _vector, IntegerVector & _position);

void IntegerVectorPushBack(IntegerVector & _vector, int _data);

void IntegerVectorRead(IntegerVector & _vector, std::istream & _stream);

void IntegerVectorReadTillZero(IntegerVector & _vector, std::istream & _stream);

void IntegerPosPrint(const IntegerVector & _vector, const IntegerVector & _position, std::ostream & _stream, char _sep = ' ');

bool IntegerVectorIsEmpty(const IntegerVector & _vector);

void IntegerPosRead(IntegerVector & _vector, IntegerVector & _position, std::istream & _stream);

#endif //  _INTEGER_VECTOR_HPP_
