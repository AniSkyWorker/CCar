#include "stdafx.h"
#include "Car.h"


int main()
{
	CCar car;
	std::string string;
	int argument;

	while (!std::cin.eof() && !std::cin.fail())
	{
		std::cout << "> ";
		std::cin >> string;

		if (string == "TurnOff")
		{
			car.TurnOffEngine();
		}
		else if (string == "TurnOn")
		{
			car.TurnOnEngine();
		}
		else if (string == "SetSpeed")
		{
			std::cin >> argument;
			car.SetSpeed(argument);
		}
		else if (string == "SetGear")
		{
			std::cin >> argument;
			car.SetGear(argument);
		}
		else if (string == "Info")
		{
			car.PrintCurrentState();
		}
		else
		{
			std::cout << "Invalid command!" << std::endl;
		}
	}

    return 0;
}

