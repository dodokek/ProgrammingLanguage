call main
hlt

; let the chaos begin

; function 
main:
; ----------
in 
pop [1] 
; ----------
push 0
; ----------
pop [2]
; ----------
call fak
; ----------
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
; function 
fak:
; ----------
; pushing variable kot
push [1]
; ----------
; pushing variable kot
push [1]
; ----------
mul
; ----------
pop [1]
; ----------
push 1
; ----------
; pushing variable schet
push [2]
; ----------
add
; ----------
pop [2]
; ----------
; if begin
; pushing variable schet
push [2]
; ----------
