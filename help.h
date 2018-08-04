
FindSet proc
	push bp
	mov bp, sp
	push ax bx cx dx si di
	; ss:[bp+4] = srak
	; ss:[bp+6] = srak
	; ss:[bp+8] = srak
	mov dx, COB_Len
	add dx, dx
	sub dx, 4
	mov Help1, dx
	inc dx
	inc dx
	mov Help2, dx
	inc dx
	inc dx
	mov Help3, dx
	
	xor ax, ax
	
@@1:
	mov bx, ax
	add bx, 2
	
	mov cx, bx
	add cx, 2
	
	inc ax
	inc ax
	cmp ax, Help1
	jnc @@no
@@2:
	xor cx, cx
	inc bx
	inc bx
	cmp bx, Help2
	jnc @@1
@@3:
	inc cx
	inc cx
	cmp cx, Help3
	jnc @@2
	
	mov si, ax
	push COB[si]
	mov si, bx
	push COB[si]
	mov si, cx
	push COB[si]
	call CheckSet
	pop si
	cmp si, 1
	jz @@yes
	jmp @@3
	
@@yes:
	mov ss:[bp+4], ax
	mov ss:[bp+6], bx
	mov ss:[bp+8], cx
	jmp @@sof
	
@@no:
	mov si, 16
	mov ss:[bp+4], si
	mov ss:[bp+6], si
	mov ss:[bp+8], si
	
@@sof:
	pop di si dx cx bx ax bp
	ret 
FindSet endp


	

ShowHelp proc
	push bp
	mov bp, sp
	push ax bx cx dx si di
	
	push 0 0 0
	call FindSet
	pop ax
	pop bx
	pop cx
	cmp ax, 16
	jz @@NoSet
	
	push ax
	push 0
	call GetHighRightCorner
	pop di ; y
	pop si ; x
	push 0ah ; color
	push si ; x
	push di ; y
	call DrawFrame
	
	push bx
	push 0
	call GetHighRightCorner
	pop di ; y
	pop si ; x
	push 0ah ; color
	push si ; x
	push di ; y
	call DrawFrame
	
	push cx
	push 0
	call GetHighRightCorner
	pop di ; y
	pop si ; x
	push 0ah ; color
	push si ; x
	push di ; y
	call DrawFrame
	
	jmp @@sof
	
@@NoSet:

@@sof:	pop di si dx cx bx ax bp
	ret 
ShowHelp endp