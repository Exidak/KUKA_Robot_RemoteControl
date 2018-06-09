// RemoteControl.cpp : Defines the entry point for the console application.
//
/*
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
	catch (ScriptParser::ScriptError error)
	{
		std::cout << "ERROR: ";
		switch (error.err)
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
		std::cout << "\tPosition " << error.pos << std::endl;
	}

    return 0;
}
*/

