// RemoteControl.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "KUKAPilot.h"

int main()
{
	KUKAPilot pilot;
	pilot.setMoveSpeed(1);
	
	for (int i = 0; i < 1000000000; i++)
		i = i;

	pilot.setMoveSpeed(-1);

    return 0;
}

