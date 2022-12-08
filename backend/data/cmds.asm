; function 
main:
PUSH 1
PUSH 1
ADD
RET
; end of func

PUSH 2
PUSH 5
JNE if_label0
CALL main
if_label0:
