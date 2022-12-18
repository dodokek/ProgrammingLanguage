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
; pushing variable b
push [1]
; ----------
; pushing variable b
push [1]
; ----------
mul
; ----------
sub
; ----------
; popping variable miaukriminant
pop [3]
; ----------
; printing variable miaukriminant
push [3] 
out
; ----------
; ----------
; if begin
; pushing variable a
push [0]
; ----------
push 0
; ----------
jne if_label0

; ----------
; if true
; pushing variable b
push [1]
; ----------
; pushing variable c
push [2]
; ----------
push 0
; ----------
sub
; ----------
div
; ----------
; popping variable otvet
pop [10]
; ----------
; printing variable otvet
push [10] 
out
; ----------
; ----------
ret
; end of func

; ----------
; ----------
; ----------
; ----------
jmp else_label0

if_label0:
; if false
push 3802
; ----------
; popping variable pustota
pop [14]
; ----------
; ----------

else_label0:
; ----------
; ----------
; if begin
push 0
; ----------
; pushing variable miaukriminant
push [3]
; ----------
jae if_label1

; ----------
; if true
; printing variable pustota
push [14] 
out
; ----------
; ----------
; printing variable pustota
push [14] 
out
; ----------
; ----------
ret
; end of func

; ----------
; ----------
; ----------
; ----------
jmp else_label1

if_label1:
; if false
push 2
; ----------
; pushing variable a
push [0]
; ----------
mul
; ----------
; pushing variable b
push [1]
; ----------
push 0
; ----------
sub
; ----------
; pushing variable miaukriminant
push [3]
; ----------
sqr
; ----------
add
; ----------
div
; ----------
; popping variable kotik1
pop [18]
; ----------
push 2
; ----------
; pushing variable a
push [0]
; ----------
mul
; ----------
; pushing variable miaukriminant
push [3]
; ----------
sqr
; ----------
; pushing variable b
push [1]
; ----------
push 0
; ----------
sub
; ----------
sub
; ----------
div
; ----------
; popping variable kotik2
pop [22]
; ----------
; printing variable kotik1
push [18] 
out
; printing variable kotik2
push [22] 
out
; ----------
; ----------
; ----------
; ----------
; ----------
; ----------

else_label1:
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
