#include <iostream>

struct ExampleStruct
{
	float value;
	ExampleStruct(float f) : value(f) {}

	void myfunc(float f)
	{
		// This function can do whatever it would like with properties of the struct
		std::cout << "(normal function) Increment value by " << f << std::endl;
		std::cout << (value += f) << std::endl;
	}
	void myfunc(float f) const
	{
		// This function cannot modify values of the struct, as according to the promise we make when we define a const function
		std::cout << "(const overload) Value plus " << f << std::endl;
		std::cout << (value + f) << std::endl;
	}
};


int main(void)
{
	// NON CONST
	std::cout << "Non-Const example:" << std::endl;
	struct ExampleStruct e(100.0f);
	e.myfunc(10);
	e.myfunc(20);
	e.myfunc(30);

	// CONST
	std::cout << "Const example:" << std::endl;
	const struct ExampleStruct eConst(100.0f);
	eConst.myfunc(10);
	eConst.myfunc(20);
	eConst.myfunc(30);

	return 0;
}
