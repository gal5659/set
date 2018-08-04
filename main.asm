locals
dseg    segment
;=====================set==================================

    SetCharacters       dw 3h dup(?)
    SetIndexim          dw 3h dup(?)
    HEFRESH equ '0'
    HEFRESHKATAN    equ 'A'-10-'0'
    
    StartingSecond dw 0
    StartingMinute dw 0
    StartingHour dw 0
    
    Help1 dw 0
    Help2 dw 0
    Help3 dw 0
    
    minute db '0'
    second db '0'
    
    CardsPack   dw  1111h,1112h,1113h,1121h,1122h,1123h,1131h,1132h,1133h,1211h,1212h,1213h,1221h,1222h,1223h,1231h,1232h,1233h,1311h,1312h,1313h,1321h,1322h,1323h,1331h,1332h,1333h,2111h,2112h,2113h,2121h,2122h,2123h,2131h,2132h,2133h,2211h,2212h,2213h,2221h,2222h,2223h,2231h,2232h,2233h,2311h,2312h,2313h,2321h,2322h,2323h,2331h,2332h,2333h,3111h,3112h,3113h,3121h,3122h,3123h,3131h,3132h,3133h,3211h,3212h,3213h,3221h,3222h,3223h,3231h,3232h,3233h,3311h,3312h,3313h,3321h,3322h,3323h,3331h,3332h,3333h
    CLength     dW  ($-CardsPack)/2
    COB_Len     dw  0ch 
    COB         dw  0fh dup(?)
    CursorX         dw 7h
    CursorY         dw 7h
    CardNow         dw 0h
    MoneChosenCards dw 0h
    MoneSetim       dw 0h
    
    

    GName   db 'Set$'
    S1  db 'play - p$'
    S2  db 'instructions - i$'
    ;S3 db 'high scores table - h$'
    S4  db 'back to this menu (from the game) - m$'
    S4b db 'back to the Main Menu - n$'
    S5  db 'exit - Esc$'
    S6  db 'There if no more card in the CardsPack.$'
    S7  db 'You have finished the game!$'
    S8  db 'press any key to continue.$'

    askName db 'enter your name (up to 10 chars) and press enter$'
    b4UserName db 0dh, 0ah
    userName db 11 dup('$')
    userNameLength dw 11

;=====================set==================================

;=====================Meshulav============================= 

    GraphicsMode    dw 0Dh  ;320x200 ; 16 colors ; 40X25 mode text
    TextMode        dw  3h

    Koteret db 'Main Menu$'
    K1  db 'Set - 1$'
    K2  db 'Malkot - 2$'

    data_file db "C:\TASM\BIN\MalkotI.txt",0
    file_handle dw ?

    buffer db 100h dup('$')
    buffer_Len dw ($-buffer)


    instructions_file db "C:\TASM\BIN\instruc.txt",0


;=====================Meshulav=============================

;=====================Malkot===============================
    a           db 0,0,0,0,0,0,0,0
    A_GET_LENGTH1 = $-a
                db 0,0,0,0,0,0,0,0
                db 0,0,0,0,0,0,0,0
                db 0,0,0,0,0,0,0,0
                db 0,0,0,0,0,0,0,0
                db 0,0,0,0,0,0,0,0
                db 0,0,0,0,0,0,0,0
                db 0,0,0,0,0,0,0,0
    A_GET_LENGTH0 = ($-a)/A_GET_LENGTH1
    EndMat db ?
    
    KoteretM db 'The 8 Queens Puzzle$'
    KoteretM2 db 'Press any key twice, and press any key  (which is not Esc) to view the next     solution. Press Esc for the main menu.$'

    LastSolutionMsg db 'Last Solution!$'
    LastMsg1 db 'there are $'
    LastMsg2 db ' differnt solutions.$'
    ExitMsg db 'press Esc for exit or m for the main    menu.$'

    Al_Len = A_GET_LENGTH1 + A_GET_LENGTH0 - 1

    am  db  A_GET_LENGTH1 dup(0)
    RL  db  Al_Len dup(0)
    LR  db  Al_Len dup(0)
    
    mone db 0
    
    result db 0
