#include "stdafx.h"
#include "Car.h"

void PrintCurrentState(CCar const& car)
{
	std::string workLine = car.IsEngineOn() ? "Engine is turned on;" : "Engine is turned off;";
	std::cout << workLine << std::endl
		<< car.GetSpeed() << " -speed of car;" << std::endl
		<< car.GetGear() << " -gear of transmission;" << std::endl;

	switch (car.GetMovementType())
	{
	case CCar::MovementType::STAY:
		workLine = "Car stay at now!;";
		break;
	case CCar::MovementType::FORWARD:
		workLine = "Car move foward at now!;";
		break;
	case CCar::MovementType::BACK:
		workLine = "Car move back at now!;";
		break;
	}

	std::cout << workLine << std::endl;
}


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
			if (!car.TurnOffEngine())
			{
				std::cout << "Engine (have already turned off) (car speed > 0 or/and transmisson not on zero gear" << std::endl;
			}
		}
		else if (string == "TurnOn")
		{
			if (!car.TurnOnEngine())
			{
				std::cout << "Engine have already turned on!" << std::endl;
			}
		}
		else if (string == "SetSpeed")
		{
			std::cin >> argument;
			if (!car.SetSpeed(argument))
			{
				std::cout << "You can't set this speed now you should change transmisson!" << std::endl;
			}
		}
		else if (string == "SetGear")
		{
			std::cin >> argument;
			if (!car.SetGear(argument))
			{
				std::cout << "You can't set this gear!" << std::endl;
			}
		}
		else if (string == "Info")
		{
			PrintCurrentState(car);
		}
		else
		{
			std::cout << "Invalid command!" << std::endl;
		}
	}

    return 0;
}

