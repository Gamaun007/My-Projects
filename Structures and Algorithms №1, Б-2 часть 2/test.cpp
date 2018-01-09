#include <iostream>
#include "string_list.h"
#include <cassert>
#include <cstring>
int main()
{
	// создаем и инициализируем список
	StringList l;
	StringListInit(l);

	// добавляем в список обычную строку-литерал
	StringListPushBack(l, "Hello");
	
	// добавляем в список обычную строку из временного буфера
	char temp[100];
	std::cin >> temp; // вводим текст Goodbye с консоли
	StringListPushBack(l, temp);
	//std::cout << l.m_pFirst->m_pNext->m_value;
	// очищаем буфер, строка в списке не должна быть задета
	temp[0] = '\0';
	
	// выделяем буфер в динамической памяти и добавляем строку в список
	char * pDynamicBuf = new char[100];
	std::cin >> pDynamicBuf; // вводим текст Thanks с консоли
	StringListPushBack(l, pDynamicBuf);
	//std::cout << l.m_pLast->m_value;

	// освобождаем память, строка в списке не должна быть задета
	delete[] pDynamicBuf;

	// проверяем значения строк в списке
	assert(!strcmp(l.m_pFirst->m_value, "Hello"));
	assert(!strcmp(l.m_pFirst->m_pNext->m_value, "Goodbye"));
	assert(!strcmp(l.m_pLast->m_value, "Thanks"));


	// уничтожаем список вместе со всеми строками
	StringListDestroy(l);
	system("pause");
		return 0;
}
