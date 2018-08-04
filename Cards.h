;=======================================================================
;Input : 3 words. 	
;			first Word - character. every digit 1, 2 or 3 (the left digit can be 1,2,3,11(3),10(2) or 9(1))
;			second word - x of the high right corner.
;			third word - y of the high right corner.
;Return Value : None
;=======================================================================
DrawCard	Proc
		push bp
		mov bp, sp
		push ax bx cx dx si di
		mov dx, ss:[bp+4] ; y
		mov cx, ss:[bp+6] ; x
		mov bx, ss:[bp+8] ; character
		push dx ; y
		push cx ; x
		call DrawEmptyCard
		mov ax, 0111000000000000b
		and ax, bx
		shr ax, 12
		cmp ax, 2
		jz @@TwoShapes
		jnc @@ThreeShapes
	@@OneShape: mov si, 0000000001110000b ; shape
		and si, bx
		shr si, 4
		push si
		mov di, 0000000000000111b ; color
		and di, bx
		push di
		mov ax, 0000011100000000b ; filling
		and ax, bx
		shr ax, 8
		push ax
		add cx, 23
		push cx		; x
		add dx, 5
		push dx		; y
		call DrawShape
		jmp @@xyz
	@@TwoShapes: mov si, 0000000001110000b ; shape
		and si, bx
		shr si, 4
		push si
		mov di, 0000000000000111b ; color
		and di, bx
		push di ; color
		mov ax, 0000011100000000b ; filling
		and ax, bx
		shr ax, 8
		push ax  ; filling
		add cx,13
		push cx		; x
		add dx, 5
		push dx		; y
		call DrawShape
		push si ; shape
		push di ; color
		push ax	; filling
		add cx, 20
		push cx ; x
		push dx	; y
		call DrawShape
		jmp @@xyz
	@@ThreeShapes: mov si, 0000000001110000b ; shape
		and si, bx
		shr si, 4
		push si
		mov di, 0000000000000111b ; color
		and di, bx
		push di
		mov ax, 0000011100000000b ; filling
		and ax, bx
		shr ax, 8
		push ax
		add cx,6
		push cx		; x
		add dx, 5
		push dx		; y
		call DrawShape
		push si ; shape
		push di ; color
		push ax	; filling
		add cx, 17
		push cx ; x
		push dx	; y
		call DrawShape
		push si ; shape
		push di ; color
		push ax	; filling
		add cx, 17
		push cx ; x
		push dx	; y
		call DrawShape
	@@xyz:	pop di si dx cx bx ax bp
		ret 6
DrawCard endp





;========================================================================
;Input : 3 Words. 
;			First word - X axis of the pixel of the high right corner.
;			Second word - Y axis of the pixel pixel of the high right corner.
;Return Value : None
;=======================================================================
DrawEmptyCard proc
	push bp
	mov bp, sp
	push ax bx cx dx si di
	mov cx, [bp+4]		;PixelX
	mov dx, [bp+6]		;PixelY
	mov di, 0fh;
	mov al, 0 ;  x
	mov ah, 0 ;  Y
@@go: 	push di ; color
	push dx ; X
	push cx	; Y
	Call PutPixel
	inc cx
	inc al
	cmp al, 60
	jnz @@go
	sub cx, 60
	xor al, al
	inc dx
	inc ah
	cmp ah, 30
	jnz @@go
	pop di si dx cx bx ax bp
	ret 4
DrawEmptyCard endp


;=======================================================================
;Input : 5 words. 	
;			first Word - shape (number 1-3).
;			second Word - color (number 1-3).
;			third word - filling (number 1-3).
;			forth word - x of the high right corner.
;			fifth word - y of the high right corner.
;Return Value : None
;=======================================================================
DrawShape	Proc
		push bp
		mov bp, sp
		push ax bx cx dx si di
		mov dx, ss:[bp+4] ; y
		mov cx, ss:[bp+6] ; x
		mov ax, ss:[bp+8] ; filling
		mov bx, ss:[bp+10] ; color
		mov si, ss:[bp+12] ; shape
		cmp si, 2 
		jz @@ellipse ; if 2
		jnc @@diamond ; if 3
	@@wave:	cmp ax, 2 ; filling
		jz @@wave2 ; pasim
		jnc @@wave3 ; full filling		
	@@wave1:	push bx ; color ; without filling
		push dx ; y
		push cx ; x
		call Wave1
		jmp @@wxy
	@@wave2: push bx ; color	
		push dx ; y
		push cx ; x
		call Wave2
		jmp @@wxy
	@@wave3:push bx ; color	
		push dx ; y
		push cx ; x
		call Wave3
		jmp @@wxy
	@@ellipse:	cmp ax, 2 ; filling
		jz @@ellipse2 ; pasim
		jnc @@ellipse3 ; full filling
	@@ellipse1:	push cx ; x ; without filling
		push dx ; y
		push bx ; color
		call Ellipse1
		jmp @@wxy
	@@ellipse2:	push cx ; x
		push dx ; y
		 push bx ; color
		call Ellipse2
		jmp @@wxy
	@@ellipse3:			push cx ; x
		push dx ; y
		push bx ; color
		call Ellipse3
		jmp @@wxy
	@@diamond:	cmp ax, 2 ; filling
		jz @@diamond2 ; pasim
		jnc @@diamond3 ; full filling
	@@diamond1:	push cx ; x ; without filling
		push dx ; y
		push bx ; color
		call Diamond1
		jmp @@wxy
	@@diamond2:	push cx ; x
		push dx ; y
		push bx ; color
		call Diamond2
		jmp @@wxy
	@@diamond3:	push cx ; x
		push dx ; y
		push bx ; color
		call Diamond3
	@@wxy:	pop di si dx cx bx ax bp
		ret 10
DrawShape endp
		
