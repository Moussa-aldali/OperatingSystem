#include "device/CgaScreen.h"
#include "lib/tools.h"

CgaScreen :: CgaScreen() : index ( Indexregister) , data(Datenregister)
{
    screen = (CgaChar*) offsetVram;
    clear();
}

CgaScreen :: CgaScreen(CgaAttr attr) : index(Indexregister), data(Datenregister) {
    screen = (CgaChar*) offsetVram;
    this -> CgaScreen :: attr = attr ; 
    clear();
}

void CgaScreen :: clear(){
const CgaAttr cleaAttr ; 
for( unsigned row = 0 ; row < Screen :: ROWS; row ++){
    for( unsigned col = 0 ; col < Screen ::COLUMNS ; col ++){
        screen[row].setChar(' ');
        screen[col].setAttr(attr);
    }
}
setCursor(0,0);

}

void CgaScreen :: scroll () {

    memcpy(screen, screen + COLUMNS , 3840 );
    for( int i = ROWS * COLUMNS -80 ; i < ROWS * COLUMNS ; i++){
        CgaScreen :: screen[i].setAttr(attr);
        CgaScreen :: screen[i].setChar(' ');
    }
    setCursor(0,24);
}

void CgaScreen :: setCursor (int column , int row) {
    unsigned pos = row * Screen :: COLUMNS + column ;
    unsigned posHigh = pos >> 8 ; 
    unsigned posLow = (pos & 0xff)& 0xff;
//lowbyte
    index.write(LOW);
    index.write(posLow);
//Highbyte
    index.write(HIGH);
    index.write(posHigh);

}

void CgaScreen :: getCursor ( int& column , int& row){

unsigned int pos ;
index.write(HIGH);
 unsigned posHigh = data.read() << 8;

 index.write(LOW);
 unsigned posLow = data.read();

pos = posHigh | posLow ; 
column = (int) pos % COLUMNS;
row = (int) pos / COLUMNS;  

}

void CgaScreen :: show(char ch, const CgaAttr& attr) {
    int column , row ; 
    getCursor(column , row);
    unsigned pos = row * COLUMNS + column;

        screen[pos].setAttr(attr);
        screen[pos].setChar(ch);

       	if (column == COLUMNS - 1) {
				if (row == ROWS - 1) {

					scroll();
					row = ROWS - 1;

				} else {
					row++;
				}
				column = 0;
			} else {
				
				column++;
			}
			setCursor(column, row);
        

}

void CgaScreen :: show(char ch) {

}



