/**/
#include "tree_static.h"
#include <cassert>
#include <cstring>
#include <iostream>

struct Tree
{
	// Массив меток узлов, тип выбирается в зависимости от задачи
	char * m_pNodeLabels;

	// Количество узлов в дереве
	int m_nNodes;

	// Массив индексов родительских узлов
	int * m_pParentIndices;
	
	// Структура, представляющая элемент связного списка индексов дочерних узлов
	struct ChildIndexElement
	{
		int m_childIndex;
		ChildIndexElement * m_pNext;
	};

		// Заголовок - указатели на первые элементы список дочерних узлов
		ChildIndexElement ** m_pHeader;

};

Tree * TreeCreate(int _nNodes)
{
	// Число узлов должно быть положительным
	assert(_nNodes > 0);

	// Создаем объект-дерево в динамической памяти
	Tree * pTree = new Tree;
	pTree->m_nNodes = _nNodes;

	// Создаем массив меток
	pTree->m_pNodeLabels = new char[_nNodes];
	memset(pTree->m_pNodeLabels, 0, _nNodes);

	// Создаем массив родительских индексов
	pTree->m_pParentIndices = new int[_nNodes];
	memset(pTree->m_pParentIndices, 0, _nNodes * sizeof(int));
	pTree->m_pParentIndices[0] = -1;

	// Создаем массив указателей на списки узлов-сыновей
	pTree->m_pHeader = new Tree::ChildIndexElement *[_nNodes];
	memset(pTree->m_pHeader, 0, sizeof(Tree::ChildIndexElement *) * _nNodes);

	// Возвращаем созданное дерево
	return pTree;
}

void TreeDestroy(Tree * _pTree)
{
	// Уничтожаем метки узлов
	delete[] _pTree->m_pNodeLabels;

	// Уничтожаем массив родительских индексов
	delete[] _pTree->m_pParentIndices;

	// Уничтожаем списки узлов-сыновей
	for (int i = 0; i < _pTree->m_nNodes; i++)
	{
		Tree::ChildIndexElement * pCurrent = _pTree->m_pHeader[i];
		while (pCurrent)
		{
			Tree::ChildIndexElement * pTemp = pCurrent->m_pNext;
			delete pCurrent;
			pCurrent = pTemp;
		}
	}

	// Уничтожаем массив указателей на списки узлов-сыновей
	delete[] _pTree->m_pHeader;

	// Уничтожаем само дерево
	delete _pTree;
	
}

int TreeGetRootIndex(const Tree &)
{
	return 0;
}

TreeNodeLabel TreeGetLabel(const Tree & _tree, int _nodeIndex)
{
	assert(_nodeIndex < _tree.m_nNodes);
	return _tree.m_pNodeLabels[_nodeIndex];
}

void TreeSetLabel(Tree & _tree, int _nodeIndex, TreeNodeLabel _label)
{
	assert(_nodeIndex < _tree.m_nNodes);
	_tree.m_pNodeLabels[_nodeIndex] = _label;
}

int TreeGetParentIndex(const Tree & _tree, int _nodeIndex) // массив родительских индексов
{
	assert(_nodeIndex < _tree.m_nNodes);
	return _tree.m_pParentIndices[_nodeIndex];
}
///////////////////////////////////////////////////////////////////////


void TreeSetParentIndex(Tree & _tree, int _nodeIndex, int _parentIndex) // комбинированно 
{
	assert(_nodeIndex < _tree.m_nNodes);
	assert(_parentIndex < _nodeIndex);

	_tree.m_pParentIndices[_nodeIndex] = _parentIndex;


	Tree::ChildIndexElement * pNewElement = new Tree::ChildIndexElement;
	pNewElement->m_childIndex = _nodeIndex;
	pNewElement->m_pNext = nullptr;

	Tree::ChildIndexElement * pCurrent = _tree.m_pHeader[_parentIndex];
	if (!pCurrent)
	{
		_tree.m_pHeader[_parentIndex] = pNewElement;
		return;
	}


	while (pCurrent->m_pNext)
		pCurrent = pCurrent->m_pNext;

	pCurrent->m_pNext = pNewElement;

	

}

