call main
hlt

; let the chaos begin

; if begin
push 2
; ----------
push 2
; ----------
je if_label0

; ----------
; if false
push 1
; ----------
; popping variable kot
pop [0]
; ----------
; ----------

if_label0:
; if true