;=======================================================================
;Input : 3 words. 	
;			first Word - color (number 1-3).
;			second word - x of the high right corner.
;			third word - y of the high right corner.
;Return Value : None
;=======================================================================
Wave3	Proc
		push bp
		mov bp, sp
		push bx ax cx dx si di
		mov cx, [bp+4]		;PixelX
		mov dx, [bp+6]		;PixelY	
		mov ax, [bp+8]		;PixelColor	( ah - not in use )
		cmp al, 2
		jz @@c2
		jnc @@c3
	@@c1:	mov al, 2h 	; Green
		jmp @@con
	@@c2:	mov al, 0ch  	; Red
		jmp @@con
	@@c3:	mov al, 5h  	; Purple
	@@con:	mov si, 5 
		add cx, 15
		add dx, 5 
		xor bl, bl   ; mone bakara                                                                                                                     	; len
	@@aaa:	inc bl
		dec cx
		dec dx
		push ax ; color
		push dx ; y
		push cx ; left x
		sub cx, si
		push cx ; right x
		add cx, si 
		Call DrawHLine	   
		cmp bl, 4
		jnz @@aaa		
		xor bl, bl
		dec cx
		push ax ; color
		push dx ; y
		push cx ; x
		call PutPixel
	@@bbb:	dec cx
		inc dx
		inc bl
		push ax ; color
		push dx ; y
		push cx ; left x
		sub cx, si
		push cx ; right x
		add cx, si 
		Call DrawHLine
		cmp bl, 5
		jnz @@bbb
		xor bl, bl
		dec cx
	@@ccc:	inc cx
		inc dx
		inc bl
		push ax ; color
		push dx ; y
		push cx ; left x
		sub cx, si
		push cx ; right x
		add cx, si 
		Call DrawHLine
		cmp bl, 3
		jnz @@ccc	
		inc cx
		push ax ; color
		push dx ; y
		push cx ; x
		call PutPixel
		sub cx , 3
		inc dx
		push ax ; color
		push dx ; y
		push cx ; x
		call PutPixel
		dec dx
		add cx, 3
		inc cx
		xor bl, bl
	@@ddd:	inc cx
		inc dx
		inc bl 
		push ax ; color
		push dx ; y
		push cx ; left x
		sub cx, si
		push cx ; right x
		add cx, si 
		Call DrawHLine
		cmp bl, 4
		jnz @@ddd
		inc cx
		xor bl, bl
	@@eee:	dec cx
		inc dx
		inc bl
		push ax ; color
		push dx ; y
		push cx ; left x
		sub cx, si
		push cx ; right x
		add cx, si 
		Call DrawHLine
		cmp bl, 6
		jnz @@eee
		xor bl, bl
	@@fff:	dec dx
		dec cx
		inc bl
		push ax ; color
		push dx ; y
		push cx ; left x
		sub cx, si
		push cx ; right x
		add cx, si 
		Call DrawHLine
		cmp bl, 4
		jnz @@fff
		pop di si dx cx bx ax bp
		ret 6
Wave3 endp


;=======================================================================
;Input : 3 words. 	
;			first Word - color (number 1-3).
;			second word - x of the high right corner.
;			third word - y of the high right corner.
;Return Value : None
;=======================================================================
Wave2 proc
		push bp
		mov bp, sp
		push bx ax cx dx si di
		mov cx, [bp+4]		;PixelX
		mov dx, [bp+6]		;PixelY	
		mov ax, [bp+8]		;PixelColor	( ah - not in use )
		cmp al, 2
		jz @@c2
		jnc @@c3
	@@c1:	mov al, 2h 	; Green
		jmp @@con
	@@c2:	mov al, 0ch  	; Red
		jmp @@con
	@@c3:	mov al, 5h  	; Purple
	@@con:	 xor bl, bl   ; mone bakara                                                                                                                     	; len
		add cx, 5
		push ax ; color
		push dx ; y
		add cx, 4
		push cx ; x2
		sub cx, 5
		push cx ; x1
		call DrawHLine
		dec cx
		push ax ; color
		push dx ; y
		push cx ; x
		call PutPixel
		dec cx
		inc dx
		push ax ; color
		push dx ; y
		push cx ; x
		call PutPixel
		push ax ; color
		push dx ; y
		add cx, 7
		push cx ; x
		sub cx, 7
		call PutPixel
		inc dx
		dec cx
		push ax ; color
		push dx ; y
		add cx, 9
		push cx ; x
		sub cx, 9
		push cx ; x
		call DrawHLine  ; line 3
		inc dx		; line 4
		dec cx
		push ax ; color
		push dx ; y
		push cx ; x
		call PutPixel
		push ax ; color
		push dx ; y
		add cx, 7
		push cx ; x
		sub cx, 3
		push cx ; x
		call DrawHLine
		add cx, 7
		push ax ; color
		push dx ; y
		push cx ; x
		call PutPixel
		inc dx		;line 5
		push ax ; color
		push dx ; y
		push cx ; x
		sub cx, 4
		push cx ; x
		call DrawHLine
		dec dx
		sub cx, 7
		dec cx
		inc dx
		push ax ; color
		push dx ; y
		add cx, 4
		push cx ; x
		sub cx, 4
		push cx ; x
		call DrawHLine
		dec cx
		inc dx  ;line 6
		push ax ; color
		push dx ; y
		push cx ; x
		call PutPixel
		push ax ; color
		push dx ; y
		add cx, 4
		push cx ; x
		sub cx, 4
		call PutPixel
		inc dx    ; line 7
		push ax ; color
		push dx ; y
		add cx, 4
		push cx ; x
		sub cx, 4
		push cx ; x
		call DrawHLine
		inc cx
		inc dx		;line 8
		push ax ; color
		push dx ; y
		push cx ; x
		call PutPixel
		push ax ; color
		push dx ; y
		add cx, 4
		push cx ; x
		sub cx, 4
		call PutPixel
		inc cx		; line 9
		inc dx
		push ax ; color
		push dx ; y
		add cx, 4
		push cx ; x
		sub cx, 4
		push cx ; x
		call DrawHLine
		inc cx
		inc dx 		;line 10
		push ax ; color
		push dx ; y
		push cx ; x
		call PutPixel
		push ax ; color
		push dx ; y
		add cx, 4
		push cx ; x
		sub cx, 4
		call PutPixel
		inc cx
		inc dx   	;line 11
		push ax ; color
		push dx ; y
		add cx, 5
		push cx ; x
		sub cx, 5
		push cx ; x
		call DrawHLine
		inc cx
		inc dx		; line 12
		push ax ; color
		push dx ; y
		push cx ; x
		call PutPixel
		push ax ; color
		push dx ; y
		add cx, 4
		push cx ; x
		sub cx, 4
		call PutPixel
		inc cx
		inc dx		
		push ax ; color
		push dx ; y
		add cx, 4
		push cx ; x
		sub cx, 4
		push cx ; x
		call DrawHLine
		inc cx
		inc dx		
		push ax ; color
		push dx ; y
		push cx ; x
		call PutPixel
		push ax ; color
		push dx ; y
		add cx, 4
		push cx ; x
		sub cx, 4
		call PutPixel
		inc cx
		inc dx		
		push ax ; color
		push dx ; y
		add cx, 4
		push cx ; x
		sub cx, 4
		push cx ; x
		call DrawhLine	
		inc dx		
		push ax ; color
		push dx ; y
		add cx, 4
		push cx ; x
		sub cx, 4
		push cx ; x
		call DrawHLine
		dec cx
		inc dx		;line 16
		push ax ; color
		push dx ; y
		push cx ; x
		call PutPixel
		push ax ; color
		push dx ; y
		add cx, 4
		push cx ; x
		sub cx, 4
		call PutPixel
		sub cx, 4
		push ax ; color
		push dx ; y
		push cx ; x
		sub cx, 4
		push cx
		add cx, 8
		call DrawHLine
		dec cx
		inc dx		;line 17
		push ax ; color
		push dx ; y
		add cx, 4
		push cx ; x
		sub cx, 4
		call PutPixel
 		push ax ; color
		push dx ; y
		push cx ; x
		call PutPixel
		sub cx, 3
		push ax ; color
		push dx ; y
		push cx ; x
		call PutPixel
		push ax ; color
		push dx ; y
		sub cx, 4
		push cx ; x
		call PutPixel
		inc cx
		inc dx		; line 18
		push ax ; color
		push dx ; y
		add cx, 9
		push cx  ; x
		sub cx, 9
		push cx ; x
		add cx, 9
		call DrawHLine
		inc dx		; line 19
		dec cx
		push ax ; color
		push dx ; y
		push cx ; x
		call PutPixel
		sub cx, 7
		push ax ; color
		push dx ; y
		push cx ; x
		call PutPixel
		inc cx
		inc dx   	;line 20
		push ax ; color
		push dx ; y
		add cx, 5
		push cx ; x
		sub cx, 5 
		push cx ; x
		call DrawHLine
		pop di si dx cx bx ax bp
		ret 6
