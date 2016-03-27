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
	~CCar();

	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(int gear);
	bool SetSpeed(unsigned speed);

private:
	bool engineCondition;
	MovementType movement;
	unsigned currentSpeed;
	int currentGear;
};

