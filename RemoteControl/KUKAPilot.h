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

	simxInt Wheel_fl;
	simxInt Wheel_rl;
	simxInt Wheel_fr;
	simxInt Wheel_rr;
	simxInt sensor;

	double speed_move;
	double speed_rotate;
};

