call main 
hlt

; let the chaos begin

; function 
main:
push 3802
; popping variable zhopka
pop [0+rax]
; getting variable a
in
pop [-1+rax] 
; getting variable b
in
pop [-1+rax] 
; getting variable c
in
pop [-1+rax] 
push 4
; pushing variable a
push [1+rax]
mul
; pushing variable c
push [3+rax]
mul
; pushing variable b
push [2+rax]
; pushing variable b
push [2+rax]
mul
sub
; popping variable miaukriminant
pop [4+rax]
; printing variable miaukriminant
push [4+rax] 
out
; if begin
; pushing variable a
push [1+rax]
push 0
jne if_label0

; if true
; if begin
; pushing variable b
push [2+rax]
push 0
jne if_label1

; if true
; printing variable zhopka
push [0+rax] 
out
ret
; end of func

jmp else_label1

if_label1:
; if false
; pushing variable b
push [2+rax]
; pushing variable c
push [3+rax]
push 0
sub
div
; popping variable otvet
pop [5+rax]
; printing variable otvet
push [5+rax] 
out
ret
; end of func


else_label1:
jmp else_label0

if_label0:
; if false
push 1337
; popping variable pustota
pop [6+rax]

else_label0:
; if begin
; pushing variable miaukriminant
push [4+rax]
push 0
jne if_label2

; if true
; pushing variable a
push [1+rax]
push 2
mul
; pushing variable b
push [2+rax]
push 0
sub
div
; popping variable otvet
pop [5+rax]
; printing variable otvet
push [5+rax] 
out
ret
; end of func

jmp else_label2

if_label2:
; if false
ret
; end of func


else_label2:
; if begin
push 0
; pushing variable miaukriminant
push [4+rax]
jae if_label3

; if true
; printing variable pustota
push [6+rax] 
out
; printing variable pustota
push [6+rax] 
out
ret
; end of func

jmp else_label3

if_label3:
; if false
push 2
; pushing variable a
push [1+rax]
mul
; pushing variable b
push [2+rax]
push 0
sub
; pushing variable miaukriminant
push [4+rax]
sqr
add
div
; popping variable kotik1
pop [7+rax]
push 2
; pushing variable a
push [1+rax]
mul
; pushing variable miaukriminant
push [4+rax]
sqr
; pushing variable b
push [2+rax]
push 0
sub
sub
div
; popping variable kotik2
pop [8+rax]
; printing variable kotik1
push [7+rax] 
out
; printing variable kotik2
push [8+rax] 
out

else_label3:
ret
; end of func

