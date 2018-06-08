#include "stdafx.h"

#include <chrono>
#include <thread>

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

	ret = simxGetObjectHandle(ClientId, "youBotArmJoint0", &Arm_0, simx_opmode_oneshot_wait);
	ret = simxGetObjectHandle(ClientId, "youBotArmJoint1", &Arm_1, simx_opmode_oneshot_wait);
	ret = simxGetObjectHandle(ClientId, "youBotArmJoint2", &Arm_2, simx_opmode_oneshot_wait);
	ret = simxGetObjectHandle(ClientId, "youBotArmJoint3", &Arm_3, simx_opmode_oneshot_wait);
	ret = simxGetObjectHandle(ClientId, "youBotArmJoint4", &Arm_4, simx_opmode_oneshot_wait);
}


KUKAPilot::~KUKAPilot()
{
	simxFinish(ClientId);
}

void KUKAPilot::setMoveSpeed(double speed)
{
	speed_move = -speed;
	resetMovement();
}

void KUKAPilot::setRotationSpeed(double speed)
{
	speed_rotate = -speed;
	resetMovement();
}

void KUKAPilot::moveRight(double speed)
{
	moveSideways(speed);
}

void KUKAPilot::moveLeft(double speed)
{
	moveSideways(-speed);
}

void KUKAPilot::waitNextCommand(int msecs)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(msecs));
}

void KUKAPilot::rotatePlatform(int pos)
{
	simxInt ret;

	ret = simxSetJointPosition(ClientId, Arm_0, 180.0f, simx_opmode_oneshot_wait);
}

void KUKAPilot::resetMovement()
{
	simxInt ret;

//	simxPauseCommunication(ClientId, 1);
	ret = simxSetJointTargetVelocity(ClientId, Wheel_back_right, speed_move + speed_rotate/2, simx_opmode_oneshot_wait);
	ret = simxSetJointTargetVelocity(ClientId, Wheel_front_right, speed_move + speed_rotate / 2, simx_opmode_oneshot_wait);
	ret = simxSetJointTargetVelocity(ClientId, Wheel_back_left, speed_move - speed_rotate / 2, simx_opmode_oneshot_wait);
	ret = simxSetJointTargetVelocity(ClientId, Wheel_front_left, speed_move - speed_rotate / 2, simx_opmode_oneshot_wait);
//	simxPauseCommunication(ClientId, 0);
}

void KUKAPilot::moveSideways(double speed)
{
	simxInt ret;

//	simxPauseCommunication(ClientId, 1);
	ret = simxSetJointTargetVelocity(ClientId, Wheel_back_right, -speed, simx_opmode_oneshot_wait);
	ret = simxSetJointTargetVelocity(ClientId, Wheel_front_right, speed, simx_opmode_oneshot_wait);
	ret = simxSetJointTargetVelocity(ClientId, Wheel_back_left, speed, simx_opmode_oneshot_wait);
	ret = simxSetJointTargetVelocity(ClientId, Wheel_front_left, -speed, simx_opmode_oneshot_wait);
//	simxPauseCommunication(ClientId, 0);
}
