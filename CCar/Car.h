#pragma once

class CCar
{
public:
	CCar();

	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(int gear);
	bool SetSpeed(unsigned speed);

	void PrintCurrentState() const;

	bool IsEngineOn() const;
	int GetGear() const;
	unsigned GetSpeed() const;

	enum MovementType
	{
		STAY,
		FORWARD,
		BACK,
		NONE
	};

	MovementType GetMovementType() const;

private:
	

	bool m_engineCondition;
	unsigned m_currentSpeed;
	int m_currentGear;
};

