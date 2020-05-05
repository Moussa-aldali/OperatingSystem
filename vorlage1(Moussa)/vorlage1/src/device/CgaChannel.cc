#include "device/CgaChannel.h"
#include "device/CgaAttr.h"
#include "device/CgaScreen.h"

CgaChannel :: CgaChannel() {
    CgaScreen();
}

CgaChannel :: CgaChannel ( const CgaAttr& attr)
{
    CgaChannel();
    setAttr(attr);
}

int CgaChannel :: write (const char* data , int size){
for(int i = 0 ; i < size ; i++){
    if (data[i]=='\n')
    {
       zeileInc();
    }
    else if (data[i]=='\r')
    {
        cursorFort();
    }
    else {
        show(data[i]);
    }
    
}
return (size -1);

}
int column ; 
int row ; 


void CgaChannel :: blueScreen(const char* error){
    clear();
    CgaAttr attError ( CgaAttr :: WHITE , CgaAttr :: BLUE , false);
    setAttr(attError);
    for(int i = 0 ; i <ROWS ; i++){
        for(int j = 0 ; j < COLUMNS ; j++)
        {
            setCursor(j,i);
        }

    }

    setCursor(30,12);
    int i = 0; 
    while (error[i] !=0)
    {
       i++;
    }
    write(error,i);

}

void CgaChannel :: zeileInc (){
    getCursor(column, row);
    if(row == 24){
        scroll();
    }
    else
    {
        setCursor(0,row +1);
    }
}

void CgaChannel :: cursorFort(){
    setCursor(0,row);

} 



