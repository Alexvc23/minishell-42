EXEC = output
CC = gcc
SRC_DIR := srcs/
OBJ_DIR := objs/
INC = includes/
FLAGS := -g -Wall -Werror -Wextra
LIB =  -I$(INC) -L/usr/local/lib -I/usr/local/include -lreadline
C_FILES = $(shell find . -iname *.c | cut -d "/" -f 3)
SRCS = $(addprefix $(SRC_DIR),$(C_FILES))
OBJ = $(addprefix $(OBJ_DIR),$(C_FILES:.c=.o))

all: $(EXEC) 

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	mkdir -p $(OBJ_DIR)
	$(CC) -I$(INC) $(FLAGS) -c $< -o $@

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $@ $(LIB)

print:
	$(info OBJS = $(OBJ))
	$(info only files= $(C_FILES))
	$(info files with paht = $(SRCS))

print-%  : ; @echo $* = $($*)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(EXEC)

re: fclean all
	