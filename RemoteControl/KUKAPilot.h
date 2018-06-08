#pragma once

#ifndef _EXTAPI__
#include "extApi.h"
#endif

class KUKAPilot
{
public:
	KUKAPilot();
	~KUKAPilot();

	// Move backward or toward
	void setMoveSpeed(double speed);
	// Rotate 
	void setRotationSpeed(double speed);
	// Move right
	void moveRight(double speed);
	// Move left
	void moveLeft(double speed);
	// wait until next command
	void waitNextCommand(int msecs);
	//// ARM
	void rotatePlatform(int speed);
private:
	void resetMovement();
	void moveSideways(double speed);
protected:
	simxInt ClientId;

	simxInt Wheel_back_right;
	simxInt Wheel_front_right;
	simxInt Wheel_back_left;
	simxInt Wheel_front_left;
	simxInt sensor;

	simxInt Arm_0;
	simxInt Arm_1;
	simxInt Arm_2;
	simxInt Arm_3;
	simxInt Arm_4;

	double speed_move;
	double speed_rotate;
};