;=====================Malkot===============================
dseg    ends

sseg    segment stack
        dw 500h dup(?)
sseg    ends

cseg    segment
assume  cs:cseg, ds:dseg, ss:sseg

include Graph.h
include conio.h
include file.h

;================set functions==================
include Cards.h
include keyboard.h
include COB.h
include help.h
include others.h    
;================set functions==================


;===============Malkot functions================
include MalkotF.h
;===============Malkot functions================


    
START: mov ax, dseg
    mov ds, ax
    push GraphicsMode
    call SetVideoMode
Lalala:
@@MainMenu: 
    call clrscrn
    mov dl, 0
    mov dh, 0
    push dx
    call GoToXY
    push offset Koteret
    call PutS

    inc dh
    inc dh
    push dx
    call GoToXY
    push offset K1
    call PutS
    
    inc dh
    push dx
    call GoToXY
    push offset K2
    call PutS

    inc dh
    push dx
    call GoToXY
    push offset S5
    call PutS

@@waitForKeyM: mov   ah,01H
              int   16H
              jnz   @@gotKeyM       ;jmp if key is ready
        jmp @@waitForKeyM
        
@@gotKeyM:  mov ah, 00H        ;key is ready, get it
                    int 16H            ;now process the key
        
        @@SG:   
            cmp al,'1'
            jz @@SetGame
        @@ML:
            cmp al,'2'
            jnz @@bye
            jmp MalkotProject
        @@bye:  cmp al,27
            jnz @@waitForKeyM
            mov ah, 4ch 
            int 21h 



@@SetGame:
@@menu:
    call clrscrn
    mov dl, 0
    mov dh, 0
    push dx
    call GoToXY
    push offset GName
    call PutS

    inc dh
    inc dh
    push dx
    call GoToXY
    push offset S1
    call PutS

    inc dh
    push dx
    call GoToXY
    push offset S2
    call PutS

    inc dh
    push dx
    call GoToXY
    push offset S4
    call PutS


    inc dh
    push dx
    call GoToXY
    push offset S4b
    call PutS

    inc dh
    push dx
    call GoToXY
    push offset S5
    call PutS
    


@@waitForKey1: mov   ah,01H
              int   16H
              jnz   @@gotKey1       ;jmp if key is ready
        jmp @@waitForKey1
        
@@gotKey1:          mov ah, 00H        ;key is ready, get it
                    int 16H            ;now process the key
        
        @@play: 
            cmp al,'p'
            jnz @@instructions
            jmp @@theGame
        @@instructions:
            cmp al,'i'
            jnz @@backMenu
            call ShowInstructions
            jmp @@waitForKey1
        @@backMenu: 
            cmp al,'m'
            jnz @@backMainMenu
            jmp @@menu
        @@backMainMenu: 
            cmp al,'n'
            jnz @@exit
            jmp @@MainMenu
        @@exit:
            cmp al,27
            jnz @@waitForKey1
            mov ah, 4ch 
            int 21h 
                            

@@theGame:
        call GetPlayerName
        
        call ClrScrn
        
        call NewGame
        

@@marker:   ; marker the chosen cards
            
            call ShowMoneSetim
            
            ; ????? ??????????? ????? ???
            push CardNow
            push 0
            call GetHighRightCorner
            pop dx ; y
            pop cx ; x
            ; ?????
            push 0eh ; yellow frame
            push cx ; x
            push dx ; y
            call DrawFrame      
            
            xor si, si
            mov bx, COB_Len
            add bx, COB_Len
            jmp @@go
    @@go: 
            mov ax, COB[si]
            shl ax, 1
            jnc @@con
            ; ????? ??????????? ????? ???
            push si
            push 0
            call GetHighRightCorner
            pop dx ; y
            pop cx ; x
            ; ?????
            push 1 ; blue frame
            push cx ; x
            push dx ; y
            call DrawFrame
            mov bx, COB_Len
            add bx, COB_Len
        @@con: inc si
            inc si
            cmp si, bx
            jnz @@go
            jmp @@waitForKey

