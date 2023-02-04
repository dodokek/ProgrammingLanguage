ifeq ($(OS),Windows_NT)
	OUTPUT_FILE_NAME = main.exe
else
	OUTPUT_FILE_NAME = main
endif


all :   
	make -C ./frontend -f MakeFile
	make -C ./backend -f MakeFile
	make -C ./execution/proc -f MakeFile
	make -C ./execution/asm -f MakeFile



clear:
	make -C ./frontend -f MakeFile clear
	make -C ./backend -f MakeFile clear
	make -C ./execution/proc -f MakeFile clear
	make -C ./execution/asm -f MakeFile clear
