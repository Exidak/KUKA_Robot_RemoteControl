#pragma once

#ifndef _EXTAPI__
#include "extApi.h"
#endif

class KUKAPilot
{
public:
	KUKAPilot();
	~KUKAPilot();

	void setMoveSpeed(double speed);
	void setRotationSpeed(double speed);
private:
	void resetMovement();
protected:
	simxInt ClientId;

	simxInt Wheel_back_right;
	simxInt Wheel_front_right;
	simxInt Wheel_back_left;
	simxInt Wheel_front_left;
	simxInt sensor;

	double speed_move;
	double speed_rotate;
};

