#ifndef _TMAMESSAGE_
#define _TMAMESSAGE_

#include "utils.h"

REGISTER_CLASS_ID(TMAMsg);

TMAMsg::TMAMsg()
{
    msgid=0; source=NULL; param=NULL;
}

TMAMsg::TMAMsg(int id,void *psource,void *pparam)
{
    msgid=id; source=psource; param=pparam;
}

// ----------------------

REGISTER_CLASS_ID(TMAMsgQueue);

TMAMsg TMAMsgQueue::NULL_MSG;

void TMAMsgQueue::putMessage(int id,void *source,void *param)
{
    msgqueue.addElement(new TMAMsg(id,source,param));
}

TMAMsg& TMAMsgQueue::getMessage(void)
{
    if (msgqueue.size()>0)
    {
        PMAMsg msg = (PMAMsg)msgqueue.elementAt(0);
        return *msg;
    }
    return NULL_MSG;
}

void TMAMsgQueue::dispatchMessage(void)
{
    if (msgqueue.size()>0) msgqueue.removeElementAt(0);
}

int TMAMsgQueue::getMessageCount(void)
{
    return msgqueue.size();
}

void TMAMsgQueue::clearQueue(void)
{
    msgqueue.clear();
}

bool TMAMsgQueue::hasMessage(void)
{
    return (msgqueue.size()>0);
}

#endif
