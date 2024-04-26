BUILD_NAME:=../averapi.so

OS=

CC=gcc
OP=3

PATH_SRC=./src/
PATH_OBJ=./obj/
PATH_BIN=./bin/

SRC=aver_device.c aver_RCA.c 
OBJ=aver_device.o aver_RCA.o

ifeq ($(OS),WIN)
	CC:=x86_64-w64-mingw32-gcc
	BUILD_NAME:=averapi.dll
endif

FLAGS+=-shared
CFLAGS+=-Wall -O$(OP) -fPIC

SRC:= $(addprefix $(PATH_SRC),$(SRC) )
OBJ:= $(addprefix $(PATH_OBJ),$(OBJ) )

$(BUILD_NAME) : $(OBJ)
	$(CC) -o $(BUILD_NAME) $(OBJ) $(FLAGS)

$(PATH_OBJ)%.o : $(PATH_SRC)%.c
	$(CC) -c $< -o $@ $(CFLAGS)

clean :
	rm $(BUILD_NAME) $(PATH_OBJ)*.o
