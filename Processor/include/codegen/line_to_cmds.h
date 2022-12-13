DEF_LINE("push", PUSH_LEN, 
    HandlePushPop (AsmInfo, line + PUSH_LEN + 1, PUSH)
)

DEF_LINE("pop", POP_LEN, 
    HandlePushPop (AsmInfo, line + POP_LEN + 1, POP)
)

DEF_LINE("jmp", JMP_LEN, 
    ParseJmp (AsmInfo, line + JMP_LEN, JMP)
)

DEF_LINE("j", J_LEN, 
    IsJmp (AsmInfo, line)
)

DEF_LINE("call", 4, 
    IsJmp (AsmInfo, line)
)