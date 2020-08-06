#include "CardEleven.h"
int CardEleven::card_price=0;
int CardEleven:: fees=0;
int CardEleven::exists=0;
Player* CardEleven:: owner=NULL;

CardEleven::CardEleven(const CellPosition &pos):Card(pos)
{
	cardNumber=11;
}
CardEleven::CardEleven()
{
	cardNumber=11;
}
int CardEleven::getExists()
{
	return exists;
}

void CardEleven::setExists(int ex)
{
	exists=ex;
}

Player* CardEleven::GetOwner()
{
	return owner;
}
void CardEleven::SetOwner(Player* ptr)
{
	owner=ptr;
}

void CardEleven::ReadCardParameters(Grid *pGrid)
{

	if(exists==0)
	{
		Output * pOut = (pGrid)->GetOutput();
		Input * pIn = (pGrid)->GetInput();
		pOut->PrintMessage("CardEleven: Enter Card_price  ...");
		card_price= pIn->GetInteger(pOut);
		pOut->PrintMessage("CardEleven: Enter Fees  ...");
		fees= pIn->GetInteger(pOut);
		exists=1;
	}
}

void CardEleven::Apply(Grid* pGrid, Player* pPlayer)
{

	/*Three cases:
	Case 1 pointer =null then we have to ask the user if he wants to buy
	Case 2 pointer==*player then nothing happens
	Case 3 pointer!=null and pointer!=player then we decrease his wallet
	*/

	// 1- Call Apply() of the base class Card to print the message that you reached this card number
	Card::Apply(pGrid,pPlayer) ;
	Input * pIn = (pGrid)->GetInput();
	Output * pOut = (pGrid)->GetOutput();

	// 2- Decrement the wallet of pPlayer by the walletAmount data member of CardOne
	if(owner==NULL) //no one owns the card
	{
		pOut->PrintMessage("Do you want to buy this Card? Y/N");
		string reply= pIn->GetSrting(pOut);
		if(reply=="Y" && pPlayer->GetWallet() >= card_price)
		{
			pOut->PrintMessage("Congratulations, you've bought the card");
			owner=pPlayer;
			owner->SetWallet( pPlayer->GetWallet() - card_price);
		}
		else if(reply=="Y" &&pPlayer->GetWallet()<card_price)
		{
			pOut->PrintMessage("You don't have enough money!");
		}
		else if(reply=="N" || reply!="Y")
		{
			pOut->PrintMessage("You didn't buy the card.");
		}
	}
	else if(owner==pPlayer)
	{
	} //if theis player owns the card nothing happens

	else if(owner!=pPlayer) //if some player owns this card and this player doesn't he pay the fees
	{
		pPlayer->SetWallet( pPlayer->GetWallet()-fees);
	}
	// pPlayer->SetWallet( pPlayer->GetWallet()+walletAmount);  
}
void CardEleven::Save(ofstream &OutFile) {
	static bool has_been_saved_with_parameters = false ;
	Card::Save(OutFile);

	if(!has_been_saved_with_parameters){
	OutFile << " " << card_price <<" "<< fees << '\n';
	has_been_saved_with_parameters = true ;
	}
	else OutFile<<"\n";
}
void CardEleven::Load(ifstream &Infile,Grid* pGrid){
	static bool has_been_loaded_with_parameters = false ;
	Card::Load(Infile, pGrid);

	if(!has_been_loaded_with_parameters){
	Infile >> card_price >> fees    ;
	has_been_loaded_with_parameters = true ;
	}

	pGrid->AddObjectToCell(this);
}
CardEleven::~CardEleven(void)
{
}
