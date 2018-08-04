;============================================
; input: 1 word (srak).
; output: 1 word - the random number.
;============================================	

Rand1to81 proc
	push bp
	mov bp, sp
	push ax bx cx dx
@@getTime:	
	mov ah, 2ch  ; Set function code
 	int 21h      ; get time from MS-DOS
	mov ax, dx   ; DH=seconds, DL=hundredths of second
 	;and ax, 0fh  ; keep only the 4 last bits of the hundredth of seconds
	xor ah, ah
	cmp ax, 82
	jc @@tse
	mov bl, 82
	div bl ; ah = sherit , al = mana
	shr ax, 8
	
@@tse:	mov ss:[bp+4], ax
	pop dx cx bx ax bp
	ret
Rand1to81 endp






	
CheckSet proc
	push bp
	mov bp, sp
	push ax bx cx dx si di
	mov ax, ss:[bp+4] ; card 1
	and ax, 0111111111111111b
	mov bx, ss:[bp+6] ; card 2
	and bx, 0111111111111111b
	add bx, ax
	mov ax, ss:[bp+8] ; card 3
	and ax, 0111111111111111b
	add bx, ax
	mov cx, 0000000000001111b
	and cx, bx
	push cx
	call CheckSifra
	pop cx
	cmp cx, 1
	jnz @@no
	mov cx, 0000000011110000b
	and cx, bx
	shr cx, 4
	push cx
	call CheckSifra
	pop cx
	cmp cx, 1
	jnz @@no
	mov cx, 0000111100000000b
	and cx, bx
	shr cx, 8
	push cx
	call CheckSifra
	pop cx
	cmp cx, 1
	jnz @@no
	mov cx, 1111000000000000b
	and cx, bx
	shr cx, 12
	push cx
	call CheckSifra
	pop cx
	cmp cx, 1
	jnz @@no
	mov si, 1
	mov ss:[bp+8], si
	jmp @@tse
@@no: xor si, si
	mov ss:[bp+8], si
@@tse:	pop di si dx cx bx ax bp
	ret 4
CheckSet endp
	
	
;===================================
; input =  1) number in array.		2) srak word.
; output = 1) high right corner y.  2) high right corner x
;===================================
GetHighRightCorner proc
	push bp
	mov bp, sp
	push ax bx cx dx si di
	;  ss:[bp+4] = srak
	mov ax, ss:[bp+6] ; number in array
	mov bl, 2
	div bl ; number in array / 2
	xor ah, ah
	mov bl, 3
	div bl ; al= row
	xor ah, ah
	mov bl, 37
	mul bl
	add ax, 7;
	mov ss:[bp+4], ax ; high right corner y
	mov ax, ss:[bp+6] ; number in array
	mov bl, 2
	div bl ; number in array / 2
	xor ah, ah
	mov bl, 3
	div bl ; ah= colum
	mov al, ah
	xor ah, ah
	mov bl, 67
	mul bl
	add ax, 7
	mov ss:[bp+6], ax ; high right corner x
	pop di si dx cx bx ax bp
	ret
GetHighRightCorner endp

NewGame proc
	push bp
	mov bp, sp
	push ax bx cx dx si di
	xor di, di
	@@shoov: 
		push 0
		call Rand1to81
		pop si
		dec si
		add si, si
		mov bx, CardsPack[si]
		shl bx, 1
		jc @@shoov
		mov bx, CardsPack[si]
		mov COB[di], bx
		xor bx, 1000000000000000b
		mov CardsPack[si], bx
		push di
		push 0
		call GetHighRightCorner
		pop	dx ; y
		pop cx ; x
		push COB[di] ; character
		push cx ; x
		push dx ; y
		call DrawCard
		inc di
		inc di
		cmp di, 24
		jnz @@shoov
		
		mov SetIndexim[0], 0
		mov SetIndexim[2], 0
		mov SetIndexim[4], 0
		mov SetCharacters[0], 0
		mov SetCharacters[2], 0
		mov SetCharacters[4], 0
		mov MoneChosenCards, 0
		call IpusSimun

		mov dh, 2 ; line
		mov dl, 69 ; colum
		push dx
		call GoToXY
		push offset UserName
		call PutS
		
		
	pop di si dx cx bx ax bp
	ret
NewGame endp	

