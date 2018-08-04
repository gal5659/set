
Clear15 proc	
;	push bp
;	mov bp, sp
;	push ax bx cx dx si di di
;	mov dx, 150
;@@go: 	
;	push 0 ; black color
;	push dx ; y
;	push 199
;	push 5
;	call DrawHLine
;	cmp dx, 195
;	jnz @@go
;	pop di si dx cx bx ax bp
;	ret

	push bp
	mov bp, sp
	push ax bx cx dx si di
	mov cx, 1
	mov dx, 150		;PixelY
	mov di, 0h ; black color
	mov al, 0 ;  x
	mov ah, 0 ;  Y
@@go: 	push di ; color
	push dx ; X
	push cx	; Y
	Call PutPixel
	inc cx
	inc al
	cmp al, 210
	jnz @@go
	sub cx, 210
	xor al, al
	inc dx
	inc ah
	cmp ah, 50
	jnz @@go
	call WClick
	pop di si dx cx bx ax bp
	ret
Clear15 endp

DrawCOB proc
	push bp
	mov bp, sp
	push ax bx cx dx si di
;	mov cx, 7
;	mov dx, 7
;	mov di, 0
;	@@shoov: 
;		push COB[di]
;		push cx
;		push dx
;		call DrawCard
;		push 0 ; Black Frame
;		push cx
;		push dx
;		call DrawFrame
;		inc di
;		inc di
;		add cx, 67
;		cmp cx, 200
;		jc @@shoov
;		mov cx, 7
;		add dx, 37
;		cmp COB_Len, 12
;		jnz @@15cards
;	@@12cards:
;		cmp dx, 118
;		jc @@shoov
;	@@15cards:
;		cmp dx, 156
;		jc @@shoov

	mov ax, COB_Len
	cmp ax, 12
	jnz @@fifteen
@@twelve:
	xor di, di
	;mov ax, COB_Len
	;add ax, COB_Len
	@@shoov12: 
		push di
		push 0
		call GetHighRightCorner
		pop dx ; y
		pop cx ; x
		push COB[di] ; character
		push cx ; x
		push dx ; y
		call DrawCard
		push 0 ; black frame
		push cx ; x
		push dx ; y
		call DrawFrame
		inc di
		inc di
		;cmp di, ax
		cmp di, 24 ; COB_Len * 2 (words array)
		jnz @@shoov12
		jmp @@sof
		
@@fifteen:
	xor di, di
	;mov ax, COB_Len
	;add ax, COB_Len
	@@shoov15: 
		push di
		push 0
		call GetHighRightCorner
		pop	dx ; y
		pop cx ; x
		push COB[di] ; character
		push cx ; x
		push dx ; y
		call DrawCard
		push 0 ; black frame
		push cx ; x
		push dx ; y
		call DrawFrame
		inc di
		inc di
		;cmp di, ax
		cmp di, 30 ; COB_Len * 2 (words array)
		jnz @@shoov15
	
@@sof:	pop di si dx cx bx ax bp
	ret
DrawCOB endp


TsamtsemCOB proc
	push bp
	mov bp, sp
	push ax bx cx dx si di
;	xor si, si ; si=0
;	mov di, COB_Len
;	add di, COB_Len ; di= 2*COB_Len
;@@go:
;	cmp COB[si], 0
;	jnz @@con
;	mov ax, COB[si+2]
;	mov COB[si], ax
;	mov COB[si+2], 0
;@@con:
;	inc si
;	inc si
;	cmp si, di
;	jnz @@go
	
	xor si, si ; si=0
	mov di, COB_Len
	add di, COB_Len ; di= 2*COB_Len
	mov bx, di
	sub bx, 6
@@go:
	cmp bx, di ; when di=bx we have finished to order the last 3 cards of COB Array
	jz @@sof
	dec di
	dec di
	cmp COB[di], 0
	jnz @@find
	jmp @@go
@@find:
	mov ax, COB[di]
	xor si, si ; si=0
@@bdok:
	cmp COB[si], 0
	jnz @@con
	mov COB[si], ax ; ax = COB[di]
	mov COB[di], 0
	jmp @@go
@@con:
	inc si
	inc si
	jmp @@bdok
	
@@sof:
	pop di si dx cx bx ax bp
	ret
TsamtsemCOB endp	
	
	
MesumanimLeEfesCOB proc
	push bp
	mov bp, sp
	push ax bx cx dx si di
	xor si, si
	mov bx, COB_Len
	add bx, COB_Len
@@go: mov ax, COB[si]
	shl ax, 1
	jnc @@con
	mov COB[si], 0
@@con: 	
	inc si
	inc si
	cmp si, bx
	jnz @@go
	pop di si dx cx bx ax bp
	ret
MesumanimLeEfesCOB endp

	
CheckSifra proc
	push bp
	mov bp, sp
	push ax bx cx
	mov ax, ss:[bp+4] ; number
	mov bl, 3
	div bl ; ah = sherit, al = shalem
	cmp ah, 0
	jz @@ok
	xor cx, cx
	mov ss:[bp+4], cx
	jmp @@sof
@@ok: xor cx, cx
	inc cx
	mov ss:[bp+4], cx
@@sof: pop cx bx ax bp
	ret
CheckSifra endp
