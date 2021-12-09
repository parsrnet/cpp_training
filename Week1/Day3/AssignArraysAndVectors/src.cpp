#include <iostream>
#include <vector>
#include <cassert>

/* Hey, look at this nifty C++! We're really taking advantage of the language now!
 * I'm opting to take advantage of templating here. This is just a forward declaration here.
 * I use templating so we can use any type of array we want.
 */

// PARAMS:
// 	const T arr[]		: Array of objects to vectorize
// 	const size_t& len	: Length of input array
template<typename T>
std::vector<T> arrToVec(const T arr[], const size_t& len);


// This constexpr function evaluates an array of type T to return its size.
// We NEED to use constexpr so that the compiler can evaluate this function on compile time rather than only at runtime.
// There's a lot going on here that isn't at all immediately apparent,
// 	so in an enterprise setting, I might avoid it but the function name really does give it away.
// That being said, this is a beautiful expression. It takes advantage of some really niche concepts, and even the constrexpr keyword
//	which we covered very briefly already.

template<typename T, size_t N> // template<typename T, size_t N> : Basically, accept a type T (and implicitly its size N)
constexpr size_t arr_len(const T (&)[N]) { return N; } // const T (&)[N] : Unnamed array reference of Type T sizeof N: return size N

int main(void)
{
	int iArr[] { 1, 2, 3 };
	std::vector<int> iVec = arrToVec(iArr, 3);


	for(auto i : iVec)
		std::cout << i << " ";
	assert(iVec[0] == iArr[0] && iVec[1] == iArr[1] && iVec[2] == iArr[2]);
	std::cout << std::endl;

	const char* cStrArr[] { "Hello", ",", "world", "!" };
	std::vector<const char*> cStrVec = arrToVec(cStrArr, arr_len<const char*>(cStrArr));
	
	std::cout << "LENGTH: " << cStrVec.size() << std::endl;
	for(auto cstr : cStrVec)
		std::cout << cstr << " ";
	assert(cStrVec[0] == cStrArr[0] && cStrVec[1] == cStrArr[1] && cStrVec[2] == cStrArr[2] && cStrVec[3] == cStrArr[3]);
	std::cout << std::endl;


	return 0;
}

template<typename T>
std::vector<T> arrToVec(const T arr[], const size_t& len)
{
	std::vector<T> vect = std::vector<T>();
	for (int i=0; i < len; i++)
		vect.push_back(arr[i]);

	return vect;
}
