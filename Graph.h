;=======================================================================
;This procedure set the video mode.
;Input : Word. Low byte - the video mode , High byte - not in use.
;Return Value : None
;=======================================================================
SetVideoMode	Proc
			push bp
			mov bp, sp
			push ax
			mov ax, [bp+4]
			mov ah, 0
			int 10h
			pop ax
			pop bp
			ret 2
SetVideoMode	Endp			


;=======================================================================
;This procedure put a pixel on the screen
;Input : 3 Words. 
;			Firs word - X axis of the pixel.
;			Second word - Y axis of the pixel.
;			Third word - Low byte - The pixel color, High byte - Not in use.
;Return Value : None
;=======================================================================
PutPixel	Proc
			push bp
			mov bp, sp
			push ax
			push cx
			push dx
			mov cx, [bp+4]		;PixelX
			mov dx, [bp+6]		;PixelY
			mov ax, [bp+8]		;PixelColor	( ah - not in use )
			mov bh, 0			;PageNumber
			mov ah, 0ch
			int 10h
			pop dx
			pop cx
			pop ax
			pop bp
			ret 6
PutPixel	Endp

;=======================================================================
;This procedure draw a vertical line on the screen.
;Input : 4 Words. 
;			Firs word - X axis of the line.
;			Second word - The top Y axis of the line.
;			Third word - The bottom Y axis of the line.
;			Fourth word - Low byte - The pixel color, High byte - Not in use.
;Return Value : None
;=======================================================================
DrawVLine	Proc
			push bp
			mov bp, sp
			push ax
			push bx
			push cx
			push dx
			mov cx, [bp+4]		;cx <==== X1
			mov bx, [bp+6]		;bx <==== Y1
			mov dx, [bp+8]		;dx <==== Y2
			mov ax, [bp+10]		;AL <==== PixelColor ( ah - not in use )
vPutPxl:	mov ah, 0ch			;PutPixel x=cx, y=dx
			int 10h
			dec dx
			cmp dx, bx
			jnc vPutPxl
			pop dx
			pop cx
			pop bx
			pop ax
			pop bp
			ret 8
DrawVLine	Endp			



;=======================================================================
;This procedure draw a horizontal line on the screen.
;Input : 4 Words. 
;			Firs word - The left X axis of the line.
;			Second word - The right X axis of the line.
;			Third word - The Y axis of the line.
;			Fourth word - Low byte - The pixel color, High byte - Not in use.
;Return Value : None
;=======================================================================
DrawHLine	Proc
			push bp
			mov bp, sp
			push ax
			push bx
			push cx
			push dx
			mov bx, [bp+4]		;bx <==== X1
			mov cx, [bp+6]		;cx <==== X2
			mov dx, [bp+8]		;dx <==== Y1
			mov ax, [bp+10]		;AL <==== PixelColor ( ah, not in use )
hPutPxl:	mov ah, 0ch			;PutPixel x=cx, y=dx
			int 10h
			dec cx
			cmp cx, bx
			jnc hPutPxl
			pop dx
			pop cx
			pop bx
			pop ax
			pop bp
			ret 8
DrawHLine	Endp