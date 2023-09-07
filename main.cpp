#include "printable.h"

int main() {
	Printable* printable = new DataHTML("Hello, world!");
	std::ofstream file("test.txt");

	if(file.is_open())
		saveTo(file, *printable);

	file.close();

	return 0;
}