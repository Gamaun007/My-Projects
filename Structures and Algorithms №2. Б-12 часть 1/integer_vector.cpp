#include "integer_vector.h"

#include <cstring>
#include <iostream>
#include <cassert>


void IntegerVectorInit(IntegerVector & _vector, int _allocatedSize)
{
	_vector.m_pData = new int[_allocatedSize];
	_vector.m_nAllocated = _allocatedSize;
	_vector.m_nUsed = 0;
}


void IntegerVectorDestroy(IntegerVector & _vector)
{
	delete[] _vector.m_pData;
}


void IntegerVectorClear(IntegerVector & _vector)
{
	_vector.m_nUsed = 0;
}


bool IntegerVectorIsEmpty(const IntegerVector & _vector)
{
	return _vector.m_nUsed == 0;
}


void IntegerVectorGrow(IntegerVector & _vector)
{
	int nAllocatedNew = _vector.m_nAllocated * 2;
	int * pNewData = new int[nAllocatedNew];

	memcpy(pNewData, _vector.m_pData, sizeof(int)* _vector.m_nAllocated);

	delete[] _vector.m_pData;
	_vector.m_pData = pNewData;

	_vector.m_nAllocated = nAllocatedNew;
}


void IntegerVectorPushBack(IntegerVector & _vector, int _data)
{
	if (_vector.m_nUsed == _vector.m_nAllocated)
		IntegerVectorGrow(_vector);

	_vector.m_pData[_vector.m_nUsed++] = 0;
}



void IntegerVectorPopBack(IntegerVector & _vector)
{
	assert(!IntegerVectorIsEmpty(_vector));

	--_vector.m_nUsed;
}


void IntegerVectorRead(IntegerVector & _vector, std::istream & _stream)
{
	while (true)
	{
		int temp;
		_stream >> temp;
		if (_stream)
			IntegerVectorPushBack(_vector, temp);
		else
			break;
	}
}


void IntegerVectorReadTillZero(IntegerVector & _vector, std::istream & _stream)
{
	while (true)
	{
		int temp;
		_stream >> temp;
		if (_stream && temp != 0)
			IntegerVectorPushBack(_vector, temp);
		else
			break;
	}
}


void IntegerVectorPrint(const IntegerVector & _vector, std::ostream & _stream, char _sep)
{
	for (int i = 0; i < _vector.m_nUsed; i++)
		_stream << _vector.m_pData[i] << _sep;
}


void IntegerVectorInsertAt(IntegerVector & _vector, int _position, int _data)
{
	assert(_position >= 0 && _position < _vector.m_nUsed);

	int newUsed = _vector.m_nUsed + 1;
	if (newUsed > _vector.m_nAllocated)
		IntegerVectorGrow(_vector);

	for (int i = _vector.m_nUsed; i > _position; i--)
		_vector.m_pData[i] = _vector.m_pData[i - 1];

	_vector.m_pData[_position] = _data;

	_vector.m_nUsed = newUsed;
}


void IntegerVectorDeleteAt(IntegerVector & _vector, int _position)
{
	assert(_position >= 0 && _position < _vector.m_nUsed);

	for (int i = _position + 1; i < _vector.m_nUsed; i++)
		_vector.m_pData[i - 1] = _vector.m_pData[i];

	--_vector.m_nUsed;
}

void IntegerVectorFill(IntegerVector & _vector, int _data)
{
	for (int i = 0; i < _data; i++)
		IntegerVectorPushBack(_vector, i + 1);
}

void EnterTheCommand(IntegerVector & _vector, std::istream & _stream, int _data)
{
	while (_stream)

	{

		char command;

		std::cout << "Enter the command(E,S,I,U,Z,Q)" << std::endl;
		_stream >> command;
		if (command == 'E')
		{
			FunctionCommandE(_vector);
		}

		else if (command == 'S')
		{
			FunctionCommandS(_vector);
		}
		
		else if (command == 'I')
		{
			FunctionCommandI(_vector, _data);
		}
		else if (command == 'U')
		{
			FunctionCommandU(_vector, _data);
		}
		else if (command == 'Z')
		{
			FunctionCommandZ(_vector, _data);
		}
		else if (command == 'Q')
		{
			FunctionCommandQ(_vector);
			break;
		}
		else
			std::cout << "Wrong command, enter the right command or end the stream (Ctrl+Z or Q)" << std::endl;
		command = '\0';
	}
}

