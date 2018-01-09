
#include "tree_static.h"
#include <iostream>


int main()
{
	// Создание дерева из 7 узлов
	const int NUM_NODES = 7;
	Tree * pTree = TreeCreate(NUM_NODES);
	char rootnumber = 'A';
	// Инициализация меток узлов
	for (int i = 0; i < NUM_NODES; i++)
	{
		TreeSetLabel(*pTree, i, rootnumber + i);
	}
	
	// Инициализация ребер
	TreeSetParentIndex(*pTree, 1, 0); // B -> A
	TreeSetParentIndex(*pTree, 2, 0); // C -> A
	TreeSetParentIndex(*pTree, 3, 0); // D -> A
	TreeSetParentIndex(*pTree, 4, 1); // E -> B
	TreeSetParentIndex(*pTree, 5, 1); // F -> B
	TreeSetParentIndex(*pTree, 6, 2); // G -> C

	// Обход дерева 3 способами с распечаткой значений:

	// 1) Прямой
	TreeDirectWalk(*pTree, &PrintNodeLabel);
	std::cout << std::endl;

	// 2) Обратный
	TreeReverseWalk(*pTree, &PrintNodeLabel);
	std::cout << std::endl;

	// 3) Симметричный
	TreeSymmetricWalk(*pTree, &PrintNodeLabel);
	std::cout << std::endl;

	// Уничтожение дерева
	TreeDestroy(pTree);
	system("pause");
}
