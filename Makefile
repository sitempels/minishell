NAME    =   minishell
CC      =   cc
CFLAGS  =   -Wall -Wextra -Werror -g
IFLAGS  =   -Iinc -Ilibft/inc
LFLAGS  =   -lreadline
LIBFT   =   libft/libft.a

SRC     =   src
OBJ     =   obj
SRCS    =   $(addprefix $(SRC)/, ft_main.c ft_execute.c ft_handl_env.c ft_handl_wild.c ft_parse.c ft_tokenize.c ft_free.c ft_handl_oper.c ft_handl_word.c ft_minishell.c ft_token.c ft_tree.c ft_debug.c ft_signal.c)
OBJS    =   $(SRCS:$(SRC)/%.c=$(OBJ)/%.o)

VOID	=	> /dev/null 2>&1

# **************************************************************************** #
#                                  RULES                                       #
# **************************************************************************** #



all: $(NAME)	

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(IFLAGS) $(OBJS) $(LIBFT) $(LFLAGS) -o $(NAME)

$(LIBFT):
	make -C libft

$(OBJ):
	mkdir -p $(OBJ)

# Compile the source files into object files
$(OBJ)/%.o: $(SRC)/%.c | $(OBJ)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

run: $(NAME)
	./$(NAME)

norm:
	clear && norminette

leak: $(NAME)
	valgrind --leak-check=full ./$(NAME)

ltrace: $(NAME)
	ltrace ./$(NAME)

strace: $(NAME)
	strace ./$(NAME)

lldb: $(NAME)
	lldb ./$(NAME)

gdb: $(NAME)
	gdb ./$(NAME)

clean:
	rm -rf ./.vscode
	rm -rf $(OBJ)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: all run leak ltrace strace lldb gdb clean fclean re
