#pragma once

template <int N> class Func
{
public:
	virtual bool operator() (unsigned int arg) = 0;
};

template <int N> class ConstTrueFunc : public Func<N>
{
public:
	virtual bool operator() (unsigned int arg) override
	{
		return true;
	}
};

template <int N> class ConstFalseFunc : public Func<N>
{
public:
	virtual bool operator() (unsigned int arg) override
	{
		return false;
	}

};

template <int N> class BalancedFunc : public Func<N>
{
public:
	virtual bool operator() (unsigned int arg) override
	{
		return (arg < (1 << N) / 2);
	}

};

template <int N> class SingleRootFunc : public Func<N>
{
public:
	unsigned int root_num;

	SingleRootFunc(unsigned int root_num): root_num(root_num) {}

	virtual bool operator() (unsigned int arg) override
	{
		return arg == root_num;
	}

};

template <int N> class DoubleRootFunc : public Func<N>
{
public:
	unsigned int root1, root2;

	DoubleRootFunc(unsigned int root1, unsigned int root2) : root1(root1), root2(root2) {}

	virtual bool operator() (unsigned int arg) override
	{
		return arg == root1 || arg == root2;
	}

};