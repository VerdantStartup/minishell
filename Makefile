#= Vars =#

NAME := minishell

SRCS := minishell.c

SRCSDIR := srcs

OBJDIR := obj

OBJ := $(addprefix $(OBJDIR)/,$(SRCS:.c=.o))

CFLAGS := -Wall -Wextra -MMD -g #add -Werror when done

export RL_LIB   := -L/Users/mwilsch/.brew/opt/readline/lib
export RL_INC   := -I/Users/mwilsch/.brew/opt/readline/include

LIBFT := libft/libft.a

INCLUDES := -I $(LIBFT) -I includes -I/opt/homebrew/Cellar/readline/8.2.1/include
#= COLORS =#

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

#= Targets =#

all: libft $(NAME)

$(NAME): $(OBJDIR) $(OBJ) $(LIBFT)
	@echo "$(GREEN)Building Minishell ...$(RESET)"
	@$(CC) $(OBJ) -lreadline -lhistory $(LIBFT) $(RL_LIB) $(INCLUDES) -o $(NAME)

$(OBJDIR)/%.o: $(addprefix $(SRCSDIR)/, %.c)
	@$(CC)  -c $(RL_INC) $(CFLAGS) $< -o $@ 

$(OBJDIR):
	@echo "$(GREEN)Building object files ...$(RESET)"
	@mkdir -p $(OBJDIR)

$(LIBFT):
	@echo "$(GREEN)Building libft ...$(RESET)"
	@$(MAKE) -C libft WITH_BONUS=1

clean:
	@echo "$(RED)Cleaning ...$(RESET)"
	@$(MAKE) -C libft clean
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -rf $(NAME) $(OBJDIR)
	@$(MAKE) -C libft fclean

re: fclean all