#include <iostream>
#include "string_list.h"
#include <cassert>
#include <cstring>
int main()
{
	// ������� � �������������� ������
	StringList l;
	StringListInit(l);

	// ��������� � ������ ������� ������-�������
	StringListPushBack(l, "Hello");
	
	// ��������� � ������ ������� ������ �� ���������� ������
	char temp[100];
	std::cin >> temp; // ������ ����� Goodbye � �������
	StringListPushBack(l, temp);
	//std::cout << l.m_pFirst->m_pNext->m_value;
	// ������� �����, ������ � ������ �� ������ ���� ������
	temp[0] = '\0';
	
	// �������� ����� � ������������ ������ � ��������� ������ � ������
	char * pDynamicBuf = new char[100];
	std::cin >> pDynamicBuf; // ������ ����� Thanks � �������
	StringListPushBack(l, pDynamicBuf);
	//std::cout << l.m_pLast->m_value;

	// ����������� ������, ������ � ������ �� ������ ���� ������
	delete[] pDynamicBuf;

	// ��������� �������� ����� � ������
	assert(!strcmp(l.m_pFirst->m_value, "Hello"));
	assert(!strcmp(l.m_pFirst->m_pNext->m_value, "Goodbye"));
	assert(!strcmp(l.m_pLast->m_value, "Thanks"));


	// ���������� ������ ������ �� ����� ��������
	StringListDestroy(l);
	system("pause");
		return 0;
}
