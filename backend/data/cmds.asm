call main
hlt

; let the chaos begin

; function 
main:
; ----------
push 3802
; ----------
; popping variable zhopka
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
; if begin
; pushing variable b
push [2]
; ----------
push 0
; ----------
jne if_label1

; ----------
; if true
; printing variable zhopka
push [0] 
out
; ----------
; ----------
ret
; end of func

; ----------
; ----------
; ----------
jmp else_label1

if_label1:
; if false
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
pop [12]
; ----------
; printing variable otvet
push [12] 
out
; ----------
; ----------
ret
; end of func

; ----------
; ----------
; ----------
; ----------

else_label1:
; ----------
; ----------
; ----------
jmp else_label0

if_label0:
; if false
push 1337
; ----------
; popping variable pustota
pop [16]
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
jne if_label2

; ----------
; if true
; pushing variable a
push [1]
; ----------
push 2
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
div
; ----------
; popping variable otvet
pop [12]
; ----------
; printing variable otvet
push [12] 
out
; ----------
; ----------
ret
; end of func

; ----------
; ----------
; ----------
; ----------
jmp else_label2

if_label2:
; if false

else_label2:
; ----------
; ----------
; if begin
push 0
; ----------
; pushing variable miaukriminant
push [4]
; ----------
jae if_label3

; ----------
; if true
; printing variable pustota
push [16] 
out
; ----------
; ----------
; printing variable pustota
push [16] 
out
; ----------
; ----------
ret
; end of func

; ----------
; ----------
; ----------
; ----------
jmp else_label3

if_label3:
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
sqr
; ----------
add
; ----------
div
; ----------
; popping variable kotik1
pop [25]
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
sqr
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
pop [29]
; ----------
; printing variable kotik1
push [25] 
out
; printing variable kotik2
push [29] 
out
; ----------
; ----------
; ----------
; ----------
; ----------
; ----------

else_label3:
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
; ----------
