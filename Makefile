# Marcos #

NAME 			= testing
LIBFT			= libft
SRC_DIR		= src/
OBJ_DIR		= obj/
CC				= gcc
CFLAGS		=  -g -lreadline -I include
RM				= rm -f

SRC_FILES	=	minishell_utils\

SRC			=	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ			=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

OBJF			= test

# Colors #

C_RESET = "\033[0m"
C_GREEN = "\033[92m"

ifdef DEBUG
	CFLAGS += -g -fsanitize=address
endif


start:
			@make -C $(LIBFT)
			@echo $(C_GREEN)"Libft complied"$(C_RESET)
			@cp $(LIBFT)/libft.a .
			@make all

all: $(NAME)
$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(INCLUDE) $(OBJ) libft.a -o $(NAME)
	@echo $(C_GREEN)"Test compilied"$(C_RESET)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJF)
	@$(CC) $(CFLAGS) -c $< $(INCLUDE) -o $@

$(OBJF):
	@mkdir -p $(OBJ_DIR)

fclean: clean
	@$(RM) $(NAME)
	@$(RM) -r $(OBJ_DIR)
	@echo "$(Red)All libs cleaned$(Reset)"

re: fclean all
	@echo "$(Yellow)Recomplied everything$(Reset)"

.PHONY: all clean fclean re
