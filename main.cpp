#include "criss_cross.h"
#include <iostream>
#include <Windows.h>

int main(int argc, char* argv[]) {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    if (argc < 3) {
        cerr << "Использование: " << argv[0] << " <входной_файл> <выходной_файл>" << endl;
        return 1;
    }
	start(argv[1], argv[2]);
	return 0;
}