Wave2 endp
;=======================================================================
;Input : 3 words. 	
;			first Word - color (number 1-3).
;			second word - x of the high right corner.
;			third word - y of the high right corner.
;Return Value : None
;=======================================================================
Wave1 proc
		push bp
		mov bp, sp
		push bx ax cx dx si di
		mov cx, [bp+4]		;PixelX
		mov dx, [bp+6]		;PixelY	
		mov ax, [bp+8]		;PixelColor	( ah - not in use )
		cmp al, 2
		jz @@c2
		jnc @@c3
	@@c1:	mov al, 2h 	; Green
		jmp @@con
	@@c2:	mov al, 0ch  	; Red
		jmp @@con
	@@c3:	mov al, 5h  	; Purple
	@@con:	 xor bl, bl   ; mone bakara                                                                                                                     	; len
		add cx, 5
		push ax ; color
		push dx ; y
		add cx, 4
		push cx ; x2
		sub cx, 5
		push cx ; x1
		call DrawHLine
		dec cx
		push ax ; color
		push dx ; y
		push cx ; x
		call PutPixel
		dec cx
		inc dx
		push ax ; color
		push dx ; y
		push cx ; x
		call PutPixel
		push ax ; color
		push dx ; y
		add cx, 7
		push cx ; x
		sub cx, 7
		call PutPixel
		inc dx
		dec cx
		push ax ; color
		push dx ; y
		push cx ; x
		call PutPixel
		push ax ; color
		push dx ; y
		add cx, 9
		push cx ; x
		sub cx, 9
		call PutPixel
		inc dx
		dec cx
		push ax ; color
		push dx ; y
		push cx ; x
		call PutPixel
		push ax ; color
		push dx ; y
		add cx, 7
		push cx ; x
		sub cx, 3
		push cx ; x
		call DrawHLine
		add cx, 7
		push ax ; color
		push dx ; y
		push cx ; x
		call PutPixel
		inc dx
		push ax ; color
		push dx ; y
		push cx ; x
		sub cx, 4
		push cx ; x
		call DrawHLine
		dec dx
		sub cx, 7
		dec cx
		inc dx
		push ax ; color
		push dx ; y
		push cx ; x
		call PutPixel
		push ax ; color
		push dx ; y
		add cx, 4
		push cx ; x
		sub cx, 4
		call PutPixel
		dec cx
		inc dx
		push ax ; color
		push dx ; y
		push cx ; x
		call PutPixel
		push ax ; color
		push dx ; y
		add cx, 4
		push cx ; x
		sub cx, 4
		call PutPixel
		inc dx
		push ax ; color
		push dx ; y
		push cx ; x
		call PutPixel
		push ax ; color
		push dx ; y
		add cx, 4
		push cx ; x
		sub cx, 4
		call PutPixel
		inc cx
		inc dx
		push ax ; color
		push dx ; y
		push cx ; x
		call PutPixel
		push ax ; color
		push dx ; y
		add cx, 4
		push cx ; x
		sub cx, 4
		call PutPixel
		inc cx
		inc dx
		push ax ; color
		push dx ; y
		push cx ; x
		call PutPixel
		push ax ; color
		push dx ; y
		add cx, 4
		push cx ; x
		sub cx, 4
		call PutPixel
		inc cx
		inc dx
		push ax ; color
		push dx ; y
		push cx ; x
		call PutPixel
		push ax ; color
		push dx ; y
		add cx, 4
		push cx ; x
		sub cx, 4
		call PutPixel
		inc cx
		inc dx
		push ax ; color
		push dx ; y
		push cx ; x
		call PutPixel
		push ax ; color
		push dx ; y
		add cx, 4
		push cx ; x
		call PutPixel
		inc cx
		push ax ; color
		push dx ; y
		push cx ; x
		call PutPixel
		sub cx, 3 
		push ax ; color
		push dx ; y
		push cx ; x
		call PutPixel
		inc cx
		inc dx
		push ax ; color
		push dx ; y
		push cx ; x
		call PutPixel
		push ax ; color
		push dx ; y
		add cx, 4
		push cx ; x
		sub cx, 4
		call PutPixel
		inc cx
		inc dx
		push ax ; color
		push dx ; y
		push cx ; x
		call PutPixel
		push ax ; color
		push dx ; y
		add cx, 4
		push cx ; x
		sub cx, 4
		call PutPixel
		inc cx
		inc dx
		push ax ; color
		push dx ; y
		push cx ; x
		call PutPixel
		push ax ; color
		push dx ; y
		add cx, 4
		push cx ; x
		sub cx, 4
		call PutPixel
		inc cx
		inc dx
		push ax ; color
		push dx ; y
		push cx ; x
		call PutPixel
		push ax ; color
		push dx ; y
		add cx, 4
		push cx ; x
		sub cx, 4
		call PutPixel
		inc dx
		push ax ; color
		push dx ; y
		push cx ; x
		call PutPixel
		push ax ; color
		push dx ; y
		add cx, 4
		push cx ; x
		sub cx, 4
		call PutPixel
		dec cx
		inc dx
		push ax ; color
		push dx ; y
		push cx ; x
		call PutPixel
		push ax ; color
		push dx ; y
		add cx, 4
		push cx ; x
		sub cx, 4
		call PutPixel
		sub cx, 4
		push ax ; color
		push dx ; y
		push cx ; x
		sub cx, 4
		push cx
		add cx, 8
		call DrawHLine
		dec cx
		inc dx
		push ax ; color
		push dx ; y
		push cx ; x
		call PutPixel
		push ax ; color
		push dx ; y
		add cx, 4
		push cx ; x
		sub cx, 4
		call PutPixel
		dec cx
		dec cx
		dec cx
		push ax ; color
		push dx ; y
		push cx ; x
		call PutPixel
		sub cx, 4
		push ax ; color
		push dx ; y
		push cx ; x
		call PutPixel
		inc cx
		inc dx
		push ax ; color
		push dx ; y
		push cx ; x
		call PutPixel
		add cx, 4
		push ax ; color
		push dx ; y
		push cx ; x
		call PutPixel
		inc cx
		push ax ; color
		push dx ; y
		push cx ; x
		call PutPixel
		add cx, 4
	 	push ax ; color
		push dx ; y
		push cx ; x
		call PutPixel
		inc dx
		dec cx
		push ax ; color
		push dx ; y
		push cx ; x
		call PutPixel
		sub cx, 7
		push ax ; color
		push dx ; y
		push cx ; x
		call PutPixel
		inc cx
		inc dx
		push ax ; color
		push dx ; y
		add cx, 5
		push cx ; x
		sub cx, 5 
		push cx ; x
		call DrawHLine
		pop di si dx cx bx ax bp
		ret 6
