cmake_minimum_required(VERSION 3.14)
project(bankcli)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
	googletest
	URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(
	accounts_test
	tests/account_test.cpp
	obj/account.o
)
target_link_libraries(
	accounts_test
	gtest_main
)


include(GoogleTest)
gtest_discover_tests(accounts_test)

