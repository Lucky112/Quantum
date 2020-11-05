#include "qbit.h"

#include <math.h>
#include <corecrt_math_defines.h>

//#define M_SQRT1_2 0.7071067811865475

namespace qbit
{

	Qbit Qbit::e0(Complex(1, 0), Complex(0, 0));
	Qbit Qbit::e1(Complex(0, 0), Complex(1, 0));

	Qbit::Qbit(Complex A, Complex B)
	{
		double norm = sqrt(A.mod2() + B.mod2());
		if (norm == 0.0) {
			a.re = M_SQRT1_2; a.im = 0.0;
			b.re = M_SQRT1_2; b.im = 0.0;
		}
		else {
			a = Complex(1.0 / norm, 0.0) * A;
			b = Complex(1.0 / norm, 0.0) * B;
		}
	}

}