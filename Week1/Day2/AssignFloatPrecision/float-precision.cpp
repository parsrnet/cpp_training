#include <cstdio>
//	 ^^^^^^^^ this is the ONLY C++ code in this application! The rest is C (except for the std namespace)

// Here are some limitations of floats, double floats, and other data types!

#define FLUSH() printf("\n\n\n")

typedef union {float f; double l; long double L; } decimal_ut; // I use a union here to save on memory (even though that's mostly unimportant) and as a bit of a flourish
typedef enum { FLOAT, DOUBLE, LONG_DOUBLE } decimal_type_et; // Sadly, we have to be explicit in C(for the most part), so here's the possible types.

// Fun little function to really streamline my examples.
void loopTable(const decimal_ut&, const decimal_type_et,  unsigned loopCount, long incrementBy);

int main(void)
{
	// Here are some values that floats can't represent exactly! //
	
	const float f = 0.3f; // Tiny f or big F declares a floating point literal
	printf("(Floating Point Decimal) {.3f} = %.20f\n"		// 0.30000001192...
		"(Scientific Notation) {.3e} = %e\n", f, f);		// 3.000000e-01

	// You can see here that there's exact precision up to the one-hundred millionth's place. //
	
	
	// Why don't we compare that to a double floating point? //
	
	const double d = 0.3l; // Tiny 'l' declares a double floating point literal
	printf("(Double Floating Point Dec) {.3l} = %.20lf\n", d);	 // 0.29999999999999998890

	// Interesting! Now we're getting a value slightly below .3, but much closer to .3 overall!
	
	
	// Why don't we try the most precise value type, the long double floating point ? //
	
	const long double ld = 0.3L; // Big 'L' declares a long double floating point literal
	printf("(Long Dbl Floating Point Dec.) {.3L} = %.20Lf\n", ld);	// 0.30000000000000000001
	
	// Now THAT is precision!! I don't think I can feasibly count to that decimal place because I don't know its name!
	

	// However, there's a BIG tradeoff! //
	/* I won't show it in the program because you can see it in the previous assignment,
	 * but double floating point values take up an astounding 16 BYTES of space! That's eight times the space of a short word!! */
	
	
	// Let's investigate the precision of these floating point values as we increase their size. //
	
	FLUSH();

	const int loopTimes = 10;
	int add = 10;
	decimal_ut floatExample { .f=0.3f };

	printf("FLOAT:\n");
	loopTable(floatExample, FLOAT, loopTimes, add);

	/* What in the world is going on with that!?
	 * Well - there's another trait of floating point numbers. That is: they're represented inside our memory as binary scientific notation.
	 * That is, x * 2^y. Some bits are dedicated to the binary number, some are dedicated to the exponent.
	 * As we increase the size of the number before the decimal point, we lose bits that are critical to the accuracy of the value after the decimal point.
	 * Further, binary scientific notation simply has no representation for some decimal numbers, so you just have to approximate.
	 */

	FLUSH();

	// Let's give it a shot with a more accurate form. //
	
	decimal_ut doubleExample {.l = 0.3l};

	printf("DOUBLE:\n");
	loopTable(doubleExample, DOUBLE, loopTimes, add);

	/* That was quite a bit more accurate! */

	FLUSH();

	// Again with another, much larger type... //

	decimal_ut longDblExample {.L = 0.3L};
	printf("LONG DOUBLE:\n");
	loopTable(longDblExample, LONG_DOUBLE, loopTimes, add);
	
	/* Wow! Almost no loss of precision until the very end! */

	FLUSH();

	/* These all share a similarity in that they're never 100% precise. Long double is extremely close, but not quite there!
	 * The implication of this in our code is that we should never, ever compare floats using the '==' operator,
	 * especially not when comparing them with integers,
	 * unless maybe in a system where we have built-in redundancy to make sure two floats/doubles are the same exact value in memory!
	 * There is a caveat using overloading! The built-in '==' operator will always convert both sides to float when used in conjunction
	 * with an integer and float value. Typically, the approximation is close enough to get it right - but not always.
	 * That's really why it's more important to be explicit rather than relying on the implicit conversion,
	 * and taking advantage of approximation
	 */

	// Here's an example of why to not use the == operator! //
	
	float testFloat = 0.3f * 100'000'000;	//We, as humans, know that .3 * 100,000,000 = 30,000,000.
	int testInt = 30'000'000;		//And we know that 30,000,000 = 30,000,000!
	printf("Is 0.3 * 100,000,000 == 30,000,000?\n");
	printf((testFloat == testInt) ? "They're equal!\n" : "They're not equal!\n"); // They're not equal!

	/* It's very important working with floating point numbers and integers to use approximation
	 * Asking 'is this number between two values?' as opposed to 'is this number exactly equal to this value?' is typically a good idea!
	 * Sometimes, representing decimals as two integer values is a better idea (int integerValue; int decimalValue)
	 */

	printf("Is %f approximately equal to %d within a margin of 5?\n", testFloat, testInt);
	float epsilon = testFloat - testInt;
	printf((epsilon <= 2.5f && epsilon >= -2.5f) ? "They're close enough to call it engineering!\n" :
	     "They're not even approximately equal!\n"); // They're close enough to call it engineering!

	// Thanks for taking a look at my code! //

	return 0;
}

void loopTable(const decimal_ut& decVal, const decimal_type_et decType, unsigned loopCount, long increment)
{
	for (unsigned i=1; i <= loopCount; i++)
	{
		printf("Iteration %2d : ", i);
		if (decType == FLOAT)
			printf("FLOAT = %.10f\n", decVal.f + increment);
		else if (decType == DOUBLE)
			printf("DOUBLE = %.10lf\n", decVal.l + increment);
		else if (decType == LONG_DOUBLE)
			printf("LONG DBL = %.10Lf\n", decVal.L + increment);
		increment *= 10;
	}
}

