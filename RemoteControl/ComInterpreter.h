#pragma once

#include "commands.h"
#include "KUKAPilot.h"

class ComInterpreter
{
public:
	ComInterpreter(KUKAPilot *pilot);
	~ComInterpreter();

	bool execCommand(ECommand cmdCode, int arg = 1);

protected:
	KUKAPilot * m_pilot;
};

