#include "printable.h"

int main() {
	Printable* printable = new PrintAsHTML("Hello, world!");
	std::ofstream file("test.txt");

	try {
		saveTo(file, printable).asHTML();
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}

	return 0;
}