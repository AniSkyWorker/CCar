#include "stdafx.h"
#include "../CCar/Car.h"

struct Car_
{
	CCar car;
	template <typename Op>
	void ExpectOperationSucceeds(Op && op, int expectedGear, int expectedSpeed, bool engineIsOn = true)
	{
		BOOST_CHECK(op());

		BOOST_CHECK_EQUAL(car.IsEngineOn(), engineIsOn);
		BOOST_CHECK_EQUAL(car.GetGear(), expectedGear);
		BOOST_CHECK_EQUAL(car.GetSpeed(), abs(expectedSpeed));
		BOOST_CHECK(car.GetMovementType() == (expectedSpeed > 0 ? (expectedGear > 0 ? CCar::MovementType::FORWARD : expectedGear == 0 ? CCar::MovementType::NONE : CCar::MovementType::BACK) : CCar::MovementType::STAY));
	}
	template <typename Op>
	void ExpectOperationFails(Op && op)
	{
		const CCar clone(car);

		BOOST_CHECK(!op());

		BOOST_CHECK_EQUAL(car.IsEngineOn(), clone.IsEngineOn());
		BOOST_CHECK_EQUAL(car.GetGear(), clone.GetGear());
		BOOST_CHECK_EQUAL(car.GetSpeed(), clone.GetSpeed());
		BOOST_CHECK_EQUAL(car.GetMovementType(), clone.GetMovementType());
	}
};

BOOST_FIXTURE_TEST_SUITE(Car, Car_)
	BOOST_AUTO_TEST_CASE(can_turn_engine_on)
	{
		ExpectOperationSucceeds([=] { return car.TurnOnEngine();}, 0, 0);
	}
	BOOST_AUTO_TEST_CASE(cant_change_speed)
	{
		ExpectOperationFails([=] { return car.SetSpeed(1);});
	}

	BOOST_AUTO_TEST_CASE(cant_change_gear)
	{
		ExpectOperationFails([=] { return car.SetGear(1);});
	}

	struct when_engine_turned_on : Car_
	{
		when_engine_turned_on()
		{
			car.TurnOnEngine();
		}
	};

	BOOST_FIXTURE_TEST_SUITE(_when_engine_turned_on_, when_engine_turned_on)

		BOOST_AUTO_TEST_CASE(can_set_first_or_back_gear)
		{
			ExpectOperationSucceeds([=] { return car.SetGear(1);}, 1, 0);
			ExpectOperationSucceeds([=] { return car.SetGear(-1);}, -1, 0);
		}

		BOOST_AUTO_TEST_CASE(can_set_speed_in_all_of_6_gear_only_if_speed_in_transmission_range)
		{
			ExpectOperationSucceeds([=] { return car.SetGear(1);}, 1, 0);
			ExpectOperationFails([=] { return car.SetSpeed(-1);});
			ExpectOperationFails([=] { return car.SetSpeed(31);});
			ExpectOperationSucceeds([=] { return car.SetSpeed(0);}, 1, 0);
			ExpectOperationSucceeds([=] { return car.SetSpeed(30);}, 1, 30);

			ExpectOperationSucceeds([=] { return car.SetGear(2);}, 2, 30);
			ExpectOperationFails([=] { return car.SetSpeed(19);});
			ExpectOperationFails([=] { return car.SetSpeed(51);});
			ExpectOperationSucceeds([=] { return car.SetSpeed(20);}, 2, 20);
			ExpectOperationSucceeds([=] { return car.SetSpeed(50);}, 2, 50);

			ExpectOperationSucceeds([=] { return car.SetGear(3);}, 3, 50);
			ExpectOperationFails([=] { return car.SetSpeed(29);});
			ExpectOperationFails([=] { return car.SetSpeed(61);});
			ExpectOperationSucceeds([=] { return car.SetSpeed(30);}, 3, 30);
			ExpectOperationSucceeds([=] { return car.SetSpeed(60);}, 3, 60);

			ExpectOperationSucceeds([=] { return car.SetGear(4);}, 4, 60);
			ExpectOperationFails([=] { return car.SetSpeed(39);});
			ExpectOperationFails([=] { return car.SetSpeed(91);});
			ExpectOperationSucceeds([=] { return car.SetSpeed(40);}, 4, 40);
			ExpectOperationSucceeds([=] { return car.SetSpeed(90);}, 4, 90);

			ExpectOperationSucceeds([=] { return car.SetGear(5);}, 5, 90);
			ExpectOperationFails([=] { return car.SetSpeed(49);});
			ExpectOperationFails([=] { return car.SetSpeed(151);});
			ExpectOperationSucceeds([=] { return car.SetSpeed(50);}, 5, 50);
			ExpectOperationSucceeds([=] { return car.SetSpeed(150);}, 5, 150);
		}

		BOOST_AUTO_TEST_CASE(on_zero_gear_of_transmission_only_can_set_speed_smaller_than_it_have)
		{
			ExpectOperationSucceeds([=] { return car.SetGear(1);}, 1, 0);
			ExpectOperationSucceeds([=] { return car.SetSpeed(30);}, 1, 30);

			ExpectOperationSucceeds([=] { return car.SetGear(0);}, 0, 30);
			ExpectOperationFails([=] { return car.SetSpeed(-1);});
			ExpectOperationFails([=] { return car.SetSpeed(31);});
			ExpectOperationSucceeds([=] { return car.SetSpeed(0);}, 0, 0);
		}

		BOOST_AUTO_TEST_CASE(cant_set_back_gear_while_car_move_foward)
		{
			ExpectOperationSucceeds([=] { return car.SetGear(1);}, 1, 0);
			ExpectOperationSucceeds([=] { return car.SetSpeed(30);}, 1, 30);

			ExpectOperationFails([=] { return car.SetGear(-1);});
			ExpectOperationSucceeds([=] { return car.SetSpeed(0);}, 1, 0);
			ExpectOperationSucceeds([=] { return car.SetGear(-1);}, -1, 0);
			ExpectOperationSucceeds([=] { return car.SetSpeed(20);}, -1, 20);
		}

		BOOST_AUTO_TEST_CASE(cant_set_1_gear_while_car_move_back)
		{
			ExpectOperationSucceeds([=] { return car.SetGear(-1);}, -1, 0);
			ExpectOperationSucceeds([=] { return car.SetSpeed(20);}, -1, 20);

			ExpectOperationFails([=] { return car.SetGear(1);});
			ExpectOperationSucceeds([=] { return car.SetGear(0);}, 0, 20);
			ExpectOperationFails([=] { return car.SetGear(1);});
			ExpectOperationSucceeds([=] { return car.SetSpeed(0);}, 0, 0);
			ExpectOperationSucceeds([=] { return car.SetGear(1);}, 1, 0);
		}

		BOOST_AUTO_TEST_CASE(engine_can_be_turned_off_only_if_car_stay_and_transmission_on_zero)
		{
			ExpectOperationSucceeds([=] { return car.SetGear(1);}, 1, 0);

			ExpectOperationFails([=] { return car.TurnOffEngine();});
			ExpectOperationSucceeds([=] { return car.SetGear(0);}, 0, 0);
			ExpectOperationSucceeds([=] { return car.TurnOffEngine();}, 0, 0, false);
		}

	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()