call main
hlt

; let the chaos begin

; function 
main:
; ----------
push 1
; ----------
; popping variable kotik
pop [0]
; ----------
push 1
; ----------
; popping variable konservy
pop [1]
; ----------
call miautorial
; ----------
ret
; end of func

; ----------
; ----------
; ----------
; ----------
; ----------
; ----------
; function 
miautorial:
; ----------
push 1
; ----------
; pushing variable konservy
push [1]
; ----------
add
; ----------
; popping variable konservy
pop [1]
; ----------
; pushing variable konservy
push [1]
; ----------
push 1
; ----------
sub
; ----------
; popping variable kotik_pomen'bshe
pop [4]
; ----------
; popping variable kotik
pop [0]
; ----------
; ----------
; ----------
; ----------
; ----------
; ----------
; ----------