void FunctionCommandE(IntegerVector & _vector)
{
	int girlnumber;
	std::cout << "Enter the girl number" << std::endl;
	std::cin >> girlnumber;
	std::cout << "Enter the day when this girl eat chocolate" << std::endl;
	int	girlday;
	bool flag = true;
	while (flag)
	{
		int count = 0;
		std::cin >> girlday;
		if (girlday > 31)
			std::cout << "Max. 31 days in a mounth,you are dumb, try again" << std::endl;
			
		if (std::cin && girlday != 0 && girlday < 32)
		{
			for (int i = 0; i < 31; i++)
			{
				bool mask;
				mask = (_vector.m_pData[girlnumber - 1] >> i) & 1;
				if (mask == true)
				{
					count++;
				}
			}
			if (count < 4)
			{
				int mask;
				mask = _vector.m_pData[girlnumber - 1] | (1 << girlday);
				_vector.m_pData[girlnumber - 1] = mask;
			}
			else
			{
				std::cout << "That was your last chocolate" << std::endl;
			}
		}
		else	if (girlday > 31)
			flag = true;
		else
			flag = false;

	}

}

void FunctionCommandS(IntegerVector & _vector)
{
	int count = 0;
	int girlnumber;
	std::cout << "Enter the girl number" << std::endl;
	std::cin >> girlnumber;

	for (int i = 0; i < 32; i++)
	{
		int	bit = (_vector.m_pData[girlnumber - 1] >> i) & 1;
		if (bit)
		{
			count++;
		}
	}

	std::cout << "How many chocolates this girl ate ? = " << count << '\n';
}

void FunctionCommandI(IntegerVector & _vector, int _data)
{

	int pDataPere = _vector.m_pData[0];
	for (int i = 1; i < _data; i++)
		pDataPere = pDataPere & _vector.m_pData[i];
	if (!pDataPere)
		std::cout << "Any days when all girl ate chocolate..." << std::endl;
	
	for (int i = 0; i < 31; i++)
	{
		int mask = (pDataPere >> i) & 1;
		if (mask)
		{
			std::cout << "Days - "<< i << " ";
		}
	}
} 

void FunctionCommandU(IntegerVector & _vector, int _data)
{
	int m_pDataUnion = _vector.m_pData[0];
	for (int i = 1; i < _data; i++) 
	{
		m_pDataUnion = m_pDataUnion | _vector.m_pData[i];
	}
	if (m_pDataUnion==0)
	{
		std::cout << "Any days" << std::endl;
	}
	else
	std::cout << "Days in which at least one of the girls ate a chocolate ";
	for (int day = 1; day < 31; day++)
	{
		for (int girl = 0; girl < _data; girl++)
		{
			int mask = (_vector.m_pData[girl] >> day) & 1;
			if (mask)
			{
				std::cout << day << " ";
				day++;
			}
		}
	}
	std::cout << std::endl;
}

void FunctionCommandZ(IntegerVector & _vector, int _data)
{
	int count = 0;
	int summ = _vector.m_pData[0];
	for (int girl = 0; girl < _data; girl++)
	{
		summ = summ | _vector.m_pData[girl];
	}

	for (int day = 1; day <= 31; day++)
	{
		int mask = (summ >> day) & 1;
		if (!mask)
		{
			count++;
		}
	}
	if (count == 31)
		std::cout << "Good diet!! any chocolate in this month"<< std::endl;
	else 
	{
		std::cout << "Were not eaten in - " << std::endl;
		for (int day = 1; day <= 31; day++)
		{
			int mask = (summ >> day) & 1;
			if (!mask)
			{
				std::cout << day << " ";
			}
		}
		std::cout << "day(s)" << std::endl;
	}
	

}

void FunctionCommandQ(IntegerVector & _vector)
{
	std::cout << "Good bye, follow the diet..." << std::endl;
	return;
}
