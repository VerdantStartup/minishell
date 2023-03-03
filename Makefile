# Marcos #

NAME 			= testing
LIBFT			= libft
SRC_DIR		= src/
OBJ_DIR		= obj/
CC				= gcc
CFLAGS		= -lreadline -I include
RM				= rm -rf

SRC_FILES	=	prepare_input utils helper_main env_substitution\

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
	@$(CC) $(CFLAGS) $(OBJ) libft.a -o $(NAME)
	@echo $(C_GREEN)"Test compilied"$(C_RESET)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJF)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJF):
	@mkdir -p $(OBJ_DIR)

clean:
	@$(RM) $(OBJ_DIR)
	@$(RM) $(OBJF)
	@make clean -C $(LIBFT)

fclean: clean
	@$(RM) $(NAME) $(NAMESV)
	@$(RM) $(LIBFT)/libft.a
	@$(RM) libft.a
	@find . -name ".DS_Store" -delete
	@echo "$(Red)All libs cleaned$(Reset)"

re: fclean start
	@echo "$(Yellow)Recomplied everything$(Reset)"

.PHONY: all clean fclean re
