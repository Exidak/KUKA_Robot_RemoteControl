#pragma once

#include "commands.h"
#include "KUKAPilot.h"

class ComInterpreter
{
public:
	ComInterpreter(KUKAPilot *pilot);
	~ComInterpreter();

	bool execCommand(ECommand cmdCode);

protected:
	KUKAPilot * m_pilot;
};

