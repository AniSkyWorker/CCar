#pragma once

class CCar
{
	enum MovementType	
	{
		stay,
		foward,
		back
	};

public:
	CCar();

	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(int gear);
	bool SetSpeed(unsigned speed);

	void Info();

private:
	MovementType GetMovementType();

	bool m_engineCondition;
	MovementType m_movement;
	unsigned m_currentSpeed;
	int m_currentGear;
};

