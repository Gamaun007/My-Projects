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

void IntegerVectorDestroy(IntegerVector & _vector);

void IntegerVectorClear(IntegerVector & _vector);

bool IntegerVectorIsEmpty(const IntegerVector & _vector);

void IntegerVectorPushBack(IntegerVector & _vector);

void IntegerVectorPopBack(IntegerVector & _vector);

void IntegerVectorInsertAt(IntegerVector & _vector, int _position, int _data);

void IntegerVectorDeleteAt(IntegerVector & _vector, int _position);

void IntegerVectorRead(IntegerVector & _vector, std::istream & _stream);

void IntegerVectorReadTillZero(IntegerVector & _vector, std::istream & _stream);

void IntegerVectorPrint(const IntegerVector & _vector, std::ostream & _stream, char _sep = ' ');

void IntegerVectorFill(IntegerVector & _vector, int _data);

void EnterTheCommand(IntegerVector & _vector, std::istream &_stream,int _data);

void FunctionCommandS(IntegerVector & _vector);

void FunctionCommandE(IntegerVector & _vector);

void FunctionCommandI(IntegerVector & _vector, int _data);

void FunctionCommandU(IntegerVector & _vector, int _data);

void FunctionCommandZ(IntegerVector & _vector, int _data);

void FunctionCommandQ(IntegerVector & _vector);

#endif //  _INTEGER_VECTOR_HPP_