// CCar.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Car.h"
#include "CarControl.h"

#include <iostream>

int main()
{
	CCar car;
	CCarControl carControl(car, std::cin, std::cout);

	while (!std::cin.eof() && !std::cin.fail())
	{
		std::cout << "> ";
		if (!carControl.HandleCommand())
		{
			std::cout << "Unknown command!" << std::endl;
		}
	}
    return 0;
}

