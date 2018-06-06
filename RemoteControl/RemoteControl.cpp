// RemoteControl.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "KUKAPilot.h"
#include "ComInterpreter.h"

int execMenu()
{
	int code;
	system("cls");
	std::cout << "8 - move forward" << std::endl;
	std::cout << "2 - move backward" << std::endl;
	std::cout << "5 - stop move" << std::endl;
	std::cout << "6 - rotate right" << std::endl;
	std::cout << "4 - rotate left" << std::endl;
	std::cout << "0 - exit" << std::endl;
	std::cin >> code;
	return code;
}

int main()
{
	KUKAPilot pilot;
	ComInterpreter com(&pilot);

	int code = execMenu();
	while (code != 0)
	{
		switch (code)
		{
		case 8:
			com.execCommand(RC_CMD_MOVE_FORWARD);
			break;
		case 2:
			com.execCommand(RC_CMD_MOVE_BACKWARD);
			break;
		case 5:
			com.execCommand(RC_CMD_STOP_MOVEMENT);
			break;
		case 4:
			com.execCommand(RC_CMD_ROTATE_LEFT);
			break;
		case 6:
			com.execCommand(RC_CMD_ROTATE_RIGHT);
			break;
		default:
			break;
		}
		code = execMenu();
	}

    return 0;
}

