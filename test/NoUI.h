#ifndef NOUI_H_INCLUDED
#define NOUI_H_INCLUDED

class NoUi : public GameUI {

public:
    NoUi(){}
    virtual ~NoUi() {}

    virtual unsigned int requestCard(list<Card*>* hand){return 0;};
    virtual void playFailed(){};
    virtual void playSucceeded(){};

};

#endif // NOUI_H_INCLUDED
