#include "GoFishUI.h"
#include <iostream>

unsigned int GoFishUI::requestCard(list<Card*>* hand)
{
    cout << "Your hand:" << endl;
    unsigned int index = 0;
    for(list<Card*>::iterator i = hand->begin(); i != hand->end(); ++i)
    {
        Card::Rank r = (*i)->rank;
        cout << "\tChoice " << (++index) << ": " << Card::getRank(r) << endl;
    }
    cout << "Select a choice: ";

    unsigned int selection;
    cin >> selection;

    return selection-1;
}

void GoFishUI::playFailed()
{
    cout << "Go Fish!" << endl;
}

void GoFishUI::playSucceeded()
{
    cout << "The player had some of those cards!" << endl;
}
