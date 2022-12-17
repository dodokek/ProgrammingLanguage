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
; pushing variable kotik_pomen'bshe
push [4]
; ----------
; pushing variable kotik
push [0]
; ----------
mul
; ----------
; popping variable kotik
pop [0]
; ----------
; if begin
; pushing variable konservy
push [1]
; ----------
push 10
; ----------
jne if_label0

; ----------
; if false
ret
; end of func

; ----------
; ----------

if_label0:
; if true
call miautorial
; ----------
; ----------
; ----------
; ----------
ret
; end of func

; ----------
; ----------
; ----------
; ----------
; ----------
; ----------
; ----------
; ----------
; ----------
