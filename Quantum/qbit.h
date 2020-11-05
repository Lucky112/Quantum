#pragma once

#include <stdio.h>
#include "complex.h"

namespace qbit
{

	class Qbit {
	public:
		Complex a;
		Complex b;

		Qbit() : a(), b() {}
		Qbit(Complex A, Complex B);
		void print() { printf("(%5.2f %5.2f)", a.re, b.re); }

		static Qbit e0;
		static Qbit e1;

	};

}