Wave1 endp

;=======================================================================
;Input : 3 words. 	
;			first word - x of the high right corner.
;			second word - y of the high right corner.
;			third Word - color (number 1-3).
;Return Value : None
;=======================================================================
Ellipse1 proc
		push bp
		mov bp, sp
		push bx ax cx dx si di
		mov ax, [bp+4]		;PixelColor	( ah - not in use )
		mov dx, [bp+6]		;PixelY	
		mov cx, [bp+8]		;PixelX
		cmp al, 2
		jz @@c2
		jnc @@c3
	@@c1:	mov al, 2h 	; Green
		jmp @@con
	@@c2:	mov al, 0ch  	; Red
		jmp @@con
	@@c3:	mov al, 5h  	; Purple
	@@con:  xor si, si
		add cx, 6
		push ax ; color
		push dx ; y
		push cx ; x
		call PutPixel
		push ax ; color
		push dx ; y
		inc cx
		push cx ; x
		call PutPixel
		dec cx
		dec cx
		inc dx
		push ax ; color
		push dx ; y
		add cx, 3
		push cx	; x
		sub cx, 3
		call PutPixel
		push ax ; color
		push dx ; y
		push cx ; x
		call PutPixel
		dec cx
		inc dx
		push ax ; color
		push dx ; y
		add cx, 5
		push cx	; x
		sub cx, 5
		call PutPixel
		push ax ; color
		push dx ; y
		push cx ; x
		call PutPixel
		inc dx
		push ax ; color
		push dx ; y
		add cx, 5
		push cx	; x
		sub cx, 5
		call PutPixel
		push ax ; color
		push dx ; y
		push cx ; x
		call PutPixel
		xor bl, bl
		dec cx
	@@squre: inc bl
		inc dx
		push ax ; color
		push dx ; y
		add cx, 7
		push cx	; x
		sub cx, 7
		call PutPixel
		push ax ; color
		push dx ; y
		push cx ; x
		call PutPixel
		cmp bl, 12
		jnz @@squre
		inc cx
		inc dx
		push ax ; color
		push dx ; y
		add cx, 5
		push cx	; x
		sub cx, 5
		call PutPixel
		push ax ; color
		push dx ; y
		push cx ; x
		call PutPixel
		inc dx
		push ax ; color
		push dx ; y
		add cx, 5
		push cx	; x
		sub cx, 5
		call PutPixel
		push ax ; color
		push dx ; y
		push cx ; x
		call PutPixel
		inc dx
		inc cx
		push ax ; color
		push dx ; y
		add cx, 3
		push cx	; x
		sub cx, 3
		call PutPixel
		push ax ; color
		push dx ; y
		push cx ; x
		call PutPixel
		inc dx
		inc cx
		push ax ; color
		push dx ; y
		push cx ; x
		call PutPixel
		inc cx
		push ax ; color
		push dx ; y
		push cx ; x
		call PutPixel
		pop di si dx cx bx ax bp
		ret 6	
Ellipse1 endp
	
;=======================================================================
;Input : 3 words. 	
;			first word - x of the high right corner.
;			second word - y of the high right corner.
;			third Word - color (number 1-3).
;Return Value : None
;=======================================================================
Ellipse2 proc
		push bp
		mov bp, sp
		push bx ax cx dx si di
		mov ax, [bp+4]		;PixelColor	( ah - not in use )
		mov dx, [bp+6]		;PixelY	
		mov cx, [bp+8]		;PixelX
		cmp al, 2
		jz @@c2
		jnc @@c3
	@@c1:	mov al, 2h 	; Green
		jmp @@con
	@@c2:	mov al, 0ch  	; Red
		jmp @@con
	@@c3:	mov al, 5h  	; Purple
	@@con:  xor si, si
		add cx, 6
		push ax ; color
		push dx ; y
		push cx ; x
		call PutPixel
		push ax ; color
		push dx ; y
		inc cx
		push cx ; x
		call PutPixel
		dec cx
		dec cx
		inc dx
		push ax ; color
		push dx ; y
		add cx, 3
		push cx	; x
		sub cx, 3
		call PutPixel
		push ax ; color
		push dx ; y
		push cx ; x
		call PutPixel
		dec cx
		inc dx
		push ax ; color
		push dx ; y
		add cx, 5
		push cx	; x
		sub cx, 5
		push cx ; x
		call DrawHLine
		inc dx
		push ax ; color
		push dx ; y
		add cx, 5
		push cx	; x
		sub cx, 5
		call PutPixel
		push ax ; color
		push dx ; y
		push cx ; x
		call PutPixel
		xor bl, bl
		dec cx
	@@squre: inc bl
		inc dx
		push ax ; color
		push dx ; y
		add cx, 7
		push cx	; x
		sub cx, 7
		push cx ; x
		call DrawHLine
		inc bl
		inc dx
		push ax ; color
		push dx ; y
		add cx, 7
		push cx	; x
		sub cx, 7
		call PutPixel
		push ax ; color
		push dx ; y
		push cx ; x
		call PutPixel
		cmp bl, 12
		jnz @@squre
		inc cx
		inc dx
		push ax ; color
		push dx ; y
		add cx, 5
		push cx	; x
		sub cx, 5
		push cx ; x
		call DrawHLine
		inc dx
		push ax ; color
		push dx ; y
		add cx, 5
		push cx	; x
		sub cx, 5
		call PutPixel
		push ax ; color
		push dx ; y
		push cx ; x
		call PutPixel
		inc dx
		inc cx
		push ax ; color
		push dx ; y
		add cx, 3
		push cx	; x
		sub cx, 3
		push cx ; x
		call DrawHLine
		inc dx
		inc cx
		push ax ; color
		push dx ; y
		push cx ; x
		call PutPixel
		inc cx
		push ax ; color
		push dx ; y
		push cx ; x
		call PutPixel
		pop di si dx cx bx ax bp
		ret 6	
Ellipse2 endp

;=======================================================================
;Input : 3 words. 	
;			first word - x of the high right corner.
;			second word - y of the high right corner.
;			third Word - color (number 1-3).
;Return Value : None
;=======================================================================
Ellipse3 proc
		push bp
		mov bp, sp
		push bx ax cx dx si di
		mov ax, [bp+4]		;PixelColor	( ah - not in use )
		mov dx, [bp+6]		;PixelY	
		mov cx, [bp+8]		;PixelX
		cmp al, 2
		jz @@c2
		jnc @@c3
	@@c1:	mov al, 2h 	; Green
		jmp @@con
	@@c2:	mov al, 0ch  	; Red
		jmp @@con
	@@c3:	mov al, 5h  	; Purple
	@@con:  xor si, si
		add cx, 6
		push ax ; color
		push dx ; y
		push cx ; x
		call PutPixel
		push ax ; color
		push dx ; y
		inc cx
		push cx ; x
		call PutPixel
		dec cx
		dec cx
		inc dx
		push ax ; color
		push dx ; y
		add cx, 3
		push cx	; x
		sub cx, 3
		push cx ; x
		call DrawHLine
		dec cx
		inc dx
		push ax ; color
		push dx ; y
		add cx, 5
		push cx	; x
		sub cx, 5
		push cx ; x
		call DrawHLine
		inc dx
		push ax ; color
		push dx ; y
		add cx, 5
		push cx	; x
		sub cx, 5
		push cx ; x
		call DrawHLine
		xor bl, bl
		dec cx
	@@squre: inc bl
		inc dx
		push ax ; color
		push dx ; y
		add cx, 7
		push cx	; x
		sub cx, 7
		push cx ; x
		call DrawHLine
		cmp bl, 12
		jnz @@squre
		inc cx
		inc dx
		push ax ; color
		push dx ; y
		add cx, 5
		push cx	; x
		sub cx, 5
		push cx ; x
		call DrawHLine
		inc dx
		push ax ; color
		push dx ; y
		add cx, 5
		push cx	; x
		sub cx, 5
		push cx ; x
		call DrawHLine
		inc dx
		inc cx
		push ax ; color
		push dx ; y
		add cx, 3
		push cx	; x
		sub cx, 3
		push cx ; x
		call DrawHLine
		inc dx
		inc cx
		push ax ; color
		push dx ; y
		push cx ; x
		call PutPixel
		inc cx
		push ax ; color
		push dx ; y
		push cx ; x
		call PutPixel
		pop di si dx cx bx ax bp
		ret 6	
Ellipse3 endp
;=======================================================================
;Input : 3 words. 	
;			first Word - color (number 1-3).
;			second word - x of the high right corner.
;			third word - y of the high right corner.
;Return Value : None
;=======================================================================
Diamond3 proc
		push bp
		mov bp, sp
		push ax bx cx dx si di
		mov ax, [bp+4]		;PixelColor	( ah - not in use )
		mov dx, [bp+6]		;PixelY	
		mov cx, [bp+8]		;PixelX
		add cx, 8 		; middle of the card
		cmp al, 2
		jz @@c2
		jnc @@c3
	@@c1:	mov al, 2h ; Green
		jmp @@con
	@@c2:	mov al, 0ch  ; Red
		jmp @@con
	@@c3:	mov al, 5h  ; Purple
	@@con:	mov si, cx ; x goes to right
		mov di, 1 ; len
		push ax ; color
		push dx ; y
		push si ; x
		call PutPixel
		inc dx
		mov bl, 0
		inc bl
	;@@open:	dec cx
	;	mov si, cx ; x mitkadem bashura
	;	inc di
	;	inc di   ; add 2 to len
	;	push ax ; color
	;	push dx ; y
	;	add si, di ; len
	;	push si ; right x
	;	sub si, di ; len
	;	push si ; left x
	;	
	;	call DrawHLine
	;	inc dx
	;	inc bl
	;	push ax ; color
	;	push dx ; y
	;	add si, di ; len
	;	push si ; right x
	;	sub si, di ; len
	;	push si ; left x
	;	call DrawHLine
	;	inc dx
	;	inc bl
	;	cmp bl, 12
	;	jnz @@open

		dec cx 								; 1
		mov si, cx ; x mitkadem bashura
		inc di
		inc di   ; add 2 to len
		push ax ; color
		push dx ; y
		add si, di ; len
		push si ; right x
		sub si, di ; len
		push si ; left x
		
		call DrawHLine
		inc dx
		inc bl
		push ax ; color
		push dx ; y
		add si, di ; len
		push si ; right x
		sub si, di ; len
		push si ; left x
		call DrawHLine
		inc dx
		inc bl
		
		
		
		
		dec cx								;2
		mov si, cx ; x mitkadem bashura
		inc di
		inc di   ; add 2 to len
		push ax ; color
		push dx ; y
		add si, di ; len
		push si ; right x
		sub si, di ; len
		push si ; left x
		
		call DrawHLine
		inc dx
		inc bl
		push ax ; color
		push dx ; y
		add si, di ; len
		push si ; right x
		sub si, di ; len
		push si ; left x
		call DrawHLine
		inc dx
		inc bl
		
		
		
		
		
		dec cx								;3
		mov si, cx ; x mitkadem bashura
		inc di
		inc di   ; add 2 to len
		push ax ; color
		push dx ; y
		add si, di ; len
		push si ; right x
		sub si, di ; len
		push si ; left x
		
		call DrawHLine
		inc dx
		inc bl
		push ax ; color
		push dx ; y
		add si, di ; len
		push si ; right x
		sub si, di ; len
		push si ; left x
		call DrawHLine
		inc dx
		inc bl
		
		
		
		dec cx									;4
		mov si, cx ; x mitkadem bashura
		inc di
		inc di   ; add 2 to len
		push ax ; color
		push dx ; y
		add si, di ; len
		push si ; right x
		sub si, di ; len
		push si ; left x
		
		call DrawHLine
		inc dx
		inc bl
		push ax ; color
		push dx ; y
		add si, di ; len
		push si ; right x
		sub si, di ; len
		push si ; left x
		call DrawHLine
		inc dx
		inc bl

		
		dec cx 								; 5
		mov si, cx ; x mitkadem bashura
		inc di
		inc di   ; add 2 to len
		push ax ; color
		push dx ; y
		add si, di ; len
		push si ; right x
		sub si, di ; len
		push si ; left x
		
		call DrawHLine
		inc dx
		inc bl
		push ax ; color
		push dx ; y
		add si, di ; len
		push si ; right x
		sub si, di ; len
		push si ; left x
		call DrawHLine
		inc dx
		inc bl
		
		
		
	;@@close:	inc cx
	;	mov si, cx ; x mitkadem bashura
	;	dec di
	;	dec di   ; sub 2 to len
	;	push ax ; color
	;	push dx ; y
	;	add si, di ; len
	;	push si ; right x
	;	sub si, di ; len
	;	push si ; left x
	;	call DrawHLine

	;	inc dx
	;	inc bl
	;	push ax ; color
	;	push dx ; y
	;	add si, di ; len
	;	push si ; right x
	;	sub si, di ; len
	;	push si ; left x
	;	call DrawHLine

	;	inc dx
	;	inc bl
	;	cmp bl, 20
	;	jnz @@close 
	
	
	inc cx
		mov si, cx ; x mitkadem bashura
		dec di
		dec di   ; sub 2 to len
		push ax ; color
		push dx ; y
		add si, di ; len
		push si ; right x
		sub si, di ; len
		push si ; left x
		call DrawHLine

		inc dx
		inc bl
		push ax ; color
		push dx ; y
		add si, di ; len
		push si ; right x
		sub si, di ; len
		push si ; left x
		call DrawHLine

		inc dx
		inc bl
		
		inc cx
		mov si, cx ; x mitkadem bashura
		dec di
		dec di   ; sub 2 to len
		push ax ; color
		push dx ; y
		add si, di ; len
		push si ; right x
		sub si, di ; len
		push si ; left x
		call DrawHLine

		inc dx
		inc bl
		push ax ; color
		push dx ; y
		add si, di ; len
		push si ; right x
		sub si, di ; len
		push si ; left x
		call DrawHLine

		inc dx
		inc bl
		
		inc cx
		mov si, cx ; x mitkadem bashura
		dec di
		dec di   ; sub 2 to len
		push ax ; color
		push dx ; y
		add si, di ; len
		push si ; right x
		sub si, di ; len
		push si ; left x
		call DrawHLine

		inc dx
		inc bl
		push ax ; color
		push dx ; y
		add si, di ; len
		push si ; right x
		sub si, di ; len
		push si ; left x
		call DrawHLine

		inc dx
		inc bl
		
		inc cx
		mov si, cx ; x mitkadem bashura
		dec di
		dec di   ; sub 2 to len
		push ax ; color
		push dx ; y
		add si, di ; len
		push si ; right x
		sub si, di ; len
		push si ; left x
		call DrawHLine

		inc dx
		inc bl
		push ax ; color
		push dx ; y
		add si, di ; len
		push si ; right x
		sub si, di ; len
		push si ; left x
		call DrawHLine

		inc dx
		inc bl
	
		
		inc cx
		mov si, cx ; x mitkadem bashura
		dec di
		dec di   ; sub 2 to len
		push ax ; color
		push dx ; y
		add si, di ; len
		push si ; right x
		sub si, di ; len
		push si ; left x
		call DrawHLine

		inc dx
		inc bl
		push ax ; color
		push dx ; y
		add si, di ; len
		push si ; right x
		sub si, di ; len
		push si ; left x
		call DrawHLine

		inc dx
		inc bl
	
	
	
	
	
	
	
	
	
	
	
	
		inc si
		push ax ; color
		push dx ; y
		push si ; x
		call PutPixel
		pop di si dx cx bx ax bp
		ret 6
Diamond3 endp

Diamond2 proc
		push bp
		mov bp, sp
		push ax bx cx dx si di
		mov ax, [bp+4]		;PixelColor	( ah - not in use )
		mov dx, [bp+6]		;PixelY	
		mov cx, [bp+8]		;PixelX
		add cx, 8 		; middle of the card
		cmp al, 2
		jz @@c2
		jnc @@c3
	@@c1:	mov al, 2h ; Green
		jmp @@con
	@@c2:	mov al, 0ch  ; Red
		jmp @@con
	@@c3:	mov al, 5h  ; Purple
	@@con:	mov si, cx ; x goes to right
		mov di, 1 ; len
		push ax ; color
		push dx ; y
		push si ; x
		call PutPixel
		inc dx
		xor bl, bl
		inc bl
	;@@open:	dec cx
	;	mov si, cx ; x mitkadem bashura
	;	inc di
	;	inc di   ; add 2 to len
	;	push ax ; color
	;	push dx ; y
	;	add si, di ; len
	;	push si ; right x
	;	sub si, di ; len
	;	push si ; left x
	;	call DrawHLine
	;	inc dx
	;	inc bl
	;	push ax ; color
	;	push dx ; y
	;	add si, di ; len
	;	push si ; right x
	;	sub si, di ; len
	;	call PutPixel
	;	push ax ; color
	;	push dx ; y
	;	push si ; left x
	;	call PutPixel
	;	inc dx
	;	inc bl
	;	cmp bl, 12
	;	jc @@open 
	
		
		dec cx
		mov si, cx ; x mitkadem bashura
		inc di
		inc di   ; add 2 to len
		push ax ; color
		push dx ; y
		add si, di ; len
		push si ; right x
		sub si, di ; len
		push si ; left x
		call DrawHLine
		inc dx
		inc bl
		push ax ; color
		push dx ; y
		add si, di ; len
		push si ; right x
		sub si, di ; len
		call PutPixel
		push ax ; color
		push dx ; y
		push si ; left x
		call PutPixel
		inc dx
		inc bl
		
		
		dec cx
		mov si, cx ; x mitkadem bashura
		inc di
		inc di   ; add 2 to len
		push ax ; color
		push dx ; y
		add si, di ; len
		push si ; right x
		sub si, di ; len
		push si ; left x
		call DrawHLine
		inc dx
		inc bl
		push ax ; color
		push dx ; y
		add si, di ; len
		push si ; right x
		sub si, di ; len
		call PutPixel
		push ax ; color
		push dx ; y
		push si ; left x
		call PutPixel
		inc dx
		inc bl
		
		
		dec cx
		mov si, cx ; x mitkadem bashura
		inc di
		inc di   ; add 2 to len
		push ax ; color
		push dx ; y
		add si, di ; len
		push si ; right x
		sub si, di ; len
		push si ; left x
		call DrawHLine
		inc dx
		inc bl
		push ax ; color
		push dx ; y
		add si, di ; len
		push si ; right x
		sub si, di ; len
		call PutPixel
		push ax ; color
		push dx ; y
		push si ; left x
		call PutPixel
		inc dx
		inc bl
		
		
		dec cx
		mov si, cx ; x mitkadem bashura
		inc di
		inc di   ; add 2 to len
		push ax ; color
		push dx ; y
		add si, di ; len
		push si ; right x
		sub si, di ; len
		push si ; left x
		call DrawHLine
		inc dx
		inc bl
		push ax ; color
		push dx ; y
		add si, di ; len
		push si ; right x
		sub si, di ; len
		call PutPixel
		push ax ; color
		push dx ; y
		push si ; left x
		call PutPixel
		inc dx
		inc bl
		
		
		dec cx
		mov si, cx ; x mitkadem bashura
		inc di
		inc di   ; add 2 to len
		push ax ; color
		push dx ; y
		add si, di ; len
		push si ; right x
		sub si, di ; len
		push si ; left x
		call DrawHLine
		inc dx
		inc bl
		push ax ; color
		push dx ; y
		add si, di ; len
		push si ; right x
		sub si, di ; len
		call PutPixel
		push ax ; color
		push dx ; y
		push si ; left x
		call PutPixel
		inc dx
		inc bl

	;@@close:	inc cx
	;	mov si, cx ; x mitkadem bashura
	;	dec di
	;	dec di   ; sub 2 to len
	;	push ax ; color
	;	push dx ; y
	;	add si, di ; len
	;	push si ; right x
	;	sub si, di ; len
	;	push si ; left x
	;	call DrawHLine

	;	inc dx
	;	inc bl
	;	push ax ; color
	;	push dx ; y
	;	add si, di ; len
	;	push si ; right x
	;	sub si, di ; len
	;	call PutPixel
	;	push ax ; color
	;	push dx ; y
	;	push si ; left x
	;	call PutPixel

	;	inc dx
	;	inc bl
	;	cmp bl, 20
	;	jnz @@close 
	
		
		
		inc cx
		mov si, cx ; x mitkadem bashura
		dec di
		dec di   ; sub 2 to len
		push ax ; color
		push dx ; y
		add si, di ; len
		push si ; right x
		sub si, di ; len
		push si ; left x
		call DrawHLine

		inc dx
		inc bl
		push ax ; color
		push dx ; y
		add si, di ; len
		push si ; right x
		sub si, di ; len
		call PutPixel
		push ax ; color
		push dx ; y
		push si ; left x
		call PutPixel

		inc dx
		inc bl
		
		
		inc cx
		mov si, cx ; x mitkadem bashura
		dec di
		dec di   ; sub 2 to len
		push ax ; color
		push dx ; y
		add si, di ; len
		push si ; right x
		sub si, di ; len
		push si ; left x
		call DrawHLine

		inc dx
		inc bl
		push ax ; color
		push dx ; y
		add si, di ; len
		push si ; right x
		sub si, di ; len
		call PutPixel
		push ax ; color
		push dx ; y
		push si ; left x
		call PutPixel

		inc dx
		inc bl
		
		
		inc cx
		mov si, cx ; x mitkadem bashura
		dec di
		dec di   ; sub 2 to len
		push ax ; color
		push dx ; y
		add si, di ; len
		push si ; right x
		sub si, di ; len
		push si ; left x
		call DrawHLine

		inc dx
		inc bl
		push ax ; color
		push dx ; y
		add si, di ; len
		push si ; right x
		sub si, di ; len
		call PutPixel
		push ax ; color
		push dx ; y
		push si ; left x
		call PutPixel

		inc dx
		inc bl
		
		
				inc cx
		mov si, cx ; x mitkadem bashura
		dec di
		dec di   ; sub 2 to len
		push ax ; color
		push dx ; y
		add si, di ; len
		push si ; right x
		sub si, di ; len
		push si ; left x
		call DrawHLine

		inc dx
		inc bl
		push ax ; color
		push dx ; y
		add si, di ; len
		push si ; right x
		sub si, di ; len
		call PutPixel
		push ax ; color
		push dx ; y
		push si ; left x
		call PutPixel

		inc dx
		inc bl
		
		inc cx
		mov si, cx ; x mitkadem bashura
		dec di
		dec di   ; sub 2 to len
		push ax ; color
		push dx ; y
		add si, di ; len
		push si ; right x
		sub si, di ; len
		push si ; left x
		call DrawHLine

		inc dx
		inc bl
		push ax ; color
		push dx ; y
		add si, di ; len
		push si ; right x
		sub si, di ; len
		call PutPixel
		push ax ; color
		push dx ; y
		push si ; left x
		call PutPixel

		inc dx
		inc bl
		
	
	
		inc si
		push ax ; color
		push dx ; y
		push si ; x
		call PutPixel
		pop di si dx cx bx ax bp
		ret 6
