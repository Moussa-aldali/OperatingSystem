;
;	    nasm -f elf -o main.o bp_noBp.asm
;   	gcc -m32 -c -o c.o main.c
;	    gcc -m32 -o run main.o c.o
;       ./run

; funktionen die verwendet werden sollen
global getDivisorCountNoBasepointer ; funktion ohne zeiger

global getDivisorCountwithBasepointer                     ; funktion mit zeiger

getDivisorCountwithBasepointer:         

    push    ebp                             ; start des programmes um segmentierungsfehler zu vermeiden
    mov	    ebp, esp                        ; aktueller basepointer
    push    ebx                             ; [ebp -4], segmentierungsfehler verhindern
    mov     ebx, [ebp + 8]                  ; speicheradresse unter der das ergebnis gespeichert werden soll

    mov     ecx, [ebp + 8]                  ; speicheradresse unter der das ergebnis gespeichert werden soll
 
    mov     ebx, 0                          ; werte 0 in ebx 


chkdiv:                     

    cmp ecx, 0                              ; division durch null verhindern
    je  end                                 ; springe zum ende bei emp gleich null
    mov eax, [ebp +8]                       ; speicheradresse unter der das ergebnis gespeichert werden soll
    mov edx, 0                              ; edx null wert immer geben 
    div ecx 
    cmp edx, 0 
    jne chkdiv_no_count                     ; wenn gleich 0 dann counter um +1 setzen
    inc ebx 

chkdiv_no_count:

    loop chkdiv                             ; schleife zurueck und dekrementiert, ecx ist teiler von eax

end:
   
    mov eax, [ebp+12]                      ; eax die Addrieserung von ebp bekommen werden soll
    mov [eax], ebx                         ; gerbe die werte von ebx in eax da wird es in returen benutzt 
    pop	ebx                                ; stabel entlernen 
    pop ebp                                ; stbel entlernen 
    ret                                    ; return to caller

;-------------------------------------------------------------------------------------------------------------------
;funktion ohne zeiger
getDivisorCountNoBasepointer:        


	push ebx                               ; counter des teilers
	
	mov eax, [esp+8]                       ; schreibe eax mit value um
	mov ecx, [esp+8]                       ; schreibe eax mit value um
	mov ebx, 0                             ; counter auf 0
	cmp eax, 0                             ; kontrolle wenn der wert 0 ist
	je exit1	                           ; wenn ja dann beende

chkdiv1: 
	cmp ecx, 0	                           ;controll if dividor=0
	je exit1		                       ;if yes ->exit

	mov eax, [esp+8]                       ;rewrite eax with value
	mov edx, 0                             ;set rest on 0

	div ecx                                ; divide with loop-counter

	cmp edx, 0                             ;controll if rest=0
	jne chkdiv_no_count1                   ;if not jump to next loop
	inc ebx                                ;if yes-> counter+1
	
chkdiv_no_count1:
	dec ecx                               ; schleifenzaehler -1
	jmp chkdiv1                           ; zur ersten schleife springen

exit1:

	mov eax, ebx                         ; gespeicherte anzahl von teilern in eax
	pop ebx                              ; entleeren des stacks
	ret                                  ; return zu aufruf
