#include "stdafx.h"
#include "KUKAPilot.h"

KUKAPilot::KUKAPilot()
{
	ClientId = simxStart("127.0.0.1", 19999, true, true, 5000, 5);

	simxInt ret;
	ret = simxGetObjectHandle(ClientId, "rollingJoint_fl", &Wheel_fl, simx_opmode_oneshot_wait);
	ret = simxGetObjectHandle(ClientId, "rollingJoint_rl", &Wheel_rl, simx_opmode_oneshot_wait);
	ret = simxGetObjectHandle(ClientId, "rollingJoint_fr", &Wheel_fr, simx_opmode_oneshot_wait);
	ret = simxGetObjectHandle(ClientId, "rollingJoint_rr", &Wheel_rr, simx_opmode_oneshot_wait);
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
	ret = simxSetJointTargetVelocity(ClientId, Wheel_fl, -3.1415f * 0.25f, simx_opmode_oneshot_wait);
	ret = simxSetJointTargetVelocity(ClientId, Wheel_rl, -3.1415f * 0.25f, simx_opmode_oneshot_wait);
	ret = simxSetJointTargetVelocity(ClientId, Wheel_fr, 3.1415f * 0.25f, simx_opmode_oneshot_wait);
	ret = simxSetJointTargetVelocity(ClientId, Wheel_rr, 3.1415f * 0.25f, simx_opmode_oneshot_wait);
}
