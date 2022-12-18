call main
hlt

; let the chaos begin

; function 
main:
; ----------
push 0
; ----------
; popping variable pustota
pop [0]
; ----------
; getting variable a
in
pop [1] 
; getting variable b
in
pop [2] 
; getting variable c
in
pop [3] 
; ----------
; ----------
; ----------
; ----------
push 4
; ----------
; pushing variable a
push [1]
; ----------
mul
; ----------
; pushing variable c
push [3]
; ----------
mul
; ----------
; pushing variable b
push [2]
; ----------
; pushing variable b
push [2]
; ----------
mul
; ----------
sub
; ----------
; popping variable miaukriminant
pop [4]
; ----------
; if begin
; pushing variable a
push [1]
; ----------
push 0
; ----------
jne if_label0

; ----------
; if true
; pushing variable b
push [2]
; ----------
; pushing variable c
push [3]
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
ret
; end of func

; ----------
; ----------

else_label0:
; ----------
; ----------
; if begin
; pushing variable miaukriminant
push [4]
; ----------
push 0
; ----------
jne if_label1

; ----------
; if true
; printing variable pustota
push [0] 
out
; ----------
; ----------
; printing variable pustota
push [0] 
out
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
push [1]
; ----------
mul
; ----------
; pushing variable b
push [2]
; ----------
push 0
; ----------
sub
; ----------
; pushing variable miaukriminant
push [4]
; ----------
add
; ----------
div
; ----------
; popping variable kotik1
pop [17]
; ----------
push 2
; ----------
; pushing variable a
push [1]
; ----------
mul
; ----------
; pushing variable miaukriminant
push [4]
; ----------
; pushing variable b
push [2]
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
pop [21]
; ----------
; printing variable kotik1
push [17] 
out
; printing variable kotik2
push [21] 
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
