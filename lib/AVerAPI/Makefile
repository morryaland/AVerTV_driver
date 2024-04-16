BUILD_NAME:=averapi.so

OS=

CC=gcc
OP=3

PATH_SRC=./src/
PATH_OBJ=./obj/
PATH_BIN=../

SRC=aver_device.c
OBJ=aver_device.o

ifeq ($(OS),WIN)
	CC:=x86_64-w64-mingw32-gcc
	BUILD_NAME:=averapi.dll
endif

FLAGS+=-shared -lusb-1.0
CFLAGS+=-Wall -O$(OP) -fPIC

SRC:= $(addprefix $(PATH_SRC),$(SRC) )
OBJ:= $(addprefix $(PATH_OBJ),$(OBJ) )
BUILD_NAME:= $(addprefix $(PATH_BIN),$(BUILD_NAME) )


$(BUILD_NAME) : $(OBJ)
	$(CC) -o $(BUILD_NAME) $(OBJ) $(FLAGS)

$(PATH_OBJ)%.o : $(PATH_SRC)%.c
	$(CC) -c $< -o $@ $(CFLAGS)

clean :
	rm $(BUILD_NAME) $(PATH_OBJ)*.o
