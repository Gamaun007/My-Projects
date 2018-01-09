#include <stdio.h>
#include <conio.h>
#include <iostream>


int WeightMaxInput();
int NodesNumberInput();
void EdgesCostInput(int max, int n, int **G);
void SortFunc(int kolreb, int **H);
void SortFuncOutput(int kolreb, int **H);
void FindMainFunc(int n, int kolreb, int **K, int **H, int **T);
void EdgesOutput(int a, int n, int max, int kolreb, int **T, int **L);
void MinWeightOutput(int kolreb, int **L);


using namespace std;
typedef int* tint;
void main()
{
	tint* G;
	tint* H;
	tint* K;
	tint* T;
	tint* L;
	setlocale(LC_ALL, "Russian");
	

	int max = WeightMaxInput();
	int n = NodesNumberInput();

	//G- свызный граф с заданной функцией стоимости, определенной на множестве ребер. 
	G = new tint[n];
	for (int i = 0; i < n; i++)
	{
		G[i] = new int[n];
	}
	EdgesCostInput(max,n,G);
	// переменная счетчик наличия ребра
	int kolreb = 0;
	for (int i = 1; i<n; i++)
	for (int j = 0; j < i; j++)
	{
		if (G[i][j] <max && G[i][j] > 0)
			kolreb++;
	}
	// создание динамического массиива размерностью равной количеству ребер
	H = new tint[kolreb];
	for (int i = 0; i<kolreb; i++)
		H[i] = new int[3];

	// Инициализация массива H в каждой ячейке массива - имеется 3 ячейки ( i-й столбец, j-й строка, стоимость ребра) 

	int a = 0;
	for (int i = 1; i<n; i++)
	for (int j = 0; j<i; j++)
	if (G[i][j] <max && G[i][j] != 0) {
		H[a][0] = i + 1;
		H[a][1] = j + 1;
		H[a][2] = G[i][j];
		a++;
	}
	cout << std::endl;

	// Сортировка ребер по убыванию веса 
	SortFunc(kolreb,H);
	SortFuncOutput(kolreb,H);
	//сдвиг в координатной плоскости
	for (int i = 0; i<kolreb; i++)
	{
		H[i][0] --;
		H[i][1] --;
	}

	K = new tint[n];
	for (int i = 0; i<n; i++)
		K[i] = new int[2];
	for (int i = 0; i<n; i++)
	{
		K[i][0] = i;
		K[i][1] = 0;
	}
	//создание квадратной матрицы
	//каркас(также называемый остовным или стягивающим деревом) T = (V, E’), где E’E - это связный граф без циклов.
	T = new tint[n];
	for (int i = 0; i<n; i++)
		T[i] = new int[n];
	for (int i = 0; i<n; i++)
	for (int j = 0; j<n; j++)
		T[i][j] = 0;
	//Коррекция индексов
	T[H[0][0]][H[0][1]] = H[0][2];
	T[H[0][1]][H[0][0]] = H[0][2];
	K[H[0][0]][1] = 1;
	K[H[0][1]][1] = 1;

	FindMainFunc(n,kolreb,K,H,T);

	kolreb = 0;
	for (int i = 1; i<n; i++)
	for (int j = 0; j<i; j++)
	if (T[i][j] <max && T[i][j] != 0)
		kolreb++;
	L = new tint[kolreb];
	for (int i = 0; i<kolreb; i++)
		L[i] = new int[3];
	//Вывод ребер минимального веса
	EdgesOutput(a,n,max,kolreb,T,L);
	MinWeightOutput(kolreb, L);
	system("pause");

}


