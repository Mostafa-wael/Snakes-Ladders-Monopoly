#include "CutCardAction.h"

#include "Grid.h"
#include "Input.h"
#include "Output.h"

#include "Card.h"

CutCardAction::CutCardAction(ApplicationManager *pApp) : Action(pApp)
{
}
void CutCardAction::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	pOut->PrintMessage("click on the source cell...");

}
void CutCardAction::Execute()
{
	ReadActionParameters();
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	Card* pCard=NULL;
	pos=new CellPosition(pIn->GetCellClicked());
	if( pos->IsValidCell() )
	{
		pCard=( pGrid->GetCard(*pos) );// will point to the card object type
	}
	else
		return;
	if( pGrid->GetCard(*pos) )
	{
		CellPosition pPos(-1,-1);
		Card* P=new Card(pPos);
		*P=*pCard;
		pGrid->SetClipboard(P);
		pGrid->RemoveObjectFromCell(*pos);
		pOut->ClearStatusBar();
	}
	else
	{
		pGrid->SetClipboard(NULL);
		pOut->ClearStatusBar();
		return;
	}


}
CutCardAction::~CutCardAction()
{
}
