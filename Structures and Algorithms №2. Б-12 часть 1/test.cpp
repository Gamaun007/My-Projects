#include <iostream>
#include "integer_vector.h"
int main()
{
	IntegerVector Girls;
	int amount = 0;
	std::cout << "Enter the amount of girls" << std::endl;
	std::cin >> amount;
	IntegerVectorInit(Girls, amount);
	IntegerVectorFill(Girls, amount);
	EnterTheCommand(Girls, std::cin,amount);
	IntegerVectorDestroy(Girls);
	system("pause");
	return 0;
}