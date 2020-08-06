#include "CopyCardAction.h"

#include "Grid.h"
#include "Input.h"
#include "Output.h"

#include "Card.h"

CopyCardAction::CopyCardAction(ApplicationManager *pApp) : Action(pApp)
{
}
void CopyCardAction::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	pOut->PrintMessage("click on the source cell...");
}
void CopyCardAction::Execute()
{
	ReadActionParameters();
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	Card*pCard=NULL;
	pos=new CellPosition(pIn->GetCellClicked());
	if(pos->IsValidCell() )
	{
		pCard=( pGrid->GetCard(*pos) );// will point to the card object type
	}
	else
		return;

	if( pGrid->GetCard(*pos) )
	{
		pGrid->SetClipboard(pCard);
		pOut->ClearStatusBar();
	}
	else
	{
		pGrid->SetClipboard(NULL);
		pOut->ClearStatusBar();
		return;
	}

}
CopyCardAction::~CopyCardAction()
{
}
