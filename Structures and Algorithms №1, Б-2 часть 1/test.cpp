#include "integer_vector.h"

int main()
{
	// ������� � �������������� ������
	IntegerVector v;
	IntegerVector p;
	IntegerVectorInit(v);
		IntegerVectorInit(p);


	// ������ ����� �� ����� 0
	std::cout << "Input integers, stop with zero: ";
	IntegerVectorReadTillZero(v, std::cin);

	// ������ �������, ������� ��������� ������� �� �����
	std::cout << "Input position of value,stop with Ctrl+Z (Enter): ";
	IntegerPosRead(v,p, std::cin);
	// ������� ������� ������� �������
	IntegerPosPrint(v,p,std::cout);
	// ����������� ������
	IntegerVectorDestroy(v,p);
	system("pause");
}
