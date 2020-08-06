#pragma once
#include "Action.h"

class CopyCardAction : public Action
{
	CellPosition* pos;
public:
	CopyCardAction(ApplicationManager *pApp);


	virtual void ReadActionParameters(); 	

	virtual void Execute();

	~CopyCardAction();

};

