ifeq ($(OS),Windows_NT)
	OUTPUT_FILE_NAME = main.exe
else
	OUTPUT_FILE_NAME = main
endif

FRONT_PATH = ./frontend
BACK_PATH = ./backend
ASM_PATH = ./execution/asm
PROC_PATH = ./execution/proc


all :   
	make -C $(FRONT_PATH) -f Makefile
	make -C $(BACK_PATH) -f Makefile
	make -C $(ASM_PATH) -f Makefile
	make -C $(PROC_PATH) -f Makefile

clear:
	make -C $(FRONT_PATH) -f Makefile clear
	make -C $(BACK_PATH) -f Makefile clear
	make -C $(ASM_PATH) -f Makefile clear
	make -C $(PROC_PATH) -f Makefile clear
