#pragma once

#include <stdio.h>
#include <math.h>
#include <corecrt_math_defines.h>

#include "qbit.h"
#include "complex.h"
#include "Func.h"

using namespace qbit;

template <int N> class QbitN {
public:
	Complex s[1 << N];

	QbitN();
	QbitN(Qbit V[N]);		// регистр из N кубитов
	void gH();				// преобразование Адамара
	void Of(Func<N>& f);				// Фазовый поворот
	void R();				// Диффузия
	void print();
};

//
//template<int N> class QbitN_Grover : public QbitN<N>
//{
//public:
//	virtual void Of() override;
//};
//
//template<int N> class QbitN_Djoz : public QbitN<N>
//{
//public:
//	virtual void Of() override;
//};

//template <int N> void QbitN_Djoz<N>::Of() {
//	for (int i = 0; i < (1 << N); i++)
//		QbitN<N>::s[i] = Complex(-1.0, 0.0) * QbitN<N>::s[i];
//}
//
//template <int N> void QbitN_Grover<N>::Of() {
//	QbitN<N>::s[1] = Complex(-1.0, 0.0) * QbitN<N>::s[1];
//}



template <int N> 
QbitN<N>::QbitN(Qbit V[N]) {
	int P = 1 << N;
	int i, j, k, n;

	for (i = 0; i < P; i++) {
		s[i] = Complex(1.0, 0.0);
	}

	for (k = 2, n = 0; k <= P; k *= 2, n++) {
		for (i = 0; i < P / k; i++) {
			for (j = 0; j < k / 2; j++) {
				s[i + 2 * j * P / k] = s[i + 2 * j * P / k] * V[n].a;
				s[i + P / k + 2 * j * P / k] = s[i + P / k + 2 * j * P / k] * V[n].b;
			}
		}
	}
}

template <int N> 
QbitN<N>::QbitN() {
	int P = 1 << N;
	int i, j, k, n;

	for (i = 0; i < P; i++) {
		s[i] = Complex(1.0, 0.0);
	}

	for (k = 2, n = 0; k <= P; k *= 2, n++) {
		for (i = 0; i < P / k; i++) {
			for (j = 0; j < k / 2; j++) {
				s[i + 2 * j * P / k] = s[i + 2 * j * P / k] * Qbit::e0.a;
				s[i + P / k + 2 * j * P / k] = s[i + P / k + 2 * j * P / k] * Qbit::e0.b;
			}
		}
	}
}

template <int N>
inline void QbitN<N>::print() {
	int p = 1 << N;
	int i;

	printf("( ");
	for (i = 0; i < p; i++) {
		printf("%5.2f ", s[i].re);
	}
	printf(")\n");
};


template <int N>
inline void QbitN<N>::gH() {
	double U[1 << N][1 << N];

	int p, q, r, x;
	int i;

	Complex s1[1 << N];

	for (p = 0; p < (1 << N); p++) {
		for (q = 0; q < (1 << N); q++) {
			r = p & q;
			x = 0;
			for (i = 0; i < N; i++) {
				x = x + (r & 1);
				r >>= 1;
			}
			U[p][q] = (x & 1 ? -1 : 1) * pow(M_SQRT1_2, N);
		}
	}

	for (p = 0; p < (1 << N); p++) {
		s1[p] = s[p];
	}

	for (p = 0; p < (1 << N); p++) {
		s[p] = Complex(0, 0);
		for (q = 0; q < (1 << N); q++) {
			s[p] = s[p] + Complex(U[p][q], 0.0) * s1[q];
		}
	}
}

template<int N>
inline void QbitN<N>::Of(Func<N>& F)
{
	for (int i = 0; i < 1<<N; i++)
		if (F(i))
			s[i] = Complex(-1.0, 0.0) * s[i];
}


template <int N> 
inline void QbitN<N>::R() {
	Complex z[1 << N];
	int i, j;

	for (i = 0; i < (1 << N); i++) {
		z[i] = s[i];
		s[i] = Complex(-1.0, 0.0) * z[i];
	}

	for (i = 0; i < (1 << N); i++) {
		for (j = 0; j < (1 << N); j++) {
			s[i] = s[i] + Complex(1.0 / (1 << (N - 1)), 0.0) * z[j];
		}
	}
}
