#pragma once

#include "ActionPlayBy.h"


// ... rest of the implementation

class ApplicationManager;
class ActionPlayBy;

class ActionPlayByType : public ActionPlayBy
{

public:
	ActionPlayByType(ApplicationManager* pApp);

	void Execute();
};