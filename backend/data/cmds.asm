call main
hlt

; let the chaos begin

; function 
; pushing variable main
push [0]
; ----------
push 2
; ----------
; popping variable kot
pop [1]
; ----------
push 0
; ----------
; popping variable schet
pop [2]
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
; pushing variable miautorial
push [3]
; ----------
; pushing variable kot
push [1]
; ----------
; pushing variable kot
push [1]
; ----------
mul
; ----------
; popping variable kot
pop [1]
; ----------
push 1
; ----------
; pushing variable schet
push [2]
; ----------
add
; ----------
; popping variable schet
pop [2]
; ----------
; if begin
; pushing variable schet
push [2]
; ----------
push 10
; ----------
je if_label0

; ----------
; if false
call miautorial
; ----------
; ----------

if_label0:
; if true
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
; ----------
