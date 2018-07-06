#ifndef _TMAFILEREADER_CPP_
#define _TMAFILEREADER_CPP_

#include "utils.h"

REGISTER_CLASS_ID(TMAFileReader);

long TMAFileReader::getCurrentOffset(FILE* f)
{ 
    return ftell(f);
}

bool TMAFileReader::seekTo(FILE* f,long pos)
{
     return (fseek(f,pos,SEEK_SET)==0);
}

long TMAFileReader::getBytes(FILE* f,void *buff,long size)
{
    return fread(buff,size,1,f);
}

unsigned char TMAFileReader::getByte(FILE* f)
{
    return fgetc(f);
}

unsigned int  TMAFileReader::get2BWord(FILE* f)
{
    unsigned char b1,b2;
    b2 = getByte(f);
	b1 = getByte(f);
	return (b1 << 8) + b2;
}

int  TMAFileReader::get2BWordSigned(FILE* f)
{
    int b1,b2;
    b2 = getByte(f);
	b1 = getByte(f);
	long l = ((b1 << 8) | b2);
	if (l & 0x8000) l=l-65536;
	return (int)l;
}

unsigned long TMAFileReader::get4BWord(FILE* f)
{
	unsigned long w1,w2;
	w2 = get2BWord(f);
	w1 = get2BWord(f);	
	return (w1 << 16) + w2;		
}

TMAString TMAFileReader::getString(FILE* f,int size)
{ 
	TMAString s;
	char *buff = new char[size+1],*index=buff;
	buff[size]=0;
	
    while (size>0)
	{
		int c = getByte(f);
		if (c>=0)
		{
			size--;
			if (c>0) { *index=c; index++; }
		}
		else size=0;
	}
	*index=0;
	s = buff;
	return s;
}
	

#endif
