#include "integer_vector.h"

int main()
{
	// Создаем и инициализируем вектор
	IntegerVector v;
	IntegerVector p;
	IntegerVectorInit(v);
		IntegerVectorInit(p);


	// Вводим числа до ввода 0
	std::cout << "Input integers, stop with zero: ";
	IntegerVectorReadTillZero(v, std::cin);

	// Вводим позицию, которую требуется вывести на экран
	std::cout << "Input position of value,stop with Ctrl+Z (Enter): ";
	IntegerPosRead(v,p, std::cin);
	// Выводим позиции первого вектора
	IntegerPosPrint(v,p,std::cout);
	// Освобождаем память
	IntegerVectorDestroy(v,p);
	system("pause");
}
