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
; printing variable miaukriminant
push [4] 
out
; ----------
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
pop [13]
; ----------
; printing variable otvet
push [13] 
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
pop [17]
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
pop [13]
; ----------
; printing variable otvet
push [13] 
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
ret
; end of func

; ----------
; ----------

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
push [17] 
out
; ----------
; ----------
; printing variable pustota
push [17] 
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
pop [26]
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
pop [30]
; ----------
; printing variable kotik1
push [26] 
out
; printing variable kotik2
push [30] 
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
; ----------
