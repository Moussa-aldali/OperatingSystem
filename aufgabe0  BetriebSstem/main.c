#include <stdio.h>
#include <math.h>

extern int getDivisorCountNoBasepointer(unsigned int value);

extern void getDivisorCountwithBasepointer(int value, int *result);

int main() {

    long long uNummber, nummber;
    int option, dcouner1, dcounter2;
    char answer;

    do {
        printf("Specify the method (0 - without base pointer, 1 - with base pointer):");
        scanf("%d", &option);
	
    }
   
    while (option != 0 && option != 1);
    
    if (option == 0) {

	printf("Enter a number:");
    	scanf("%lld", &uNummber); 
	
	if(0 > uNummber ){
	
	 
	printf("Your number doesn't fit in the unsigned range! \n");
	
	}
	
	 else if(uNummber > pow(2, 32)){
	
	printf("Your number doesn't fit in the unsigned range! \n");
	
	}
	 else if(0 < uNummber < pow(2, 32)){

	  
   	    dcouner1 = getDivisorCountNoBasepointer(uNummber);
   	 printf("The number of dividers is: %d\n", dcouner1);

	   }
	    

    }else {
    
	printf("Enter a number:");
    	scanf("%lld", &nummber); 
	
	if((-pow(2, 31) < nummber) && (nummber < pow(2, 31))){
		if(nummber < 0){
		getDivisorCountwithBasepointer(nummber*(-1), &dcounter2);
		printf("The number of dividers is:  %d\n", dcounter2);
		}else{
		getDivisorCountwithBasepointer(nummber, &dcounter2);
		printf("The number of dividers is:  %d\n", dcounter2);
		}

		 
	}else{    
	
             printf("Your number doesn't fit in the range of int!\n"); 
	     	     
	}
	
    }
    
    return 0;
}