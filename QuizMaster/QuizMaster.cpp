#include <iostream>
#include <fstream>
#include "Administrator.h"
#include "Console.h";

int main()
{
	Admin admin1 = Admin("Kaloyan", "Tanev", "kaloyan13tanev", "kaloyantanev");
	std::ofstream ofs("Users.bin", std::ios::binary);
	size_t size = 1;
	ofs.write((const char*)&size, sizeof(size));
	admin1.serialize(ofs);
	ofs.close();
	try {
		Console::Start();
	}
	catch (std::exception ex) {
		std::cout << ex.what() << std::endl;
	}
}