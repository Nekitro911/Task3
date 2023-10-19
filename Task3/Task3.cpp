// Task3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#pragma hdrstop
#include <conio.h>
#include <iostream>
#include <string>
#include <windows.h>
#include <time.h>
#include <stdlib.h>

using std::cout;
using std::cin;
using std::endl;

struct TInf {
	int num;
	TInf* next;
};
int N;
int compare, fw;

int IsQueueEmpty(TInf* qHead, TInf* qTail)
{
	return qHead == NULL ? 1 : 0;
}
void SetQueueNext(TInf** pqHead, TInf** pqTail, TInf* next)
{
	if (IsQueueEmpty(*pqHead, *pqTail))
		*pqHead = next;
	else
		(*pqTail)->next = next;
	*pqTail = next;
	(*pqTail)->next = NULL;
}
void AddQueueNext(TInf** pqHead, TInf** pqTail, int num)
{
	TInf* p = new TInf;
	p->num = num;
	p->next = NULL;
	SetQueueNext(pqHead, pqTail, p);
}

void EmptyQueue(TInf** pqHead, TInf** pqTail)
{
	*pqHead = NULL;
	*pqTail = NULL;
}
void ConcatQueues(TInf** pq1Head, TInf** pq1Tail, TInf* q2Head, TInf* q2Tail)
{
	if (IsQueueEmpty(q2Head, q2Tail))
		return;
	if (IsQueueEmpty(*pq1Head, *pq1Tail)) {
		*pq1Head = q2Head;
		*pq1Tail = q2Tail;
	}
	else {
		(*pq1Tail)->next = q2Head;
		*pq1Tail = q2Tail;
	}
}

int Digit(int num, int digitsNumber, int digitNo)
{
	int i;
	char s[10];
	_itoa_s(num, s, 10);
	while (strlen(s) < digitsNumber) {
		for (i = strlen(s); i >= 0; i--)
			s[i + 1] = s[i];
		s[0] = '0';
	}
	return s[digitNo - 1] - '0';
}


void Sort(TInf** pqHead, TInf** pqTail)
{
	const int l = 3;
	const int _m = 10;
	TInf* qmHead[_m];
	TInf* qmTail[_m];
	int d;
	compare = 0;
	fw = 0;
	for (int j = l; j >= 1; j--) {
		for (int i = 0; i < _m; i++)
			EmptyQueue(&qmHead[i], &qmTail[i]);
		TInf* p = *pqHead;
		while (p != NULL) {
			d = Digit(p->num, l, j);
			TInf* pTmp = p;
			p = p->next;
			SetQueueNext(&qmHead[d], &qmTail[d], pTmp);
			qmTail[d]->next = NULL;
			fw++;
		}
		EmptyQueue(pqHead, pqTail);
		for (int i = 0; i < _m; i++) {
			ConcatQueues(pqHead, pqTail, qmHead[i], qmTail[i]);
			fw++;
		}
	}
}

void RandomQueue(TInf** pqHead, TInf** pqTail)
{
	EmptyQueue(pqHead, pqTail);

	for (int i = 1; i <= N; i++)
		AddQueueNext(pqHead, pqTail, 1 + rand() % N);
}

void AscQueue(TInf** pqHead, TInf** pqTail)
{
	EmptyQueue(pqHead, pqTail);
	for (int i = 1; i <= N; i++)
		AddQueueNext(pqHead, pqTail, i);
}

void DescQueue(TInf** pqHead, TInf** pqTail)
{
	EmptyQueue(pqHead, pqTail);
	for (int i = N; i >= 1; i--)
		AddQueueNext(pqHead, pqTail, i);
}

void PrintQueue(TInf* qHead, TInf* qTail)
{
	TInf* p = qHead;
	while (p != NULL) {
		printf("%4d", p->num);
		p = p->next;
	}
	cout << "\n";
}

int Checksum(TInf* qHead, TInf* qTail)
{
	int sum = 0;
	TInf* p = qHead;
	while (p != NULL) {
		sum += p->num;
		p = p->next;
	}
	return sum;
}

int SeriesNumber(TInf* qHead, TInf* qTail)
{
	int series = 1;
	TInf* p = qHead;
	int prev = p->num;
	p = p->next;
	while (p != NULL) {
		if (p->num < prev)
			series++;
		prev = p->num;
		p = p->next;
	}
	return series;
}

void PrintChecksum(TInf* qHead, TInf* qTail)
{
	cout << "Kontrolnaia summa elementov spiska: ";
	cout << Checksum(qHead, qTail) << endl;
}

void PrintInf(TInf* qHead, TInf* qTail)
{
	cout << "Kollochestvo serii v spiske: " << SeriesNumber(qHead, qTail) << "\nKollichestvo sravnenii: " << compare << ", kollichestvo peresilok: " << fw << endl;
}

void Print(TInf** pqHead, TInf** pqTail, const char* s)
{
	cout <<  s << ":" << endl;
	PrintQueue(*pqHead, *pqTail);
	cout << "\n";
	PrintChecksum(*pqHead, *pqTail);
	cout << "\n";
	Sort(pqHead, pqTail);
	cout << "Posledovatelnost posle sortirovki:\n";
	PrintQueue(*pqHead, *pqTail);
	cout << "\n";
	PrintChecksum(*pqHead, *pqTail);
	PrintInf(*pqHead, *pqTail);
}
int main()
{
	system("mode con cols=85 lines=75");
	system("color 0");
	TInf* qHead, *qTail;
	cout << "Vvedite kollichestvo elementov v spiske dlia posleduyshei srtirovki: ";
	cin >> N;
	system("cls");
	RandomQueue(&qHead, &qTail);
	/*Print(&qHead, &qTail);
	AscQueue(&qHead, &qTail);
	Print(&qHead, &qTail);
	DescQueue(&qHead, &qTail);
	Print(&qHead, &qTail);*/
	Print(&qHead, &qTail, "\n1) Random posledovatelnost");
	AscQueue(&qHead, &qTail);
	Print(&qHead, &qTail, "\n2) Uporadochennaia posledovatelnost po vozrastaniy");
	DescQueue(&qHead, &qTail);
	Print(&qHead, &qTail, "\n3) Uporadochennaia posledovatelnost po ubivaniy");
	system("pause");
	return 0;
}


// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
