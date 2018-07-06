#ifndef _TMAINPUTCONTROLLER_CPP_
#define _TMAINPUTCONTROLLER_CPP_

#include "ma_classes.h"

REGISTER_CLASS_ID(TMAInputController);

TMAInputController::TMAInputController()
{
    buffHoldDown = NULL;
    buffPressDown = NULL;
}

TMAInputController::~TMAInputController()
{
    clearBuff();
}

void TMAInputController::clearBuff()
{
    if (buffHoldDown) delete buffHoldDown;
    buffHoldDown = NULL;

    if (buffPressDown) delete buffPressDown;
    buffPressDown = NULL;
}

void TMAInputController::setNumControls(int num)
{
    buffSize = num;
    clearBuff();
    buffHoldDown = new bool[buffSize];
    buffPressDown = new bool[buffSize];
    clearStatus();    
}

void TMAInputController::clearStatus()
{
    memset(buffHoldDown,0,buffSize*sizeof(bool));
    memset(buffPressDown,0,buffSize*sizeof(bool));
}

void TMAInputController::clearStatus(int num)
{
    buffHoldDown[num]=false;
    buffPressDown[num]=false;
}
 
void TMAInputController::setStatus(int num,bool status)
{
    buffHoldDown[num]=status;
    if (!status) buffPressDown[num]=false;
}
        
bool TMAInputController::isHoldDown(int num)
{
    return buffHoldDown[num];
}

bool TMAInputController::isAnyHoldDown()
{
    for (int i=0;i<buffSize;i++) if (buffHoldDown[i]) return true;
    return false;
}
    
bool TMAInputController::isPressDown(int num)
{
    if (buffHoldDown[num] && !buffPressDown[num])
    {
        buffPressDown[num] = true;
        return true;
    }
    return false;
}

#endif
