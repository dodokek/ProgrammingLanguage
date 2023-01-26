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
push 0
; ----------
; popping variable sonnyi_ded
pop [1]
; ----------
; getting variable a
in
pop [2] 
; getting variable b
in
pop [3] 
; getting variable c
in
pop [4] 
; ----------
; ----------
; ----------
; ----------
push 4
; ----------
; pushing variable a
push [2]
; ----------
mul
; ----------
; pushing variable c
push [4]
; ----------
mul
; ----------
; pushing variable b
push [3]
; ----------
; pushing variable b
push [3]
; ----------
mul
; ----------
sub
; ----------
; popping variable miaukriminant
pop [5]
; ----------
; if begin
; pushing variable a
push [2]
; ----------
push 0
; ----------
jne if_label0

; ----------
; if true
; if begin
; pushing variable b
push [3]
; ----------
push 0
; ----------
jne if_label1

; ----------
; if true
; if begin
; pushing variable c
push [4]
; ----------
push 0
; ----------
jne if_label2

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
jmp else_label2

if_label2:
; if false
; printing variable sonnyi_ded
push [1] 
out
; ----------
; ----------
ret
; end of func

; ----------
; ----------
; ----------

else_label2:
; ----------
; ----------
; ----------
jmp else_label1

if_label1:
; if false
; pushing variable b
push [3]
; ----------
; pushing variable c
push [4]
; ----------
push 0
; ----------
sub
; ----------
div
; ----------
; popping variable otvet
pop [15]
; ----------
; printing variable otvet
push [15] 
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
pop [19]
; ----------
; ----------

else_label0:
; ----------
; ----------
; if begin
; pushing variable miaukriminant
push [5]
; ----------
push 0
; ----------
jne if_label3

; ----------
; if true
; pushing variable a
push [2]
; ----------
push 2
; ----------
mul
; ----------
; pushing variable b
push [3]
; ----------
push 0
; ----------
sub
; ----------
div
; ----------
; popping variable otvet
pop [15]
; ----------
; printing variable otvet
push [15] 
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

else_label3:
; ----------
; ----------
; if begin
push 0
; ----------
; pushing variable miaukriminant
push [5]
; ----------
jae if_label4

; ----------
; if true
; printing variable pustota
push [19] 
out
; ----------
; ----------
; printing variable pustota
push [19] 
out
; ----------
; ----------
ret
; end of func

; ----------
; ----------
; ----------
; ----------
jmp else_label4

if_label4:
; if false
push 2
; ----------
; pushing variable a
push [2]
; ----------
mul
; ----------
; pushing variable b
push [3]
; ----------
push 0
; ----------
sub
; ----------
; pushing variable miaukriminant
push [5]
; ----------
sqr
; ----------
add
; ----------
div
; ----------
; popping variable kotik1
pop [28]
; ----------
push 2
; ----------
; pushing variable a
push [2]
; ----------
mul
; ----------
; pushing variable miaukriminant
push [5]
; ----------
sqr
; ----------
; pushing variable b
push [3]
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
pop [32]
; ----------
; printing variable kotik1
push [28] 
out
; printing variable kotik2
push [32] 
out
; ----------
; ----------
; ----------
; ----------
; ----------
; ----------

else_label4:
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
; ----------
