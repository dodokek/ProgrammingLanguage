call main
hlt

; let the chaos begin

; function 
main:
push 2
pop [1]
call fak
push [1] 
out 
ret
; end of func

; function 
fak:
; pushing variable kot
push [1]
push 1
sub
pop [5]
; pushing variable kot
push [1]
; pushing variable lotok
push [5]
add
pop [1]
; if begin
; pushing variable kot
push [1]
push 20
je if_label0

; if false
call fak

if_label0:
; if true
ret
; end of func

