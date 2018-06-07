#include "stdafx.h"
#include "KUKAPilot.h"

KUKAPilot::KUKAPilot()
{
	speed_rotate = 0;
	speed_move = 0;

	ClientId = simxStart("127.0.0.1", 19999, true, true, 5000, 5);

	simxInt ret;
	ret = simxGetObjectHandle(ClientId, "rollingJoint_fl", &Wheel_back_right, simx_opmode_oneshot_wait);
	ret = simxGetObjectHandle(ClientId, "rollingJoint_rl", &Wheel_front_right, simx_opmode_oneshot_wait);
	ret = simxGetObjectHandle(ClientId, "rollingJoint_fr", &Wheel_back_left, simx_opmode_oneshot_wait);
	ret = simxGetObjectHandle(ClientId, "rollingJoint_rr", &Wheel_front_left, simx_opmode_oneshot_wait);
}


KUKAPilot::~KUKAPilot()
{
	simxFinish(ClientId);
}

void KUKAPilot::setMoveSpeed(double speed)
{
	speed_move = speed;
	resetMovement();
}

void KUKAPilot::setRotationSpeed(double speed)
{
	speed_rotate = speed;
	resetMovement();
}

void KUKAPilot::resetMovement()
{
	simxInt ret;

	ret = simxSetJointTargetVelocity(ClientId, Wheel_back_right, speed_move - speed_rotate/2, simx_opmode_oneshot_wait);
	ret = simxSetJointTargetVelocity(ClientId, Wheel_front_right, speed_move - speed_rotate / 2, simx_opmode_oneshot_wait);
	ret = simxSetJointTargetVelocity(ClientId, Wheel_back_left, speed_move + speed_rotate / 2, simx_opmode_oneshot_wait);
	ret = simxSetJointTargetVelocity(ClientId, Wheel_front_left, speed_move + speed_rotate / 2, simx_opmode_oneshot_wait);
}
