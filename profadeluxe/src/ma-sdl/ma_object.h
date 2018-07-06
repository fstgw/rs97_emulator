#ifndef _MA_OBJECT_H_
#define _MA_OBJECT_H_

#define REGISTER_CLASS\
    virtual long classID() { return (long)&CLASS_ID; }
    
#define PUBLIC_CLASS_ID\
    static short CLASS_ID    
    
#define REGISTER_CLASS_ID(X)\
    short X::CLASS_ID=0
    
#define CLASS_ID(X) (long)&X::CLASS_ID

// Debe implementarse está función como punto de entrad
// del programa
//
extern int MainProc(int argc, char** argv);

// ******************************************
// Superclase de toda la jerarquia de objetos
// ******************************************
//
class TMAObject
{
    REGISTER_CLASS protected:          
    public:                 
        PUBLIC_CLASS_ID;  
        bool isInstanceOf(long class_id);
        long getClassID(void);
        virtual ~TMAObject()=0;
};
typedef TMAObject *PMAObject;

#endif
