EXEC = output
AT	= @
CC = gcc
SRC_DIR := srcs/
OBJ_DIR := objs/
INC = includes/
FLAGS := -g -Wall -Werror -Wextra
# libraries to use readline functions
LIB =  -I$(INC) -L/usr/local/lib -I/usr/local/include -lreadline
LIBFT = libft/
# subdirectories to create in obj folder
SUBDIRS = $(addprefix $(OBJ_DIR),$(shell find srcs/ -type d | cut -c 6-))
# files without main folder and files with subdirectories if exit
C_FILES = $(shell find srcs/ -iname *.c | cut -c 6-)
# files with main directory and files with subdirectories if exist 
SRCS = $(addprefix $(SRC_DIR),$(C_FILES))
# objects from main folder srcs and subfolders
OBJ = $(addprefix $(OBJ_DIR),$(C_FILES:.c=.o))

all: libft $(EXEC)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	mkdir -p $(OBJ_DIR) $(SUBDIRS)
	$(CC) -I$(INC) $(FLAGS) -c $< -o $@

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $@ $(LIB) $(LIBFT)libft.a

# rule to debug Makefile
print:
	$(info OBJS = $(OBJ))
	$(info only files= $(C_FILES))
	$(info files with path = $(SRCS))
	$(info subdirectories = $(SUBDIRS))

libft:
	$(MAKE) -C $(LIBFT)

clean:
	rm -rf $(OBJ_DIR)
	make -C $(LIBFT) clean


fclean: clean
	rm -rf $(EXEC)
	make -C $(LIBFT) fclean
	
re: fclean all

.PHONY: libft fclean all