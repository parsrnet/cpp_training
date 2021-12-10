#include <cassert>

int main(void)
{
	int a = 0;
	// UNARY OPERATORS //
	assert(a++ == 0); // Suffixed ++: Increment, return value before increment.
	assert(++a == 2); // Prefixed ++: Decrement, return reference to value (after increment).

	assert(a-- == 2); // Suffixed --: Decrement, return value before decrement
	assert(--a == 0); // Prefixed --: Decrement, return reference to value (after decrement).

	a = 10;
	assert(-a == -10);			// Minus -: value * -1.
	assert((!a) == 0);			// Unary NOT !: value == 0
	assert(*(&a) == a);			// Address of &: The address of the variable in memory
	assert(sizeof a == sizeof(a));		//sizeof: The size of the expression in bytes (technically a C unary operator, as exampled by the lack of parens. Also used like a function)

	a = 3;
	assert(~a == ~0 - 3);	// Unary bitwise NOT operator - flip ALL bits.

	// BINARY OPERATORS //
	
	/* Arithmetic */
	int lhs = 10, rhs = 5;		// left-hand side, right-hand side
	assert(lhs * rhs == 50);	// Multiplication
	assert(lhs / rhs == 2);		// Division
	assert(lhs % rhs == 0);		// Modulus (remainder of division)
  
	assert(lhs + rhs == 15); 	// Addition
	assert(lhs - rhs == 5);		// Subtraction
	
	/* Bitwise */
	lhs = 0b101, rhs = 0b011;
	assert((lhs << rhs) == 0b101000);	// Bitshift left: Move bits x bits to the left
	assert((lhs >> rhs) == 0);		// Bitshift right: Move bits x bits to the right
	assert((lhs ^ rhs) == 0b110);		// Bitwise XOR: Bits NOT equal and NOT 0 (1 ^ 1 = 0, 1 ^ 0 = 1, 0 ^ 0 = 0)
	assert((lhs & rhs) == (0b001));		// Bitwise AND: Bits EQUAL and NOT 0 (1 & 1 = 1, 1 & 0 = 0, 0 & 0 = 0)
	assert((lhs | rhs) == 0b111);		// Bitwise OR: Either bit 1 (1 | 1 = 1 , 1 | 0 = 1, 0 | 0 = 0)

	/* Comparison */
	lhs = 10, rhs = 10;
	assert((lhs == rhs) == 1);	// Compare EQ equals
	assert((lhs != rhs) == 0);	// Compare NEQ not equals
	assert((lhs >= rhs) == 1);	// Compare GEQ greater than/equals
	assert((lhs <= rhs) == 1);	// Compare LEQ less than/equals
	assert((lhs > rhs) == 0);	// Compare GT greater than
	assert((lhs < rhs) == 0);	// Compare LT less than

	/* Logical */
	lhs = 1, rhs = 0;
	assert((lhs == 1 && rhs == 0) == 1);	// Logical AND
	assert((lhs == 1 || rhs == 1) == 1);	// Logical OR

	// TERNARY //
	
	/* There's a single ternary operator in C, and it operates almost identically to an if statement */
	
	int x = 10, y = 20, z = 30;
	assert((x == y ? x*y : z) == z); 	// (condition) ? (body) : (else)
	y = 10;
	assert((x == y ? x*y : z) == x*y);

	return 0;
}
