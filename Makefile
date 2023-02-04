ifeq ($(OS),Windows_NT)
	OUTPUT_FILE_NAME = main.exe
else
    OUTPUT_FILE_NAME = main
endif


all :  
	make -C ./frontend -f MakeFile
