#include "stdafx.h"
#include "Car.h"


CCar::CCar()
	:currentGear(0)
	,currentSpeed(0)
	,engineCondition(false)
	,movement(MovementType::stay)
{
}

CCar::~CCar()
{
}

bool CCar::TurnOnEngine()
{
	if (engineCondition)
	{
		return false;
	}
	else
	{
		engineCondition = true;
	}

	return true;
}

bool CCar::TurnOffEngine()
{
	if ((engineCondition && movement == MovementType::stay && currentGear == 0) && engineCondition)
	{
		engineCondition = false;
	}
	else
	{
		return false;
	}

	return true;
}

bool CCar::SetGear(int gear)
{
	switch (gear)
	{
	case -1:
		if (!(currentGear < 2 && currentSpeed == 0))
		{
			return false;
		}
		break;
	case 0:
		break;
	case 1:
		if (!((currentGear == 0 && movement == MovementType::stay) || (movement == MovementType::foward && currentSpeed < 30)))
		{
			return false;
		}
		break;
	case 2:
		if (!(movement == MovementType::foward && currentSpeed > 20 && currentSpeed < 50))
		{
			return false;
		}
		break;
	case 3:
		if (!(movement == MovementType::foward && currentSpeed > 30 && currentSpeed < 60))
		{
			return false;
		}
		break;
	case 4:
		if (!(movement == MovementType::foward && currentSpeed > 40 && currentSpeed < 90))
		{
			return false;
		}
		break;
	case 5:
		if (!(movement == MovementType::foward && currentSpeed > 50))
		{
			return false;
		}
		break;
	default:
		return false;
	}

	currentGear = gear;
	return true;
}

bool CCar::SetSpeed(unsigned speed)
{
	switch (currentGear)
	{
	case -1:
		if (!(speed < 20))
		{
			return false;
		}
		break;
	case 0:
		if (!(speed <= currentSpeed))
		{
			return false;
		}
		break;
	case 1:
		if (!(speed < 30))
		{
			return false;
		}
		break;
	case 2:
		if (!(speed > 20 && speed < 50))
		{
			return false;
		}
		break;
	case 3:
		if (!(speed > 30 && speed < 60))
		{
			return false;
		}
		break;
	case 4:
		if (!(speed > 40 && speed < 90))
		{
			return false;
		}
		break;
	case 5:
		if (!(speed > 50 && speed < 150))
		{
			return false;
		}
		break;
	}

	currentSpeed = speed;
	return true;
}
