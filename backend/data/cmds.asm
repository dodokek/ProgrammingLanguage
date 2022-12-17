call main
hlt

; let the chaos begin

; function 
main:
; ----------
; getting variable a
in
pop [0] 
; getting variable b
in
pop [1] 
; getting variable c
in
pop [2] 
; ----------
; ----------
; ----------
; ----------
call bebra
; ----------
; if begin
; pushing variable miaukriminant
push [3]
; ----------
push 0
; ----------
jne if_label0

; ----------
; if false
push 0
; ----------
; pushing variable b
push [1]
; ----------
push 2
; ----------
; pushing variable a
push [0]
; ----------
mul
; ----------
div
; ----------
sub
; ----------
; popping variable kotik1
pop [4]
; ----------
; printing variable kotik1
push [4] 
out
; ----------
; ----------
; ----------
; ----------

if_label0:
; if true
push 0
; ----------
; pushing variable b
push [1]
; ----------
sub
; ----------
; pushing variable miaukriminant
push [3]
; ----------
add
; ----------
push 2
; ----------
; pushing variable a
push [0]
; ----------
mul
; ----------
div
; ----------
; popping variable kotik1
pop [4]
; ----------
push 0
; ----------
; pushing variable b
push [1]
; ----------
sub
; ----------
; pushing variable miaukriminant
push [3]
; ----------
sub
; ----------
push 2
; ----------
; pushing variable a
push [0]
; ----------
mul
; ----------
div
; ----------
; popping variable kotik2
pop [12]
; ----------
; printing variable kotik1
push [4] 
out
; printing variable kotik2
push [12] 
out
; ----------
; ----------
; ----------
; ----------
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
; function 
bebra:
; ----------
; popping variable miaukriminant
pop [3]
; ----------
; pushing variable b
push [1]
; ----------
; pushing variable b
push [1]
; ----------
mul
; ----------
push 4
; ----------
; pushing variable a
push [0]
; ----------
mul
; ----------
; pushing variable c
push [2]
; ----------
mul
; ----------
sub
; ----------
sqr
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
