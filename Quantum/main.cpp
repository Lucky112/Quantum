#include "qbit.h"
#include "qbitN.h"
#include "Func.h"

#include <stdio.h>
#include <iostream>

#define N 4

bool IsConstantByDjoz(Func<N>& f);
std::pair<int, double> Grover(Func<N>& f);

const char* GetBitStr(int arg);
std::pair<int, double> argmax(Complex s[], int len);

int main()
{
	setlocale(LC_ALL, "Russian");

	ConstTrueFunc<N> CTF;
	ConstFalseFunc<N> CFF;
	BalancedFunc<N> BF;

	SingleRootFunc<N> SRF1(1);
	SingleRootFunc<N> SRF7(7);

	DoubleRootFunc<N> DRF24(2, 4);
	
	bool res = IsConstantByDjoz(CTF);
	if (res)
		printf("Функция %s является константой\n", typeid(CTF).name());
	else
		printf("Функция %s является сбалансированной\n", typeid(CTF).name());

	res = IsConstantByDjoz(CFF);
	if (res)
		printf("Функция %s является константой\n", typeid(CFF).name());
	else
		printf("Функция %s является сбалансированной\n", typeid(CFF).name());

	res = IsConstantByDjoz(BF);
	if (res)
		printf("Функция %s является константой\n", typeid(BF).name());
	else
		printf("Функция %s является сбалансированной\n\n", typeid(BF).name());



	std::pair<int, double> arg;

	arg = Grover(SRF1);
	printf("Корень уравнения f(x%d) = 1 имеет вид %s c вероятностью %5.2f\n", SRF1.root_num, GetBitStr(arg.first), arg.second);

	arg = Grover(SRF7);
	printf("Корень уравнения f(x%d) = 1 имеет вид %s c вероятностью %5.2f\n\n", SRF7.root_num, GetBitStr(arg.first), arg.second);



	arg = Grover(CFF);
	printf("Корень уравнения %s(xn) = 1 имеет вид %s c вероятностью %5.2f\n", typeid(CFF).name(), GetBitStr(arg.first), arg.second);

	arg = Grover(CTF);
	printf("Корень уравнения %s(xn) = 1 имеет вид %s c вероятностью %5.2f\n\n", typeid(CTF).name(), GetBitStr(arg.first), arg.second);



	arg = Grover(DRF24);
	printf("Корень уравнения f(x%d|x%d) = 1 имеет вид %s c вероятностью %5.2f\n\n", DRF24.root1, DRF24.root2, GetBitStr(arg.first), arg.second);
}

const char* GetBitStr(int arg)
{
	if (arg == 0)
		return "0";

	static char res[N];
	for (int i = 0; i<N; i++)
		res[N-i-1] = (arg & (int)pow(2, i)) ? '1' : '0';

	return res;
}

bool IsConstantByDjoz(Func<N>& f)
{
	QbitN <N> q;

	q.gH();
	q.Of(f);
	q.gH();

	return ! (fabs(q.s[0].mod2()) < 0.0001);
}

std::pair<int, double> Grover(Func<N>& f)
{
	QbitN<N> q;

	const int iter = (int)trunc(M_PI * sqrt(pow(2, N)) / 4);

	q.gH();
	for (int i = 0; i < iter; i++) {
		q.Of(f);
		q.R();
	}

	return argmax(q.s, 1<<N);
}


std::pair<int, double> argmax(Complex s[], int len)
{
	int index = -1;
	double max = 0;

	for (int i = 0; i < len; i++)
	{
		double mod = s[i].mod2();
		if (mod >= max)
		{
			max = mod;
			index = i;
		}
	}

	return std::make_pair(index, max);
}
