#include "io/PrintStream.h"

PrintStream :: PrintStream(OutputChannel* chan) : channel(*chan)
{
}

PrintStream :: PrintStream(OutputChannel& chan) : channel(chan)
{
}

void PrintStream :: print(const char* str){
	
	int i = 0;
	while (str[i] != '\0'){
		i++;		//Länge des Strings ermitteln
	}
	channel.write(str, i);	//für die Länge des Strings Zeichen ausgeben
}

void PrintStream :: print(char ch){
	channel.write(ch);
}

void PrintStream :: println(const char* str){
	print(str);
	println();
}

void PrintStream :: println(){
	print('\n');			//Zeile "ausgeben"
	}

void PrintStream :: print (int x, int base){
	
	if (x<0) {		
		print('-');
		x *= (-1);		//x auf positiv setzen
	}
	
	print((unsigned) x, base);
}

void PrintStream :: print(unsigned x, int base){
	
	if(!((base == 2) || (base == 10) || (base == 16))){
		print("Fehler: Falsche Basis");
		return;	
	}

	int maxLength = 32;
	char digits[17] = "0123456789ABCDEF";	
	char result[maxLength];

	int modulo = 0;
	int resultLength = 0;

	while((x != 0) && resultLength < maxLength){ 	//Algorithmus für Basendarstellung
		x = x / base;
		modulo = x % base;
		result[resultLength] = digits[modulo];		
		resultLength++;
	}
	
	switch(base){
		case 2: print("0b");
			break;
		case 10: print("0d");
			break;
		case 16: print("0x");
			break;
	}
	
	if (resultLength == 0){
		print("0");
	} else {
		for (int i = resultLength; i >= 0; i--){
			print(result[i]);
		}
	}
}


void PrintStream :: print(void* p){

	print((unsigned int) p, HEX);
}


	