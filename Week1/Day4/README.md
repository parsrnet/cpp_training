# Day 4 Assignments

## 1. Arithmetic Expressions:
`assert(3 == 3.0)`

This will pass! The integer on the right side is implicitly converted into a double floating point and that just so happens to be the equivalent of 3.0.
___
```
float x = 3.1;
assert(x == 3.1);
```
This will _NOT_ pass. Setting x = 3.1 literal will implicitly convert the double 3.1 to a float. When we compare them, we are comparing the float to a double which will lead to precision errors. We can instead write (double x = 3.1) OR (float x = 3.1f; assert(x == 3.1f);) to make this pass.
___
`assert(3.1 == 3.1);`

This will pass just fine! This compares the double literal 3.1 to the double literal 3.1, which we can rely on the compiler to optimize to `assert(TRUE)` because we're comparing two literals of identitical value.
___
`assert(true == 1.0);`

This will pass. The boolean true is implicitly convert to a double with the equivalent value of 1.0.
___
`assert('a' == 97);`

This will pass. According to the ASCII chart, the value of char 'a' is 97, and the literal is implictly converted to an int type.
___
```
int* p = 0;
assert(NULL == p);
```
This will pass (so long as NULL is defined in the corresponding header)! We're actually setting the value of a pointer to 0, which means nullptr or NULL (a C macro equal to 0). If we were to instead convert this to `int* p = new int(0);` then the assert would fail, because it's checking the address held by p - not the value.
___
```
assert(NULL == 0);
```
As I stated previously, most C developers understand that NULL is a special compile-time constant equal to 0. This will pass because we are comparing 0 to 0, which is true. 
## 2. Truth Table for Cast Operators
|                 	|        float        	|         int        	|         char        	|         bool        	|
|----------------:	|:-------------------:	|:------------------:	|:-------------------:	|:-------------------:	|
| ... + __float__ 	|    float + float    	| (float)int + float 	| (float)char + float 	| (float)bool + float 	|
|   ... + __int__ 	|  float + (float)int 	|      int + int     	|   (int)char + int   	|   (int)bool + int   	|
|  ... + __char__ 	| float + (float)char 	|   int + (int)char  	|     char + char     	|  (char)bool + char  	|
|  ... + __bool__ 	| float + (float)bool 	|   int + (int)bool  	|  char + (char)bool  	|     bool + bool     	|

## 3. Operators
Take a look at my code in this [example](https://github.com/parsrnet/cpp_training/edit/main/Week1/Day4/example) for all the operators in C that I am aware of.

## 4. Increment Operators
```
#include <cassert>
int main(void)
{
  int x=4;
  int y=x+++2;
  assert(y == 6);
  assert(x == 5);
}
```
The assert will pass TRUE! This is because we can simplify the expression `y=x+++2` as `y = (x++) + 2`. Because the increment is post-fixed, we can expect the expression `x++` to return the value of `x` before incrementation: 4. `y = 4 + 2` is equal to 6, so `y = 6` and `x++` would increment x from 4 to 5, thus `x = 5`.

## 5. AND/OR/NOT Operators
| A 	| B 	| !A 	| !B 	| A && B 	| A \|\| B 	|
|---	|---	|----	|----	|--------	|----------	|
| 0 	| 0 	|  1 	|  1 	|    0   	|     0    	|
| 1 	| 0 	|  0 	|  1 	|    0   	|     1    	|
| 0 	| 1 	|  1 	|  0 	|    0   	|     1    	|
| 1 	| 1 	|  0 	|  0 	|    1   	|     1    	|
