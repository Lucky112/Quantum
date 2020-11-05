#pragma once

class Complex
{
public:
	double re, im;

	Complex() : re(0), im(0) {}
	Complex(double re, double im) : re(re), im(im) {  }

	double mod2() { return re * re + im * im; }

	Complex operator + (Complex other) { return Complex(re + other.re, im + other.im); }
	Complex operator * (Complex other) { return Complex(re * other.re - im * other.im, re * other.im + other.re * im); }
};