Diamond2 endp



;=======================================================================
;Input : 3 words. 	
;			first Word - color (number 1-3).
;			second word - x of the high right corner.
;			third word - y of the high right corner.
;Return Value : None
;=======================================================================
Diamond1 proc
		push bp
		mov bp, sp
		push bx ax cx dx si di
		mov ax, [bp+4]		;PixelColor	( ah - not in use )
		mov dx, [bp+6]		;PixelY	
		mov cx, [bp+8]		;PixelX
		add cx, 8 		; middle of the card
		cmp al, 2
		jz @@c2
		jnc @@c3
	@@c1:	mov al, 2h ; Green
		jmp @@con
	@@c2:	mov al, 0ch  ; Red
		jmp @@con
	@@c3:	mov al, 5h  ; Purple
	@@con:	mov si, cx ; x goes to right
		mov di, cx ; x goes to left
		push ax ; color
		push dx ; y
		push si ; x
		call PutPixel
		xor bl, bl		; mone bakara for Y
		inc bl 			; start from 1
		inc dx
		inc bl
	;@@open:	dec di				;		*
	;	inc si				;	       * *
	;	push ax ; color		;	       * *
	;	push dx ; y			;	      *   *
	;	push si ; x			; 	      *   *
	;	call PutPixel	;            *     *
	;	push ax ; color	;            *     *
	;	push dx ; y             
	;	push di ; x
	;	call PutPixel
	;	inc dx
	;	inc bl 
	;	push ax ; color
	;	push dx ; y
	;	push si ; x
	;	call PutPixel
	;	push ax ; color
	;	push dx ; y
	;	push di ; x
	;	call PutPixel
	;	inc dx
	;	inc bl
	;	cmp bl, 12
	;	jnz @@open
	
		dec di				;1		*
		inc si				;	       * *
		push ax ; color		;	       * *
		push dx ; y			;	      *   *
		push si ; x			; 	      *   *
		call PutPixel	;            *     *
		push ax ; color	;            *     *
		push dx ; y             
		push di ; x
		call PutPixel
		inc dx
		inc bl 
		push ax ; color
		push dx ; y
		push si ; x
		call PutPixel
		push ax ; color
		push dx ; y
		push di ; x
		call PutPixel
		inc dx
		inc bl
		
		dec di				;2		*
		inc si				;	       * *
		push ax ; color		;	       * *
		push dx ; y			;	      *   *
		push si ; x			; 	      *   *
		call PutPixel	;            *     *
		push ax ; color	;            *     *
		push dx ; y             
		push di ; x
		call PutPixel
		inc dx
		inc bl 
		push ax ; color
		push dx ; y
		push si ; x
		call PutPixel
		push ax ; color
		push dx ; y
		push di ; x
		call PutPixel
		inc dx
		inc bl
		
		dec di				;3		*
		inc si				;	       * *
		push ax ; color		;	       * *
		push dx ; y			;	      *   *
		push si ; x			; 	      *   *
		call PutPixel	;            *     *
		push ax ; color	;            *     *
		push dx ; y             
		push di ; x
		call PutPixel
		inc dx
		inc bl 
		push ax ; color
		push dx ; y
		push si ; x
		call PutPixel
		push ax ; color
		push dx ; y
		push di ; x
		call PutPixel
		inc dx
		inc bl
		
		dec di				;4		*
		inc si				;	       * *
		push ax ; color		;	       * *
		push dx ; y			;	      *   *
		push si ; x			; 	      *   *
		call PutPixel	;            *     *
		push ax ; color	;            *     *
		push dx ; y             
		push di ; x
		call PutPixel
		inc dx
		inc bl 
		push ax ; color
		push dx ; y
		push si ; x
		call PutPixel
		push ax ; color
		push dx ; y
		push di ; x
		call PutPixel
		inc dx
		inc bl
		
		dec di				;5		*
		inc si				;	       * *
		push ax ; color		;	       * *
		push dx ; y			;	      *   *
		push si ; x			; 	      *   *
		call PutPixel	;            *     *
		push ax ; color	;            *     *
		push dx ; y             
		push di ; x
		call PutPixel
		inc dx
		inc bl 
		push ax ; color
		push dx ; y
		push si ; x
		call PutPixel
		push ax ; color
		push dx ; y
		push di ; x
		call PutPixel
		inc dx
		inc bl
		

	
	;@@close:	inc di
	;	dec si
	;	push ax ; color
	;	push dx ; y
	;	push si ; x
	;	call PutPixel
	;	push ax ; color
	;	push dx ; y
	;	push di ; x
	;	call PutPixel
	;	inc dx
	;	inc bl 
	;	push ax ; color
	;	push dx ; y
	;	push si ; x
	;	call PutPixel
	;	push ax ; color
	;	push dx ; y
	;	push di ; x
	;	call PutPixel
	;	inc dx
	;	inc bl
	;	cmp bl, 20
	;	jnz @@close
	
		inc di 				;12
		dec si
		push ax ; color
		push dx ; y
		push si ; x
		call PutPixel
		push ax ; color
		push dx ; y
		push di ; x
		call PutPixel
		inc dx
		inc bl 
		push ax ; color
		push dx ; y
		push si ; x
		call PutPixel
		push ax ; color
		push dx ; y
		push di ; x
		call PutPixel
		inc dx
		inc bl
	
	inc di 					; 13
		dec si
		push ax ; color
		push dx ; y
		push si ; x
		call PutPixel
		push ax ; color
		push dx ; y
		push di ; x
		call PutPixel
		inc dx
		inc bl 
		push ax ; color
		push dx ; y
		push si ; x
		call PutPixel
		push ax ; color
		push dx ; y
		push di ; x
		call PutPixel
		inc dx
		inc bl
	
	inc di 					; 14
		dec si
		push ax ; color
		push dx ; y
		push si ; x
		call PutPixel
		push ax ; color
		push dx ; y
		push di ; x
		call PutPixel
		inc dx
		inc bl 
		push ax ; color
		push dx ; y
		push si ; x
		call PutPixel
		push ax ; color
		push dx ; y
		push di ; x
		call PutPixel
		inc dx
		inc bl
	
	inc di 					; 15
		dec si
		push ax ; color
		push dx ; y
		push si ; x
		call PutPixel
		push ax ; color
		push dx ; y
		push di ; x
		call PutPixel
		inc dx
		inc bl 
		push ax ; color
		push dx ; y
		push si ; x
		call PutPixel
		push ax ; color
		push dx ; y
		push di ; x
		call PutPixel
		inc dx
		inc bl
	
	
	
		dec si 						; 20
		push ax ; color
		push dx ; y
		push si ; x
		call PutPixel
		pop di si dx cx bx ax bp
		ret 6
