#include "sort_algorithms.h"

#include <algorithm>
#include <memory.h>
#include <stdlib.h>


void selectionSort(char ** _pData, const int _N)
{
	for (int i = 0; i < _N - 1; i++)
	{
		int lowIndex = i;
		for (int j = i + 1; j < _N; j++)
		if (_stricmp(_pData[j], _pData[lowIndex]) < 0)
			lowIndex = j;

		std::swap(_pData[lowIndex], _pData[i]);
	}
}


void randomShuffle(char ** _pData, int _N)
{
	for (int i = 0; i < _N; i++)
	{
		int j = i + (rand() % (_N - i));
		std::swap(_pData[i], _pData[j]);
	}
}


int partition(char ** _pData, int _low, int _high)
{
	char *pivot = _pData[_low];
	int i = _low, j = _high + 1;

	while (true)
	{
		while (_stricmp(_pData[++i], pivot) < 0)
		if (i == _high)
			break;

		while (_stricmp(pivot, _pData[--j]) < 0)
		if (j == _low)
			break;

		if (i >= j)
			break;

		std::swap(_pData[i], _pData[j]);
	}

	std::swap(_pData[_low], _pData[j]);

	return j;
}


void quickSortInternal(char ** _pData, int _low, int _high)
{
	if (_low >= _high)
		return;

	if ((_high - _low) < 10)
	{
		selectionSort(_pData + _low, (_high - _low + 1));
		return;
	}

	int j = partition(_pData, _low, _high);

	quickSortInternal(_pData, _low, j - 1);
	quickSortInternal(_pData, j + 1, _high);
}


void quickSort(char ** _pData, int _N)
{
	randomShuffle(_pData, _N);
	quickSortInternal(_pData, 0, _N - 1);
}
