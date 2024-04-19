BUILD_NAME=AVerTV

OS=

CC=clang
OP=3

PATH_SRC=./src/
PATH_OBJ=./obj/
PATH_LIB=./lib/
PATH_BIN=./bin/

SRC=main.c
OBJ=main.o
LIB=averapi.so

ifeq ($(OS),WIN)
	CC:=x86_64-w64-mingw32-gcc
	BUILD_NAME:= $(addsuffix .exe,$(BUILD_NAME))
	LIB:=averapi.dll
endif

FLAGS+=-lusb-1.0
CFLAGS+=-Wall -O$(OP)

SRC:= $(addprefix $(PATH_SRC),$(SRC) )
OBJ:= $(addprefix $(PATH_OBJ),$(OBJ) )
LIB:= $(addprefix $(PATH_LIB),$(LIB) )
BUILD_NAME_LN:=$(BUILD_NAME)
BUILD_NAME:= $(addprefix $(PATH_BIN),$(BUILD_NAME) )


$(BUILD_NAME) : $(OBJ) $(LIB)
	$(CC) $(FLAGS) -o $(BUILD_NAME) $(OBJ) $(LIB)
	ln -sf $(BUILD_NAME) $(BUILD_NAME_LN)

$(PATH_OBJ)%.o : $(PATH_SRC)%.c
	$(CC) -c $< -o $@ $(CFLAGS)

$(LIB) :
	make -C lib/AVerAPI/ OS=$(OS) OP=$(OP)

clean :
	rm $(BUILD_NAME) $(PATH_OBJ)*.o $(BUILD_NAME_LN)
	make -C lib/AVerAPI/ clean
