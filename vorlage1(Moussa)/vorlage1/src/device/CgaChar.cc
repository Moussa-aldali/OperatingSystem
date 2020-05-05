#include "device/CgaChar.h"

void CgaChar :: setChar(char c) {
this -> characters = c ;
}


char CgaChar :: getChar () {
    return characters;
}

void CgaChar :: setAttr (const CgaAttr& attr)
{
    cgaAttr = attr; 
}