#include <iostream>
#include "Park.h"

void main()
{
	int ROW=70, COL=25;
	Park my_park;
	int number_of_grass;
	std::cout << "Enter number of grass" << std::endl;
	std::cin >> number_of_grass;
	my_park.set_in_begin(number_of_grass);
	my_park.print();
	my_park.change_iteration();
	my_park.change_iteration();
	my_park.print();
	/*
	while (1)
	{
		my_park.change_iteration();
		my_park.print();
		std::cin.get();
	}*/

	std::cin.get();
	std::cin.get();
	std::cin.get();

}