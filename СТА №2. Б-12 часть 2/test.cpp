#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <iostream>
#include "integer_vector.h"
#include "sort_algorithms.h"

int main()
{
	IntegerVector Text;
	IntegerVectorInit(Text,20);
	IntegerVectorRead(Text, std::cin);
	IntegerVectorPrint(Text, std::cout);
	quickSort(Text.m_pData, Text.m_nUsed);
	IntegerVectorPrint(Text, std::cout);
	IntegerVectorDestroy(Text);

	system("pause");
	return 0;
}