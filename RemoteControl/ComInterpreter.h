#pragma once

#include "commands.h"
#include "KUKAPilot.h"

class ComInterpreter
{
public:
	ComInterpreter();
	~ComInterpreter();

	bool connect();
	bool execCommand(ECommand cmdCode, int arg = 1);

protected:
	KUKAPilot * m_pilot;
};

