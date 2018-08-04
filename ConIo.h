;=======================================================================
;This procedure clear the screen and GoToXy 0,0
;Input : None
;Return Value : None
;=======================================================================
ClrScrn proc		
		push ax
		push cx
		push dx
		mov dl, 10
		mov ah, 2
		mov cx, 50
ClrLine:int 21h
		loop ClrLine
		
		;GoToXy (0,0)
		xor bh, bh		;Page number - 0
		xor dx, dx		;dl<---Column=0  ,  dh<---Line=0
		mov ah, 2
		int 10h
		
		pop dx
		pop cx				
		pop ax
		ret
ClrScrn EndP


;=======================================================================
;This procedure moves the cursor to new position (line,column)
;Input : Word. Low byte - column , High byte - line, 
;Return Value : None
;=======================================================================
GoToXY	proc
		push bp
		mov bp, sp
		Push ax
		Push dx
		mov dx, [bp+4]	;dl<---Column  ,  dh<---Line
		xor bh, bh
		mov  ah,2       ;The function number	
		int  10h        ;The interrupt number
		Pop dx
		Pop ax
		pop bp
		ret 2
GoToXY	EndP


;=======================================================================
;This procedure moves the cursor to the begining of the next line
;Input : None
;Return Value : None
;=======================================================================
NewLine	Proc
		push ax
		push dx
		mov dl, 10
		mov ah, 2
		int 21h
		mov dl, 13
		mov ah, 2
		int 21h
		pop dx
		pop ax
		ret
NewLine Endp


;=======================================================================
;This procedure writes a character on the screen
;Input : Word. Low byte - the character , High byte - not in use.
;Return Value : None
;=======================================================================
PutCh	Proc
		push bp
		mov bp, sp
		push ax
		push dx
		mov dx, [bp+4]		;The character in DL
		mov ah, 2
		int 21h
		pop dx
		pop ax
		pop bp
		ret 2
PutCh	Endp


;=======================================================================
;This procedure writes a character on the screen, 
;and moves the cursor to the begining of the next line.
;Uses : NewLine Proc
;Input : Word. Low byte - the character , High byte - not in use.
;Return Value : None
;=======================================================================
PutChar	Proc
		push bp
		mov bp, sp
		push ax
		push dx
		mov dx, [bp+4]
		mov ah, 2
		int 21h
		call NewLine
		pop dx
		pop ax
		pop bp
		ret 2
PutChar	Endp


;=======================================================================
;This procedure writes a string on the screen.
;Input : Word. The string address.
;Return Value : None
;=======================================================================
PutS	Proc
		push bp
		mov bp, sp
		push ax
		push dx
		mov dx, [bp+4]
		mov ah, 9
		int 21h
		pop dx
		pop ax
		pop bp
		ret 2
PutS	EndP




;=======================================================================
;This procedure writes on the screen a Decimal byte, stored in a string 
;Input : Word. The Number. ( The number is in the right 4 bits, only )
;Return Value : None
;=======================================================================
ShowDecimalByte	Proc
		push bp
		mov bp, sp
		push ax
		push dx
		mov ax, [bp+4]	;The number is in al
		xor ah, ah		;For the div command
		mov dl, 10h
		div dl
		mov dx, ax
		add dx, 3030h
		
		;The next 2 lines is an option. ( Mark with stars )
		;To show only 1 digit in case the number is less then 10h - it shows ( 7 insted of 07 )
		;cmp dl, 30h			;***********
		;jz ShowRightDigit		;***********
		
		mov ah, 2
		int 21h
ShowRightDigit:
		mov dl, dh
		mov ah, 2
		int 21h
		pop dx				 
		pop ax
		pop bp
		ret 2
ShowDecimalByte	Endp


;=======================================================================
;This procedure writes on the screen a Decimal word, stored in a string 
;Input : Word. The Number.
;Return Value : None
;=======================================================================
ShowDecimalWord	Proc
		push bp
		mov bp, sp
		mov bx, [bp+4]
		mov al, bh
		push ax
		call ShowDecimalByte
		mov al, bl
		push ax
		call ShowDecimalByte
		pop bp
		ret 2
ShowDecimalWord	Endp


;=======================================================================
;This procedure gets a character from the user. 
;The character isn't shown on the screen.
;Input : None
;Return Value : AL <===== Ascii code of the character 
;=======================================================================
GetCh	Proc
		mov ah, 7
		int 21h
		ret
GetCh	EndP


;=======================================================================
;This procedure gets a character from the user. 
;The character is shown on the screen.
;Input : None
;Return Value : AL <===== Ascii code of the character 
;=======================================================================
GetChE	Proc
		mov ah, 1
		int 21h
		ret
GetChE	EndP


;=======================================================================
;This procedure gets a character from the user,
;and moves the cursor to the begining of the next line.
;The character is shown on the screen. 
;Uses : NewLine Proc
;Input : None
;Return Value : AL <===== Ascii code of the character 
;=======================================================================
GetChar	Proc
		mov ah, 7
		int 21h
		call NewLine
		ret
GetChar	EndP

;=======================================================================
;This procedure returns the postion of the cursor : Line and Column
;Input : None
;Return Value : DX : DH <---- Line Number   ,  DL <----- Column Number
;=======================================================================
GetCursorPostion	Proc
		push ax
		push bx
		mov ah, 3
		mov bh, 0
		int 10h			; DH <---- Line Number   ,  DL <----- Column Number
		pop bx
		pop ax
		ret
GetCursorPostion	Endp	