int WeightMaxInput()
{
	int imax;
	do
	{
		cin.clear();
		cin.sync();
		cout << " Введите максимально допустимое значене веса ребра = ";
		cin >>imax;
		if (cin.fail()) cout << "Введенный некорректные данные, повторите ввод..." << endl;
		else
		if (imax <= 0) cout << "Рёбра не могут иметь отрицательный, и 0 вес, повторите ввод..." << endl;
	} while (cin.fail() || imax <= 0);


	imax++;
	return imax;
}
int NodesNumberInput()
{
	int in;
	do
	{
		cin.clear();
		cin.sync();
		cout << "\n Введите число вершин графа: \n ";
		cin >> in;
		if (cin.fail()) cout << "Введены некорректные данные, повторите ввод..." << endl;
		else
		if (in <= 1) cout << "Число вершин граффа не может быть меньше или= 1, повторите ввод..." << endl;
	} while (cin.fail() || in <= 1);
	return in;
}
void EdgesCostInput(int max, int n, int **G)
{
	cout << " Введите стоимость каждого ребра ( если ребра нет между показаными вершинами, введите 0 ) \n ";
	for (int i = 1; i<n; i++)
	for (int j = 0; j<i; j++)
	{
		do
		{
			cin.clear();
			cin.sync();
			cout << "Для ребра " << i + 1 << "-->" << j + 1 << "= ";
			cin >> G[i][j];
			if (cin.fail()) cout << "Введены некорректные данные, повторите ввод..." << endl;
			else
			if (G[i][j]<0) cout << "Вес вершины не может быть меньше 0, повторите ввод..." << endl;
			else
			if (G[i][j]>max - 1) cout << "Вес вершины - больше заданного, повторите ввод..." << endl;
		} while (cin.fail() || G[i][j]<0 || G[i][j]>max - 1);

	}
	for (int i = 1; i<n; i++)         // зеркально заполнение верхнего треугольника матрицы.
	for (int j = 0; j < i; j++)
	{
		G[j][i] = G[i][j];
	}
	
}
void SortFunc(int kolreb, int **H)
{
	int f, d, s;
	for (int i = 0; i<kolreb - 1; i++)
	for (int j = 0; j<kolreb - 1; j++)
	if (H[j][2] >H[j + 1][2]) {
		f = H[j][2];
		H[j][2] = H[j + 1][2];
		H[j + 1][2] = f;
		d = H[j][0];
		H[j][0] = H[j + 1][0];
		H[j + 1][0] = d;
		s = H[j][1];
		H[j][1] = H[j + 1][1];
		H[j + 1][1] = s;
	}
}
void SortFuncOutput(int kolreb, int **H)
{
	cout << "Матрица достижимости отсортированная по убыванию \n ";
	for (int i = 0; i<kolreb; i++)
	{
		cout << H[i][0] << "-->";
		cout << H[i][1] << " = ";
		cout << H[i][2] << std::endl;
		cout << " ";
	}
}
void FindMainFunc(int n, int kolreb, int **K, int **H, int **T)
{
	int m = 2;
	for (int i = 1; i<kolreb; i++)
		// если не диагональ
	if (K[H[i][0]][1] != K[H[i][1]][1])
	{
		//если ребро существует
		if (K[H[i][0]][1] >0 && K[H[i][1]][1] >0)
		{
			for (int j = 0; j<n; j++)
				//нашли ячейку на данной i-терации, получаем доступ к ячейке на анной итерации
			if (K[H[i][1]][1] == K[j][1])
			{  //переходим к следующему столбцу
				K[j][1] = K[H[i][0]][1];
			}
			K[H[i][1]][1] = K[H[i][0]][1];//j-eзначениеприсваивается i-му
			T[H[i][0]][H[i][1]] = H[i][2];
			T[H[i][1]][H[i][0]] = H[i][2];
		}
		// если сравнваемые строки не равны
		if ((K[H[i][0]][1] >0 && K[H[i][1]][1] == 0)
			|| (K[H[i][0]][1] == 0 && K[H[i][1]][1] >0))
		{
			//если строка слева не равна нулю, присваиваем следующей строке справа эту строку
			if (K[H[i][0]][1] != 0)
				K[H[i][1]][1] = K[H[i][0]][1];
			// на оборот
			if (K[H[i][1]][1] != 0)
				K[H[i][0]][1] = K[H[i][1]][1];
			// присваиваем значения веса ребра по индексам массиива размерности равной количеству ребер
			T[H[i][0]][H[i][1]] = H[i][2];
			T[H[i][1]][H[i][0]] = H[i][2];
		}
		if (K[H[i][0]][1] == 0 && K[H[i][1]][1] == 0)
		{
			K[H[i][0]][1] = m;
			K[H[i][1]][1] = m;
			T[H[i][0]][H[i][1]] = H[i][2];
			T[H[i][1]][H[i][0]] = H[i][2];
			m++;
		}
	}
}
void EdgesOutput(int a,int n,int max,int kolreb, int **T,int **L)
{
	cout << endl << " Вывод рёбер минимального веса \n ";
	a = 0;
	for (int i = 1; i<n; i++)
	for (int j = 0; j<i; j++)
	if (T[i][j] <max && T[i][j] != 0) {
		L[a][0] = i + 1;
		L[a][1] = j + 1;
		L[a][2] = T[i][j];
		a++;
	}
	for (int i = 0; i<kolreb; i++) {
		cout << L[i][0] << "-->";
		cout << L[i][1] << " = ";
		cout << L[i][2] << "\n ";
	}
}
void MinWeightOutput(int kolreb, int **L)
{
	int b = 0;
	for (int i = 0; i<kolreb; i++)
		b += L[i][2];
	cout << endl << " Стоимость остовного дерева = " << b << endl;
}