
# ****     ****     **     **   ** ******** ******** ** **       ********
# /**/**   **/**    ****   /**  ** /**///// /**///// /**/**      /**/////
# /**//** ** /**   **//**  /** **  /**      /**      /**/**      /**
# /** //***  /**  **  //** /****   /******* /******* /**/**      /*******
# /**  //*   /** **********/**/**  /**////  /**////  /**/**      /**////
# /**   /    /**/**//////**/**//** /**      /**      /**/**      /**
# /**        /**/**     /**/** //**/********/**      /**/********/********
# //         // //      // //   // //////// //       // //////// ////////

EXEC = minishell 
AT	= @
CC = gcc
SRC_DIR := srcs/
OBJ_DIR := objs/
INC = includes/
FLAGS := -g -Wall -Werror -Wextra 
SYSTEM = $(shell uname -s)

# libraries to use readline functions
RL_LIB      := -L/usr/local/opt/readline/lib    
RL_INC      := -I/usr/local/opt/readline/include    
LIB =  $(RL_INC) $(RL_LIB) -lreadline  

LIBFT = libft/
# subdirectories to create in obj folder
SUBDIRS = $(addprefix $(OBJ_DIR),$(shell find srcs/ -type d | cut -c 6-))
# files without main folder and files with subdirectories if exit
C_FILES = $(shell find srcs/ -iname *.c | cut -c 6-)
# files with main directory and files with subdirectories if exist 
SRCS = $(addprefix $(SRC_DIR),$(C_FILES))
# objects from main folder srcs and subfolders
OBJ = $(addprefix $(OBJ_DIR),$(C_FILES:.c=.o))

# ─── Color ──────────────────────────────────────────────────────────────────────
RESET	= 	\033[0;0m
ERASE	=	\033[2K\r
GREY	=	\033[30m
RED		=	\033[31m
GREEN	=	\033[32m
YELLOW	=	\033[33m
BLUE	=	\033[34m
PINK	=	\033[35m
CYAN	=	\033[36m
WHITE	=	\033[37m
BOLD	=	\033[1m
UNDER	=	\033[4m
SUR		=	\033[7m
END		=	\033[0m
CENTER	=	\033[60G

# ─── Rules ──────────────────────────────────────────────────────────────────────
all: libft $(EXEC)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(AT)mkdir -p $(OBJ_DIR) $(SUBDIRS)
	$(AT)$(CC) $(RL_INC) -I$(INC) $(FLAGS) -c $< -o $@
	$(AT)printf "$(CYAN) Creating ----> $(RESET)$(BOLD)$(WHITE) $@ $(GREEN)$(CENTER)$(CENTER) ( ✔ ) ️$(END)\n"

$(EXEC) : $(OBJ)
	 $(AT)$(CC) $(OBJ) $(LIB) $(LIBFT)libft.a -o $@
	$(AT)printf "$(BOLD) $(RED) Executable ----> $(RESET)$(BOLD)$(CYAN) $@ $(GREEN)$(CENTER) ( ✔ ) ️$(END)\n"

# rule to debug Makefile
print:
	$(info OBJS = $(OBJ))
	$(info only files= $(C_FILES))
	$(info files with path = $(SRCS))
	$(info subdirectories = $(SUBDIRS))

libft:
	$(AT)$(MAKE) -sC $(LIBFT)

clean:
	$(AT)rm -rf $(OBJ_DIR)
	$(AT)make  -sC  $(LIBFT) clean
	@printf "$(BOLD)$(RED)(MINISHELL) ----> $(RESET)$(BOLD)$(WHITE) Removing objects $(END)\n"


fclean: 
	$(AT)rm -rf $(OBJ_DIR) $(EXEC)
	$(AT)make -sC$(LIBFT) fclean
	@printf "$(BOLD)$(RED)(MINISHELL) ----> $(RESET)$(BOLD)$(WHITE) Cleaning everything up $(END)\n"
	
re: fclean all

.PHONY: libft fclean all
.SILENT: 