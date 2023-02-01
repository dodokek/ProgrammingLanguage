call main 
hlt

; let the chaos begin

; function 
main:
push 0
; popping variable ded
pop [0+rax]
; getting variable ded
in
pop [0+rax] 
push 0
; popping variable otec
pop [1+rax]
; getting variable otec
in
pop [1+rax] 
push 0
; popping variable brat
pop [2+rax]
; getting variable brat
in
pop [2+rax] 
push 0
; popping variable greatded
pop [3+rax]
push 0
; popping variable greatbab
pop [4+rax]
; if begin
; pushing variable ded
push [0+rax]
; if true
push 4
; pushing variable ded
push [0+rax]
mul
; pushing variable brat
push [2+rax]
mul
sub
; popping variable godfather
pop [5+rax]
; if begin
push 0
; pushing variable godfather
push [5+rax]
jae if_label1

; if true
; printing variable greatded
push [3+rax] 
out
; printing variable greatbab
push [4+rax] 
out
push 1
ret
; end of func

jmp else_label1

if_label1:
; if false
push 1
ret
; end of func


else_label1:
jmp else_label0

if_label0:
; if false
; if begin
; pushing variable otec
push [1+rax]
; if true
; printing variable greatded
push [3+rax] 
out
push 1
ret
; end of func

jmp else_label2

if_label2:
; if false
push 1
ret
; end of func


else_label2:

else_label0:
push 0
ret
; end of func

