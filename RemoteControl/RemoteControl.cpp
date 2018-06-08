// RemoteControl.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "KUKAPilot.h"
#include "ScriptParser.h"

int main()
{
	KUKAPilot pilot;
	ComInterpreter com(&pilot);
	ScriptParser scr(&com);

	try {
		scr.runScriptFromFile("script.txt");
	}
	catch (EErrCode err)
	{
		std::cout << "ERROR: ";
		switch (err)
		{
		case RC_ERR_INVALID_TYPE:
			std::cout << "INVALID TYPE";
			break;
		case RC_ERR_SCRIPT_SYNTAX:
			std::cout << "INCORRECT SYNTAX";
			break;
		case RC_ERR_SCRIPT_EXIST:
			std::cout << "SCRIPT ALREADY EXIST";
			break;
		default:
			break;
		}
	}

    return 0;
}

