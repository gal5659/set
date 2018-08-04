DClick proc
	push bp
	mov bp, sp
	push ax bx cx dx si di
	mov ax, CursorX
	cmp ax, 141
	jz @@tse
	push 0 ; black frame
	push CursorX
	push CursorY
	call DrawFrame
	mov di, CardNow
	inc di	
	inc di
	mov CardNow, di
	push 0eh ; yellow frame
	mov cx, CursorX
	add cx, 67
	mov CursorX, cx
	push CursorX ; x
	push CursorY ; y
	call DrawFrame
@@tse:	pop di si dx cx bx ax bp
	ret
DClick endp


AClick proc
	push bp
	mov bp, sp
	push ax bx cx dx si di
	mov ax, CursorX
	cmp ax, 7
	jz @@tse
	push 0 ; black frame
	push CursorX
	push CursorY
	call DrawFrame
	mov di, CardNow
	dec di	
	dec di
	mov CardNow, di
	push 0eh ; yellow frame
	mov cx, CursorX
	sub cx, 67
	mov CursorX, cx
	push CursorX ; x
	push CursorY ; y
	call DrawFrame
@@tse:	pop di si dx cx bx ax bp
	ret
AClick endp

WClick proc
	push bp
	mov bp, sp
	push ax bx cx dx si di
	mov ax, CursorY
	cmp ax, 7
	jz @@tse
	push 0 ; black frame
	push CursorX
	push CursorY
	call DrawFrame
	mov di, CardNow
	sub di, 6	
	mov CardNow, di
	push 0eh ; yellow frame
	mov dx, CursorY
	sub dx, 37
	mov CursorY, dx
	push CursorX ; x
	push CursorY ; y
	call DrawFrame
@@tse:	pop di si dx cx bx ax bp
	ret
WClick endp

SClick proc
	push bp
	mov bp, sp
	push ax bx cx dx si di
	mov ax, COB_Len
	cmp ax, 15
	jz @@15cards
@@12cards:	mov ax, CursorY
	cmp ax, 118
	jz @@tse
	jmp @@do
@@15cards:
	mov ax, CursorY
	cmp ax, 155
	jz @@tse
@@do:	push 0 ; black frame
	push CursorX
	push CursorY
	call DrawFrame
	mov di, CardNow
	add di, 6	
	mov CardNow, di
	push 0eh ; yellow frame
	mov dx, CursorY
	add dx, 37
	mov CursorY, dx
	push CursorX ; x
	push CursorY ; y
	call DrawFrame
@@tse:	pop di si dx cx bx ax bp
	ret
SClick endp

QClick proc
	push bp
	mov bp, sp
	push ax bx cx dx si di
	;push 0 ; black
	;push 10
	;push 300
	;call PutPixel
	mov si, CardNow
	mov ax, COB[si]
	xor ax, 1000000000000000b
	mov COB[si], ax
	shl ax, 1
	jc @@Checking
	shr ax, 1
	mov COB[si], ax
	mov di, MoneChosenCards
	dec di
	dec di
	mov MoneChosenCards, di
	mov SetCharacters[di], 0
	mov SetIndexim[di], 0
	mov si, CardNow
	push si
	push 0
	call GetHighRightCorner
	pop dx ; y
	pop cx ; x
	push 0eh
	push cx ; x
	push dx ; y
	call DrawFrame

	jmp @@tse

@@Checking:
		mov si, CardNow
		mov di, MoneChosenCards
		mov ax, COB[si]
		mov SetCharacters[di], ax
		mov SetIndexim[di], si
		cmp di,4 
		jz @@3AreChosen
		inc di
		inc di
		mov MoneChosenCards, di
		jmp @@tse
@@3AreChosen:
		push SetCharacters[0]
		push SetCharacters[2]
		push SetCharacters[4]
		call CheckSet
		pop ax
		cmp ax, 1
		jz @@TrueSet
		jmp @@KolMikre
	@@TrueSet:
		mov ax, MoneSetim
		inc ax
		mov MoneSetim, ax
		call MesumanimLeEfesCOB
		call TsamtsemCOB
		cmp COB_Len, 15
		jnz @@12cards
		mov COB_Len, 12
		call Clear15
		jmp @@KolMikre
		
			@@12cards:
					
				@@aa:	mov di, 18 
					push 0
					call Rand1to81
					pop si
					add si, si
					mov bx, CardsPack[si]
					shl bx, 1
					jc @@aa
					mov bx, CardsPack[si]
					xor bx, 1000000000000000b
					mov CardsPack[si], bx
					xor bx, 1000000000000000b
					mov COB[di], bx
					inc di
					inc di
					jmp @@bb
					
					
	;@@ElKolMikre:	jmp @@KolMikre	
	
	
	
				@@bb:	push 0
					call Rand1to81
					pop si
					add si, si
					mov bx, CardsPack[si]
					shl bx, 1
					jc @@bb
					mov bx, CardsPack[si]
					xor bx, 1000000000000000b
					mov CardsPack[si], bx
					xor bx, 1000000000000000b
					mov COB[di], bx
					inc di
					inc di
					
				@@cc:	push 0
					call Rand1to81
					pop si
					add si, si
					mov bx, CardsPack[si]
					shl bx, 1
					jc @@cc
					mov bx, CardsPack[si]
					xor bx, 1000000000000000b
					mov CardsPack[si], bx
					xor bx, 1000000000000000b
					mov COB[di], bx
					
	
	@@KolMikre:
		
		xor si, si
		mov bx, COB_Len
		add bx, COB_Len
	@@go:
		mov ax, COB[si]				;clear all (first bit)
		and ax, 0111111111111111b
		mov COB[si], ax
		inc si
		inc si
		cmp si, bx ; bx = 2*(COB_Len)
		jnz @@go
		
		mov SetIndexim[0], 0
		mov SetIndexim[2], 0
		mov SetIndexim[4], 0
		mov SetCharacters[0], 0
		mov SetCharacters[2], 0
		mov SetCharacters[4], 0
		mov MoneChosenCards, 0
		call DrawCOB
	
@@tse:	pop di si dx cx bx ax bp
	ret
QClick endp


ThreeClick proc
	push bp
	mov bp, sp
	push ax bx cx dx si di
	mov COB_Len, 15
	mov di, 24
				@@aa:	push 0
					call Rand1to81
					pop si
					add si, si
					mov bx, CardsPack[si]
					shl bx, 1
					jc @@aa
					mov bx, CardsPack[si]
					xor bx, 1000000000000000b
					mov CardsPack[si], bx
					xor bx, 1000000000000000b
					mov COB[di], bx
					inc di
					inc di
					
				@@bb:	push 0
					call Rand1to81
					pop si
					add si, si
					mov bx, CardsPack[si]
					shl bx, 1
					jc @@bb
					mov bx, CardsPack[si]
					xor bx, 1000000000000000b
					mov CardsPack[si], bx
					xor bx, 1000000000000000b
					mov COB[di], bx
					inc di
					inc di
					
				@@cc:	push 0
					call CheckIfSof
					pop ax
					cmp ax, 0
					jz @@con1
					jmp EmptyCardsPack
				@@con1:	push 0
					call Rand1to81
					pop si
					add si, si
					mov bx, CardsPack[si]
					shl bx, 1
					jc @@cc
					mov bx, CardsPack[si]
					xor bx, 1000000000000000b
					mov CardsPack[si], bx
					xor bx, 1000000000000000b
					mov COB[di], bx
		
		
		call DrawCOB	
					
					
@@tse:	pop di si dx cx bx ax bp
	ret
ThreeClick endp