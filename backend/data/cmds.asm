; function 
main:
push 1
push 1
add
ret
; end of func

; if begin
push 1
push 2
jne if_label0

; if true
push 2
pop [88]

if_label0:
; if false
; if begin
push 3
; pushing variable X
push [88]
jne if_label1

; if true
push 123

if_label1:
; if false
push 546
