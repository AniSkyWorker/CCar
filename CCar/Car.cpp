#include "stdafx.h"
#include "Car.h"

CCar::CCar()
	:m_currentGear(0)
	,m_currentSpeed(0)
	,m_engineCondition(false)
	,m_movement(MovementType::stay)
{
}


bool CCar::TurnOnEngine()
{
	if (m_engineCondition)
	{
		return false;
		std::cout << "Engine have already turned on!" << std::endl;
	}
	else
	{
		m_engineCondition = true;
	}

	return true;
}

bool CCar::TurnOffEngine()
{
	if (m_engineCondition && m_movement == MovementType::stay && m_currentGear == 0)
	{
		m_engineCondition = false;
	}
	else
	{
		return false;
		std::cout << "Engine (have already turned off) (car speed > 0 or/and transmisson not on zero gear" << std::endl;
	}

	return true;
}

bool CCar::SetGear(int gear)
{

	m_movement = GetMovementType();

	switch (gear)
	{
	case -1:
		if (!(m_currentGear < 2 && m_currentSpeed == 0))
		{
			return false;
		}
		break;
	case 0:
		break;
	case 1:
		if (!((m_currentGear < 1 && m_movement == MovementType::stay) || (m_movement == MovementType::foward && m_currentSpeed < 30)))
		{
			return false;
		}
		break;
	case 2:
		if (!(m_movement == MovementType::foward && m_currentSpeed >= 20 && m_currentSpeed <= 50))
		{
			return false;
		}
		break;
	case 3:
		if (!(m_movement == MovementType::foward && m_currentSpeed >= 30 && m_currentSpeed <= 60))
		{
			return false;
		}
		break;
	case 4:
		if (!(m_movement == MovementType::foward && m_currentSpeed >= 40 && m_currentSpeed <= 90))
		{
			return false;
		}
		break;
	case 5:
		if (!(m_movement == MovementType::foward && m_currentSpeed >= 50))
		{
			return false;
		}
		break;
	default:
		std::cout << "You can't set this gear!" << std::endl;
		return false;
	}

	m_currentGear = gear;
	return true;
}

bool CCar::SetSpeed(unsigned speed)
{
	if (!m_engineCondition)
	{
		return false;
		std::cout << "Engine turned off!" << std::endl;
	}

	switch (m_currentGear)
	{
	case -1:
		if (!(speed <= 20))
		{
			return false;
		}
		break;
	case 0:
		if (!(speed <= m_currentSpeed))
		{
			return false;
		}
		break;
	case 1:
		if (!(speed <= 30))
		{
			return false;
		}
		break;
	case 2:
		if (!(speed >= 20 && speed <= 50))
		{
			return false;
		}
		break;
	case 3:
		if (!(speed >= 30 && speed <= 60))
		{
			return false;
		}
		break;
	case 4:
		if (!(speed >= 40 && speed <= 90))
		{
			return false;
		}
		break;
	case 5:
		if (!(speed >= 50 && speed <= 150))
		{
			return false;
		}
		break;
	default:
		std::cout << "You can't set this speed now you should change transmisson!" << std::endl;
		break;
	}

	m_currentSpeed = speed;
	m_movement = GetMovementType();
	return true;
}

void CCar::Info()
{
	std::string workLine = m_engineCondition ? "Engine is turned on;" : "Engine is turned off;";
	std::cout << workLine << std::endl
		<< m_currentSpeed << " -speed of car;" << std::endl
		<< m_currentGear << " -gear of transmission;" << std::endl;

	switch (m_movement)
	{
	case MovementType::stay:
		workLine = "Car stay at now!;";
		break;
	case MovementType::foward:
		workLine = "Car move foward at now!;";
		break;
	case MovementType::back:
		workLine = "Car move back at now!;";
		break;
	}

	std::cout << workLine << std::endl;

}

CCar::MovementType CCar::GetMovementType()
{
	if (m_currentGear > 0 && m_currentSpeed > 0)
	{
		return MovementType::foward;
	}
	else if (m_currentGear < 0 && m_currentSpeed > 0)
	{
		return MovementType::back;
	}
	else if(m_currentSpeed == 0)
	{
		return MovementType::stay;
	}
		
	return m_movement;
}