Diamond1 endp	


DrawFrame proc
		push bp
		mov bp, sp
		push bx ax cx dx si di
		mov dx, ss:[bp+4] ; y, high right corner
		mov cx, ss:[bp+6] ; x, high right corner
		mov ax, ss:[bp+8] ; color 
		
		dec cx
		dec cx
		dec cx
		
		push ax ; color   ; Draw High Horizontal lines
		dec dx
		dec dx
		dec dx
		push dx ; y
		add cx, 66
		push cx ; x2
		sub cx, 66
		push cx ; x1
		call DrawHLine
		
		push ax ; color
		inc dx
		push dx ; y
		add cx, 66
		push cx ; x2
		sub cx, 66
		push cx ; x1
		call DrawHLine
		
		push ax ; color
		inc dx
		push dx ; y
		add cx, 66
		push cx ; x2
		sub cx, 66
		push cx ; x1
		call DrawHLine
		
		add dx, 30   ; Draw Low Horizontal lines
		
		push ax ; color
		inc dx
		push dx ; y
		add cx, 66
		push cx ; x2
		sub cx, 66
		push cx ; x1
		call DrawHLine
		
		push ax ; color
		inc dx
		push dx ; y
		add cx, 66
		push cx ; x2
		sub cx, 66
		push cx ; x1
		call DrawHLine
		
		push ax ; color
		inc dx
		push dx ; y
		add cx, 66
		push cx ; x2
		sub cx, 66
		push cx ; x1
		call DrawHLine
		
		
		push ax ; color
		push dx ; y2
		sub dx, 33
		push dx ; y1
		push cx ; x
		call DrawVLine
		
		inc cx
		add dx, 33
		push ax ; color
		push dx ; y2
		sub dx, 33
		push dx ; y1
		push cx ; x
		call DrawVLine
		
		inc cx
		add dx, 33
		push ax ; color
		push dx ; y2
		sub dx, 33
		push dx ; y1
		push cx ; x
		call DrawVLine
		
		add cx, 61
		add dx, 30
		push ax ; color
		push dx ; y2
		sub dx, 30
		push dx ; y1
		push cx ; x
		call DrawVLine
		
		inc cx
		add dx, 30
		push ax ; color
		push dx ; y2
		sub dx, 30
		push dx ; y1
		push cx ; x
		call DrawVLine
		
		inc cx
		add dx, 30
		push ax ; color
		push dx ; y2
		sub dx, 30
		push dx ; y1
		push cx ; x
		call DrawVLine
		
		inc cx
		add dx, 30
		push ax ; color
		push dx ; y2
		sub dx, 30
		push dx ; y1
		push cx ; x
		call DrawVLine
		
		pop di si dx cx bx ax bp
		ret 6
	DrawFrame endp
		
		
	