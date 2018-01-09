
#include "tree_static.h"
#include <iostream>


int main()
{
	// �������� ������ �� 7 �����
	const int NUM_NODES = 7;
	Tree * pTree = TreeCreate(NUM_NODES);
	char rootnumber = 'A';
	// ������������� ����� �����
	for (int i = 0; i < NUM_NODES; i++)
	{
		TreeSetLabel(*pTree, i, rootnumber + i);
	}
	
	// ������������� �����
	TreeSetParentIndex(*pTree, 1, 0); // B -> A
	TreeSetParentIndex(*pTree, 2, 0); // C -> A
	TreeSetParentIndex(*pTree, 3, 0); // D -> A
	TreeSetParentIndex(*pTree, 4, 1); // E -> B
	TreeSetParentIndex(*pTree, 5, 1); // F -> B
	TreeSetParentIndex(*pTree, 6, 2); // G -> C

	// ����� ������ 3 ��������� � ����������� ��������:

	// 1) ������
	TreeDirectWalk(*pTree, &PrintNodeLabel);
	std::cout << std::endl;

	// 2) ��������
	TreeReverseWalk(*pTree, &PrintNodeLabel);
	std::cout << std::endl;

	// 3) ������������
	TreeSymmetricWalk(*pTree, &PrintNodeLabel);
	std::cout << std::endl;

	// ����������� ������
	TreeDestroy(pTree);
	system("pause");
}
