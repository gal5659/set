cleanBuffer proc
	push bp
	mov bp, sp
	push ax bx cx dx si di
	xor si, si
@@a:
	mov buffer[si], '$'
	inc si
	cmp si, buffer_Len
	jnz @@a
	
	pop di si dx cx bx ax bp
	ret
cleanBuffer endp

HighScoreTable proc
	push bp
	mov bp, sp
	push ax bx cx dx si di
	
	call ClrScrn

	call cleanBuffer
	
	mov ax,3d00h                             ;; read-only mode
	mov dx,offset data_file               
	int 21h
	
	mov file_handle, ax

	;reading file
	mov ah,3fh
	mov bx,file_handle
	mov cx,29h		; how many bytes do you want to read
	mov dx,offset buffer
	int 21h

	mov ah,3eh		; close file
	mov bx,file_handle
	int 21h
	
	mov dl, 0
	mov dh, 0
	push dx
	call GoToXY
	mov dx, offset buffer
	push dx
	call PutS

	pop di si dx cx bx ax bp
	ret 
HighScoreTable endp	
	
ShowInstructions proc
	push bp
	mov bp, sp
	push ax bx cx dx si di
	
	call ClrScrn
	call cleanBuffer
	
	mov ax,3d00h                             ;; read-only mode
	mov dx,offset instructions_file               
	int 21h
	
	mov file_handle, ax

	;reading file
	mov ah,3fh
	mov bx,file_handle
	mov cx,29h		; how many bytes do you want to read
	mov dx,offset buffer
	int 21h

	mov ah,3eh		; close file
	mov bx,file_handle
	int 21h
	
	mov dl, 0
	mov dh, 0
	push dx
	call GoToXY
	mov dx, offset buffer
	push dx
	call PutS

	pop di si dx cx bx ax bp
	ret 
ShowInstructions endp