#include "mainMenu.h"
#include "IntroSort.h"
#include <iostream>

auto printArray(int array[], int const size) -> void
{
    for (auto i = 0; i < size; i++)
	    std::cout << array[i] << " ";
	std::cout << std::endl;
}

auto main() -> int
{
	int array[] = { 12, 11, 13, 5, 6, 7 };
	IntroSort::sort(array, 6);
	printArray(array, 6);
	
	mainMenu menu;
	menu.showMainMenu();
    return 0;
}
