call main 
hlt

; let the chaos begin

; function 
main:
push 1
; popping variable bebra
pop [0+rax]
push 1
; popping variable verkh
pop [1+rax]
; pushing function call param: bebra
push [0+rax]
; pushing function call param: verkh
push [1+rax]
; switching namespace
push 3
push rax
add
pop rax
; calling func
call fak
; switching namespace
push 3
push rax
sub
pop rax
; popping variable bebra
pop [0+rax]
; printing variable bebra
push [0+rax] 
out
ret
; end of func

; function 
fak:
; poping function argument: sus
pop [0+rax]
; poping function argument: rez
pop [1+rax]
; pushing variable sus
push [0+rax]
push 1
add
; popping variable sus
pop [0+rax]
; pushing variable rez
push [1+rax]
; pushing variable sus
push [0+rax]
mul
; popping variable rez
pop [1+rax]
; printing variable sus
push [0+rax] 
out
; printing variable rez
push [1+rax] 
out
; if begin
; pushing variable sus
push [0+rax]
push 10
jne if_label0

; if true
; returning the value from var: rez
push [1+rax]
ret
; end of func

jmp else_label0

if_label0:
; if false
; pushing function call param: rez
push [1+rax]
; pushing function call param: sus
push [0+rax]
; switching namespace
push 3
push rax
add
pop rax
; calling func
call fak
; switching namespace
push 3
push rax
sub
pop rax
; popping variable rez
pop [1+rax]

else_label0:
; returning the value from var: rez
push [1+rax]
ret
; end of func

