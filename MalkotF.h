BdokLoach proc
	push bp
	mov bp, sp
	push ax bx cx dx si di
	
	mov si, 0
Ipus_am:
	mov am[si], 0
	inc si
	cmp si, A_GET_LENGTH1
	jc Ipus_am
	
	mov si, 0
Ipus_RL:
	mov RL[si], 0
	inc si
	cmp si, Al_Len
	jc Ipus_RL
	
	mov si, 0
Ipus_LR:
	mov LR[si], 0
	inc si
	cmp si, Al_Len
	jc Ipus_LR
	
	;ss:bp+4 = srak
	mov si, 0 ; s
	dec si
OutL:	inc si	
	cmp si, A_GET_LENGTH0
	jnc @@true
	mov di, 0
	dec di
InL:	inc di
	cmp di, A_GET_LENGTH1
	jnc OutL
If_1:			; if there is a malka
	mov ax, si
	mov bl, A_GET_LENGTH1
	mul bl ; ax = start of this line
	add ax, di
	;mov bx, offset a
	mov bx, ax
	cmp a[bx], 1
	jnz InL
If_2:	;if (++am[a] > 1)
	mov al, am[di]
	cmp al, 0
	jnz @@false
	mov am[di], 1
If_3:	;if (++LR[s - a + arr.GetLength(0)-1] > 1)
	mov bx, si
	sub bx, di
	add bx, A_GET_LENGTH0
	dec bx
	mov al, LR[bx]
	cmp al, 0
	jnz @@false
	mov LR[bx], 1
If_4:	;if (++RL[a + s] > 1)
	mov bx, si
	add bx, di
	mov al, RL[bx]
	cmp al, 0
	jnz @@false
	mov RL[bx], 1
	jmp InL
	
@@false:
	mov cx, 21h
	mov ss:[bp+4], cx
	jmp @@sof
@@true:
	mov cx, 1h
	mov ss:[bp+4], cx
@@sof:
	pop di si dx cx bx ax bp
	ret
BdokLoach endp

TsorLoach proc
	push bp
	mov bp, sp
	push ax bx cx dx si di
	mov si, ss:[bp+4] ; shora
	
@@If_1:	
	cmp si, A_GET_LENGTH0
	jnc @@Else_1
	mov di, 0
	dec di
@@Loolaa:
	inc di
	cmp di, A_GET_LENGTH1
	jnc @@ElSof
	
	mov ax, si
	mov bl, A_GET_LENGTH1
	mul bl ; ax = start of this line
	add ax, di
	mov bx, ax
	
	mov a[bx], 1
	inc si
	push si
	dec si
	call TsorLoach
	mov a[bx], 0
	jmp @@Loolaa
	
@@ElSof: jmp @@sof1	
@@Else_1:

	push 0
	call BdokLoach	
	pop cx
	cmp cx, 1h
	jnz @@sof1

	
	
@@waitForKey: 

			  mov   ah,01H
              int   16H
              jnz   @@gotKey       ;jmp if key is ready
			  jmp @@waitForKey
		
@@gotKey: 			mov ah, 00H        ;key is ready, get it
                    int 16H            ;now process the key
	
	@@tze: 	cmp al,27
		jnz @@cont1
		mov mone, 0
		jmp Lalala
	
@@cont1:	
	push 0
	call GoToXY
	xor dh, dh
	mov dl, mone
	inc dl
	mov mone, dl
	push dx ; num
	push 10 ; basis
	call HamaratBasis
	pop ax
	push 0
	call GoToXY
	push ax
	call printword
	
;	and dl, 11110000b
;	shr dl, 4
;	cmp dl, 10
;	jc daleg1
;	add dl ,7
;daleg1:	
;	add dl, '0'
;	mov ah, 2
;	int 21h
;	mov dl, mone
;	and dl, 00001111b
;	cmp dl, 10
;	jc daleg2
;	add dl ,7
;daleg2:	
;	add dl, '0'
;	mov ah, 2
;	int 21h

	
	push offset a
	push 0
	call ShowMatrice
	
	
@@sof1:
	pop di si dx cx bx ax bp
	ret 2
TsorLoach endp

ShowMatrice	proc
				push bp
				mov bp, sp
				push ax bx dx si
				mov si, [bp+4]
				mov bx, [bp+6]
				mov cl, 23 ; orech malben
				mov ch, A_GET_LENGTH0
	Next:			mov dl, [bx+si]
				cmp dl, 1
				jz @@Malka
				push 0ah ; color
				jmp @@cont
		@@Malka:	push 01h ; color
		@@cont:		mov ax, bx
				sub ax, offset a
				div ch
				mul cl
				add ax, 10
				push ax ; push y
				mov ax, si
				mul cl
				add ax, 5
				push ax ; push x
				call DrawMalben
				;add dl, '0'
				;mov ah, 2
				;int 21h
				inc si
				cmp si, A_GET_LENGTH0
				jc Next
				mov si, 0
				add bx, A_GET_LENGTH0
				cmp bx, offset endMat
				jc Next
				pop si dx bx ax bp
				ret 4								
ShowMatrice	endp

;========================================================================
;Input : 3 Words. 
;			First word - X axis of the pixel of the high right corner.
;			Second word - Y axis of the pixel pixel of the high right corner.
;			Third Word - color
;Return Value : None
;=======================================================================
DrawMalben proc
	push bp
	mov bp, sp
	push ax bx cx dx si di
	mov cx, [bp+4]		;PixelX
	mov dx, [bp+6]		;PixelY
	mov di, [bp+8]		;color
	mov al, 0 ;  x
	mov ah, 0 ;  Y
@@go: 	push di ; color
	push dx ; X
	push cx	; Y
	Call PutPixel
	inc cx
	inc al
	cmp al, 20
	jnz @@go
	sub cx, 20
	xor al, al
	inc dx
	inc ah
	cmp ah, 20
	jnz @@go
	pop di si dx cx bx ax bp
	ret 6
DrawMalben endp