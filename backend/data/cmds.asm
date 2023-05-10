call main 
ret

; let the chaos begin

; function 
main:
push 1
; popping variable bebra
pop [0+rax]
push 1
; popping variable tekushch
pop [1+rax]
push 2
; popping variable topchik
pop [2+rax]
; pushing function call param: bebra
push [0+rax]
; pushing function call param: tekushch
push [1+rax]
; pushing function call param: topchik
push [2+rax]
; switching namespace
push 4
push rax
add
pop rax
; calling func
call fak
; switching namespace
push 4
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
; poping function argument: verkh
pop [0+rax]
; poping function argument: sus
pop [1+rax]
; poping function argument: rez
pop [2+rax]
; pushing variable sus
push [1+rax]
push 1
add
; popping variable sus
pop [1+rax]
; pushing variable rez
push [2+rax]
; pushing variable sus
push [1+rax]
mul
; popping variable rez
pop [2+rax]
push 123
; popping variable bebra
pop [3+rax]
; if begin
; pushing variable sus
push [1+rax]
; pushing variable verkh
push [0+rax]
jne if_label0

; if true
; returning the value from var: rez
push [2+rax]
ret
; end of func

jmp else_label0

if_label0:
; if false
; pushing function call param: rez
push [2+rax]
; pushing function call param: sus
push [1+rax]
; pushing function call param: verkh
push [0+rax]
; switching namespace
push 5
push rax
add
pop rax
; calling func
call fak
; switching namespace
push 5
push rax
sub
pop rax
; popping variable rez
pop [2+rax]

else_label0:
; returning the value from var: rez
push [2+rax]
ret
; end of func

; goodbye
hlt
