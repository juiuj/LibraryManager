#include <iostream>
#include <string>
#include <list>
#include <cstring>
#include <fstream>
#include <iostream>
#include "Book.h"
#include "LibraryManager.h"

#define ADMIN_PSSWORD 1111

// 책장 크기
#define ROW 3
#define COL 5

int main()
{
	LibraryManager manager = LibraryManager();
	manager.initialize();
}