BUILD_NAME=AVerTV

CC=gcc
OPT=3

PREFIX_SRC= ./src/
PREFIX_OBJ= ./obj/
PREFIX_BIN= ./bin/

SRC= main.c
OBJ= main.o

SRC:= $(addprefix $(PREFIX_SRC), $(SRC))
OBJ:= $(addprefix $(PREFIX_OBJ), $(OBJ))

FLUGS+= -lm
CFLUGS+= -Wall -O$(OPT)

ifeq ($(BUILD_STATUS),DEBUG)
	CFLUGS+= -D DEBUG
endif

$(PREFIX_BIN)$(BUILD_NAME) : $(OBJ)
	$(CC) $(OBJ) -o $(PREFIX_BIN)$(BUILD_NAME) $(FLUGS)
	ln -sf $(PREFIX_BIN)$(BUILD_NAME) $(BUILD_NAME)

$(PREFIX_OBJ)%.o : $(PREFIX_SRC)%.c
	$(CC) -c $< -o $@ $(CFLUGS)

clean :
	rm -fr $(PREFIX_BIN)* $(PREFIX_OBJ)*.o
	rm $(BUILD_NAME)