int TreeGetLeftmostChildIndex(const Tree & _tree, int _nodeIndex) // со списками дочерних узлов
{
	assert(_nodeIndex < _tree.m_nNodes);

	Tree::ChildIndexElement * pCurrent = _tree.m_pHeader[_nodeIndex];
	return pCurrent ? pCurrent->m_childIndex : -1;
}

int TreeGetRightSiblingIndex(const Tree & _tree, int _nodeIndex) // со списками дочерних узлов 
{
	// Проверяем корректность индекса
	assert(_nodeIndex < _tree.m_nNodes);

	// Ищем родительский узел, перебирая все списки сыновей
	for (int i = 0; i < _nodeIndex; i++)
	{
		Tree::ChildIndexElement * pCurrent = _tree.m_pHeader[i];
		while (pCurrent)
		{
			if (pCurrent->m_childIndex == _nodeIndex)
			{
				// Искомый узел найден, соответственно, это был список узла-родителя.
				// Следующий узел-сын известен по непосредственной структурной связи
				Tree::ChildIndexElement * pNext = pCurrent->m_pNext;
				return pNext ? pNext->m_childIndex : -1;
			}
			pCurrent = pCurrent->m_pNext;
		}
	}

	// Братский узел не найден
	return -1;

}

// Прямой обход дерева, начиная с конкретного узла
void TreeDirectWalk(const Tree & _tree, int _nodeIndex, TreeNodeVisitFunction _f)
{
	// Посещаем начальный узел
	(*_f)(_tree, _nodeIndex);

	// Рекурсивно вызываем обход для каждого дочернего узла
	int childIndex = TreeGetLeftmostChildIndex(_tree, _nodeIndex);
	while (childIndex != -1)
	{
		TreeDirectWalk(_tree, childIndex, _f);
		childIndex = TreeGetRightSiblingIndex(_tree, childIndex);
	}
}

// Обратный обход дерева, начиная с конкретного узла
void TreeReverseWalk(const Tree & _tree, int _nodeIndex, TreeNodeVisitFunction _f)
{
	// Рекурсивно вызываем обход для каждого дочернего узла
	int childIndex = TreeGetLeftmostChildIndex(_tree, _nodeIndex);
	while (childIndex != -1)
	{
		TreeReverseWalk(_tree, childIndex, _f);
		childIndex = TreeGetRightSiblingIndex(_tree, childIndex);
	}

	// В конце посещаем узел-родитель
	(*_f)(_tree, _nodeIndex);
}

// Симметричный обход дерева, начиная с конкретного узла
void TreeSymmetricWalk(const Tree & _tree, int _nodeIndex, TreeNodeVisitFunction _f)
{
	// Рекурсивно посещаем самый левый дочерний узел, если такой имеется
	int childIndex = TreeGetLeftmostChildIndex(_tree, _nodeIndex);
	if (childIndex != -1)
		TreeSymmetricWalk(_tree, childIndex, _f);

	// Посещаем узел-родитель
	(*_f)(_tree, _nodeIndex);

	// Без дочерних узлов дальше двигаться не куда
	if (childIndex == -1)
		return;

	// Рекурсивно посещаем каждый следующий дочерний узел
	while (true)
	{
		childIndex = TreeGetRightSiblingIndex(_tree, childIndex);
		if (childIndex == -1)
			break;

		TreeSymmetricWalk(_tree, childIndex, _f);
	}
}

// Прямой обход дерева, начиная с корня
void TreeDirectWalk(const Tree & _tree, TreeNodeVisitFunction _f)
{
	TreeDirectWalk(_tree, TreeGetRootIndex(_tree), _f);
}

// Обратный обход дерева, начиная с корня
void TreeReverseWalk(const Tree & _tree, TreeNodeVisitFunction _f)
{
	TreeReverseWalk(_tree, TreeGetRootIndex(_tree), _f);
}

// Симметричный обход дерева, начиная с корня
void TreeSymmetricWalk(const Tree & _tree, TreeNodeVisitFunction _f)
{
	TreeSymmetricWalk(_tree, TreeGetRootIndex(_tree), _f);
}

void PrintNodeLabel(const Tree & _t, int _nodeIndex)
{
	std::cout << TreeGetLabel(_t, _nodeIndex) << ' ';
}
