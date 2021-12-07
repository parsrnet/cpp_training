#include <iostream>
#include <thread>
#include <chrono>

#define PHONY_DELAY_MS 10

using namespace std;

int main(void)
{
	unsigned long ops = 0;

	const char* message = "Hello World!?";
	int i = 0;

	srand(time(NULL));
	while (message[i] != '\0')
	{
		ops++;
		char curChar = message[i], guess = 0;

		// We do give the program a hint so that we aren't checking the full ASCII table, instead just the human-readable symbols.

		if (curChar >= 0x20 && curChar <= 0x7E)
			guess = 0x20 + (rand() % 0x5E);
		
		// And if it does encounter a non-human-readable symbol, it'll just automatically guess it.

		else
			guess = curChar;

		cout << guess << flush;
		
		this_thread::sleep_for(chrono::milliseconds(PHONY_DELAY_MS));

		if (guess == curChar)
			i++;
		else
			cout << '\b' << flush;
	}

	cout << endl << "Wow! We printed `" << message << "` in " << ops << " operations!" << endl;
	
	return 0;
}
