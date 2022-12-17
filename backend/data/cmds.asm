call main
hlt

; let the chaos begin

; function 
main:
; ----------
; getting variable nu_eto_vse
in
pop [0] 
; ----------
push 1
; ----------
; popping variable kotik
pop [1]
; ----------
push 1
; ----------
; popping variable konservy
pop [2]
; ----------
call miautorial
; ----------
; printing variable kotik
push [1] 
out
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
; function 
miautorial:
; ----------
push 1
; ----------
; pushing variable konservy
push [2]
; ----------
add
; ----------
; popping variable konservy
pop [2]
; ----------
; pushing variable konservy
push [2]
; ----------
; pushing variable kotik
push [1]
; ----------
mul
; ----------
; popping variable kotik
pop [1]
; ----------
; printing variable kotik
push [1] 
out
; ----------
; if begin
; pushing variable konservy
push [2]
; ----------
; pushing variable nu_eto_vse
push [0]
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