@@waitForKey: 
                

              mov   ah,01H
              int   16H
              jnz   @@gotKey       ;jmp if key is ready
              jmp @@waitForKey
        
@@gotKey:           mov ah, 00H        ;key is ready, get it
                    int 16H            ;now process the key
            @@d:        cmp al,'d'
                    jnz @@a
                    call DClick         ;right
                    jmp @@marker
            @@a:        cmp al,'a'
                    jnz @@s
                    call AClick         ;left
                    jmp @@marker
            @@s:        cmp al,'s'
                    jnz @@w
                    call SClick         ;down
                    jmp @@marker
            @@w:        cmp al,'w'
                    jnz @@q
                    call WClick         ; up
                    jmp @@marker
            @@q:    cmp al,'q'
                    jnz @@three
                    call QClick         ; choose. 
                    jmp @@marker
            @@three: cmp al, '3'
                    jnz @@Help
                    call ThreeClick
                    jmp @@marker
            @@Help: cmp al, 'h'
                    jnz @@bye1
                    call ShowHelp
                    jmp @@marker
        
            @@bye1: cmp al,27
                jz @@cont
                jmp @@marker
            @@cont: mov MoneSetim, 0
                mov cx, userNameLength
                mov si, offset userName
            @@lool: mov ds:[si], 0
                inc si
                loop @@lool

                jmp Lalala
EmptyCardsPack: call ClrScrn
        mov dx, 0
        push dx
        call GoToXY
        push offset S6
        call PutS

        inc dh
        push dx
        call GoToXY
        push offset S7
        call PutS

        inc dh
        push dx
        call GoToXY
        push offset S8
        call PutS       
@@waitForKeyFinished: 

        mov   ah,01H
                int   16H
                jnz   @@gotKeyFinished       ;jmp if key is ready
        jmp @@waitForKeyFinished
        
@@gotKeyFinished: mov ah, 00H        ;key is ready, get it
                int 16H            ;now process the key
        
        jmp Lalala

MalkotProject:
        call ClrScrn

    xor dx, dx
    push dx
    call GoToXY
    push offset KoteretM
    call PutS

    inc dh
    inc dh
    push dx
    call GoToXY
    push offset KoteretM2
    call PutS

@@waitForKeyMalkot: 

        mov   ah,01H
                int   16H
                jnz   @@gotKeyMalkot       ;jmp if key is ready
        jmp @@waitForKeyMalkot
        
@@gotKeyMalkot: mov ah, 00H        ;key is ready, get it
                int 16H            ;now process the key
        
        cmp al, 27
        jnz @@continue
        jmp Lalala
@@continue: call ClrScrn
    push 0
    call TsorLoach
;Globalsof:
    
@@waitForKeyMalkotE1: 

        mov   ah,01H
                int   16H
                jnz   @@gotKeyMalkotE1       ;jmp if key is ready
        jmp @@waitForKeyMalkotE1
        
@@gotKeyMalkotE1: mov ah, 00H        ;key is ready, get it
                int 16H            ;now process the key
            
    call ClrScrn
        
    mov dl, 0
    mov dh, 0
    push dx
    call GoToXY
    push offset LastMsg1
    call PutS
    
    xor ah, ah
    mov al, mone
    push ax
    push 10
    call HamaratBasis
    call printword

    push offset LastMsg2
    call PutS

    mov dl, 0
    mov dh, 2
    push dx
    call GoToXY
    push offset ExitMsg
    call PutS

@@waitForKeyMalkotE2: 

        mov   ah,01H
                int   16H
                jnz   @@gotKeyMalkotE2       ;jmp if key is ready
        jmp @@waitForKeyMalkotE2
        
@@gotKeyMalkotE2: mov ah, 00H        ;key is ready, get it
                int 16H            ;now process the key
        cmp al, 27
        jz @@TheEnd
        cmp al, 'm'
        jnz @@waitForKeyMalkotE2
        jmp Lalala

@@TheEnd:
        int 3h
cseg    ends
end     Start       