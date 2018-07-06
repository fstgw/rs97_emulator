#ifndef _TMARANDOM_CPP_
#define _TMARANDOM_CPP_

#include "utils.h"

REGISTER_CLASS_ID(TMARandom);

void TMARandom::init (unsigned long seed)
{
    if (seed==0) srand(clock());
    else srand(seed);
}

unsigned long TMARandom::nextInt(void)
{
    return rand();
}

unsigned long TMARandom::nextInt(unsigned long valor)
{
    if (valor<2) return 0;
    return (rand()%(valor - 1));
}

#endif
