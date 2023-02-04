ifeq ($(OS),Windows_NT)
	OUTPUT_FILE_NAME = main.exe
else
    OUTPUT_FILE_NAME = main
endif

CC = g++
# CFLAGS = -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -D_DEBUG -D_EJUDGE_CLIENT_SIDE
CFLAGS = -Wshadow
IFLAGS = -I./include/ 

#main

SRC_DIR = ./
OBJ_DIR = ./lib/

SRC = fileUtils.cpp parser_frontend.cpp stringUtils.cpp main.cpp translitor.cpp
OBJ = $(patsubst %.cpp, $(OBJ_DIR)%.o, $(SRC)) 

#SRC = $(wildcard $(SRC_DIR)*.cpp)
#OBJ = $(patsubst $(SRC_DIR)%.cpp, $(OBJ_DIR)%.o, $(SRC)) 

#linking
all : $(OBJ) 
	$(CC) $(IFLAGS) $(CFLAGS) $^ -o $(OUTPUT_FILE_NAME)

#main
$(OBJ_DIR)%.o : $(SRC_DIR)%.cpp
	echo $(OBJ)
	$(CC) $(IFLAGS) $(CFLAGS) -c $^ -o $@

clear: 
	rm -f $(OBJ_DIR)*.o