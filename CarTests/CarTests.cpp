#include "stdafx.h"
#include "../CCar/Car.h"

struct CarSetFixture
{
	CCar car;
};

BOOST_FIXTURE_TEST_SUITE(Car, CarSetFixture)

	BOOST_AUTO_TEST_CASE(car_engine_turned_off_by_default)
	{
		BOOST_CHECK(!car.TurnOffEngine());
	}

	BOOST_AUTO_TEST_CASE(cant_set_speed_when_engine_turned_off)
	{
		BOOST_CHECK(!car.SetSpeed(10));
	}

	BOOST_AUTO_TEST_CASE(car_engine_can_be_turned_on)
	{
		BOOST_CHECK(car.TurnOnEngine());
	}

	struct when_engine_turned_on_ : CarSetFixture
	{
		when_engine_turned_on_()
		{
			car.TurnOnEngine();
		}
	};

	BOOST_FIXTURE_TEST_SUITE(when_engine_turned_on, when_engine_turned_on_)

		BOOST_AUTO_TEST_CASE(can_set_gear)
		{
			BOOST_CHECK(car.SetGear(1));
		}

		BOOST_AUTO_TEST_CASE(can_set_speed_in_all_of_6_gear_if_speed_in_transmission_range)
		{
			BOOST_CHECK(car.SetGear(1));
			BOOST_CHECK(car.SetSpeed(0));
			BOOST_CHECK(car.SetSpeed(30));

			BOOST_CHECK(car.SetGear(3));
			BOOST_CHECK(car.SetSpeed(30));
			BOOST_CHECK(car.SetSpeed(60));

			BOOST_CHECK(car.SetGear(5));
			BOOST_CHECK(car.SetSpeed(50));
			BOOST_CHECK(car.SetSpeed(150));
		}

		BOOST_AUTO_TEST_CASE(cant_set_if_speed_not_in_transmission_range)
		{
			BOOST_CHECK(car.SetGear(1));
			BOOST_CHECK(!car.SetSpeed(50));
		}

		BOOST_AUTO_TEST_CASE(on_zero_gear_of_transmission_only_can_set_speed_smaller_than_it_have)
		{
			BOOST_CHECK(car.SetGear(1));
			BOOST_CHECK(car.SetSpeed(30));

			BOOST_CHECK(car.SetGear(0));
			BOOST_CHECK(car.SetSpeed(20));
			BOOST_CHECK(!car.SetSpeed(21));
		}

		BOOST_AUTO_TEST_CASE(cant_set_back_gear_while_car_move_foward)
		{
			BOOST_CHECK(car.SetGear(1));
			BOOST_CHECK(car.SetSpeed(30));

			BOOST_CHECK(!car.SetGear(-1));
			BOOST_CHECK(car.SetSpeed(0));
			BOOST_CHECK(car.SetGear(-1));
			BOOST_CHECK(car.SetSpeed(20));
		}

		BOOST_AUTO_TEST_CASE(cant_set_1_gear_while_car_move_back)
		{
			BOOST_CHECK(car.SetGear(-1));
			BOOST_CHECK(car.SetSpeed(20));

			BOOST_CHECK(!car.SetGear(1));
			BOOST_CHECK(car.SetGear(0));
			BOOST_CHECK(!car.SetGear(1));
			BOOST_CHECK(car.SetSpeed(0));
			BOOST_CHECK(car.SetGear(1));
		}

		BOOST_AUTO_TEST_CASE(engine_can_be_turned_off_only_if_car_stay_and_transmission_on_zero)
		{
			BOOST_CHECK(car.SetGear(1));

			BOOST_CHECK(!car.TurnOffEngine());
			BOOST_CHECK(car.SetGear(0));
			BOOST_CHECK(car.TurnOffEngine());
		}
	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()