printword proc
		push bp
		mov bp, sp
		push ax bx cx dx si di	
		;push TextMode
		;call SetVideoMode
		mov ax, ss:[bp+4] ; number
		shr ax, 12
		cmp ax, 0ah
		jc aa
		add ax, HEFRESHKATAN
	aa:	add ax, HEFRESH
		mov dl, al
		mov ah, 2h
		int 21h ; sof hatsaget 1
		mov ax, ss:[bp+4] ; number
		sh1: shr ax, 8
		and ax, 000Fh
		cmp ax, 0ah
		jc ab
	add ax, HEFRESHKATAN
	ab:	add ax, HEFRESH
		mov dl, al
		mov ah, 2h
		int 21h ; sof hatsaget 2
		mov ax, ss:[bp+4] ; number
		shr ax, 4
		and ax, 000Fh
		cmp ax, 0ah
		jc ac
		add ax, HEFRESHKATAN
	ac:	add ax, HEFRESH
		mov dl, al
		mov ah, 2h
		int 21h ; sof hatsaget3
		mov ax, ss:[bp+4] ; number
		and ax, 000Fh
		cmp ax, 0ah
		jc ad
		add ax, HEFRESHKATAN
	ad:	add ax, HEFRESH
		mov dl, al
		mov ah, 2h
		int 21h ; sof hatsaget 4
		;push GraphicsMode
		;call SetVideoMode
		pop di si dx cx bx ax bp
		ret 2
printword endp



ShowMoneSetim proc
	push bp
	mov bp, sp
	push ax bx cx dx si di
	mov dh, 5 ; line
	mov dl, 69 ; colum
	push dx
	call GoToXY
	
	;mov ax, MoneSetim
	;push ax
	;call printword
	
	mov ax, MoneSetim
	push ax
	push 10
	call HamaratBasis
	pop ax
	push ax
	call printword
	
	pop di si dx cx bx ax bp
	ret 
ShowMoneSetim endp

HamaratBasis proc
	push bp
 	mov bp, sp
 	push ax bx cx dx	
	mov bx, ss:[bp+4] ; basis
	mov ax, ss:[bp+6] ; num
	
	cmp ax, 0
	jz @@sof

	xor dx, dx
	div bx            ;  dx=h, ax=l /bx , ax = shalem dx=sheerit
	
	
	push ax
	push bx
	call HamaratBasis
	pop ax
	
	shl ax, 4
	add ax, dx
	
	mov ss:[bp+6], ax

@@sof:	pop dx cx bx ax bp
	ret 2
HamaratBasis endp

GetPlayerName proc
	push bp
	mov bp, sp
	push ax bx cx dx si di
	call clrScrn
	mov dl, 0
	mov dh, 0
	push dx
	call GoToXY
	push offset askName
	call PutS
	
	inc dh
	inc dh
	inc dh
	push dx
	call GoToXY
	mov cx, 0ah
	mov si, offset userName
	xor di, di
@@getName:
	mov ah, 01h
	int 21h ; get input with echo
	
	cmp al, 13
	je @@sof ; Quit if 'enter' 
	
	mov ds:[si], al
	inc si
	inc di
	cmp di, 0ah
	je @@sof
	jmp @@getName
@@sof:
	pop di si dx cx bx ax bp
	ret
GetPlayerName endp


IpusSimun proc
	push bp
	mov bp, sp
	push ax bx cx dx si di
	mov bx, offset CardsPack
	mov si, 0
	mov cx, CLength
	dec cx
@@lool:
	mov ax, ds:[bx+si]
	and ax, 0111111111111111b
	mov ds:[bx+si], ax
	inc si
	inc si
	loop @@lool
	pop di si dx cx bx ax bp
	ret
IpusSimun endp
	
CheckIfSof proc
	push bp
	mov bp, sp
	push ax bx cx dx si di
	; ss:[bp+4] = srak
	xor si, si
	xor cx, cx
	mov bx, offset CardsPack
	mov dx, CLength
	shl dx, 1
	dec si
	dec si
@@loolaa:
	inc si
	inc si
	mov ax, ds:[bx+si]
	rol ax, 1
	jnc @@bdok
	inc cx
@@bdok:
	cmp si, dx
	jnz @@loolaa
	
	cmp cx, CLength
	jz @@ken
@@lo:	mov ax, 0
	mov ss:[bp+4], ax
	jmp @@sof
@@ken:	mov ax, 1
	mov ss:[bp+4], ax
@@sof:	
	pop di si dx cx bx ax bp
	ret
CheckIfSof endp