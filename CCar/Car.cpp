#include "stdafx.h"
#include "Car.h"

CCar::CCar()
	:m_currentGear(0)
	,m_currentSpeed(0)
	,m_engineCondition(false)
{
}

bool CCar::TurnOnEngine()
{
	if (m_engineCondition)
	{
		std::cout << "Engine have already turned on!" << std::endl;
		return false;
	}

	m_engineCondition = true;
	return true;
}

bool CCar::TurnOffEngine()
{
	if (m_engineCondition && GetMovementType() == MovementType::STAY && m_currentGear == 0)
	{
		m_engineCondition = false;
		return true;
	}
	else
	{
		std::cout << "Engine (have already turned off) (car speed > 0 or/and transmisson not on zero gear" << std::endl;
		return false;
	}
}

bool CCar::SetGear(int gear)
{
	if (!m_engineCondition)
	{
		std::cout << "Engine turned off!" << std::endl;
		return false;
	}

	MovementType movement = GetMovementType();

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
		if (!((m_currentGear < 1 && movement == MovementType::STAY) || (movement == MovementType::FORWARD && m_currentSpeed < 30)))
		{
			return false;
		}
		break;
	case 2:
		if (!(movement == MovementType::FORWARD && m_currentSpeed >= 20 && m_currentSpeed <= 50))
		{
			return false;
		}
		break;
	case 3:
		if (!(movement == MovementType::FORWARD && m_currentSpeed >= 30 && m_currentSpeed <= 60))
		{
			return false;
		}
		break;
	case 4:
		if (!(movement == MovementType::FORWARD && m_currentSpeed >= 40 && m_currentSpeed <= 90))
		{
			return false;
		}
		break;
	case 5:
		if (!(movement == MovementType::FORWARD && m_currentSpeed >= 50))
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
		std::cout << "Engine turned off!" << std::endl;
		return false;
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
	return true;
}

void CCar::PrintCurrentState() const
{
	std::string workLine = m_engineCondition ? "Engine is turned on;" : "Engine is turned off;";
	std::cout << workLine << std::endl
		<< m_currentSpeed << " -speed of car;" << std::endl
		<< m_currentGear << " -gear of transmission;" << std::endl;

	switch (GetMovementType())
	{
	case MovementType::STAY:
		workLine = "Car stay at now!;";
		break;
	case MovementType::FORWARD:
		workLine = "Car move foward at now!;";
		break;
	case MovementType::BACK:
		workLine = "Car move back at now!;";
		break;
	}

	std::cout << workLine << std::endl;

}

CCar::MovementType CCar::GetMovementType() const
{
	if (m_currentGear > 0 && m_currentSpeed > 0)
	{
		return MovementType::FORWARD;
	}
	else if (m_currentGear < 0 && m_currentSpeed > 0)
	{
		return MovementType::BACK;
	}
	else if (m_currentSpeed == 0)
	{
		return MovementType::STAY;
	}

	return MovementType::NONE;
}
