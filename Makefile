# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sjacquet <sjacquet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/14 10:47:36 by stempels          #+#    #+#              #
#    Updated: 2025/07/09 11:36:34 by stempels         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#MAKEFLAGS += --silent
#
NAME_PROJECT = minishell 
NAME = $(NAME_PROJECT)
debug: NAME = $(addprefix debug_, $(NAME_PROJECT))
TYPE = EXEC
#----------------------------COMPILER------------------------------------------#
CC = cc
debug: CC = gcc 
CCFLAGS = -Wall -Wextra -Werror
debug: CCFLAGS = -g3
CPPFLAGS = $(INC_FLAG)
#
#----------------------------LINKER--------------------------------------------#
#----------------------------DEBUG---------------------------------------------#
#----------------------------HEADER--------------------------------------------#
INC_DIR = inc
INC_FLAG = -I$(INC_DIR)
#
#----------------------------SRC-----------------------------------------------#
MAIN = main
SRC_DIR = src
#
ENV_DIR = env
SRC_ENV = $(addprefix $(ENV_DIR)/, env_list env_node env_utils env_from_envp env_del env_sort)
#
LEXER_DIR = lexer
SRC_LEXER = $(addprefix $(LEXER_DIR)/, lexer lexer_utils)
#
PARSER_DIR = parser
SRC_PARSER = $(addprefix $(PARSER_DIR)/, parser parser_cmd here_doc parser_utils)
#
EXEC_DIR = exec
SRC_EXEC = $(addprefix $(EXEC_DIR)/, exec execute_redir exec_utils)
#
EXPAND_DIR = expand
SRC_EXPAND = $(addprefix $(EXPAND_DIR)/, expand process_arg expand_wordsplitting expand_quoteremoval expand_utils expand_string expand_exit expand_var)
#
BUILTIN_DIR = builtin
SRC_BUILTIN = $(addprefix $(BUILTIN_DIR)/, cd echo env exit export pwd unset)
#
UTILS_DIR = utils
SRC_UTILS = $(addprefix $(UTILS_DIR)/, debug error path signal display shell cleaning redir)
#
SRCS ::= $(MAIN) $(SRC_LEXER) $(SRC_ENV) $(SRC_PARSER) $(SRC_EXEC) $(SRC_EXPAND) $(SRC_BUILTIN) $(SRC_UTILS)
SRC = $(addprefix $(SRC_DIR)/, $(addsuffix .c, $(SRCS))) 
#
#----------------------------OBJ-----------------------------------------------#
OBJ_DIR = obj
OBJ = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))
#
#----------------------------LIB-----------------------------------------------#
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
INC_FLAG += -I $(LIBFT_DIR)/$(INC_DIR)
LIB_FLAG = -lft -lreadline 
#
#----------------------------MISC----------------------------------------------#
DEPENDS = $(patsubst %.c, %.d, $(SRC))
#
#----------------------------RULES---------------------------------------------#
#
all: $(NAME)
#
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c Makefile
	@mkdir -p $(@D)
	$(CC) $(CCFLAGS) $(CPPFLAGS) -MMD -MP -c $< -o $@
#
lib:	$(LIBFT) 
$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)
#
$(NAME): $(OBJ) $(LIBFT) 
	$(CC) $(CCFLAGS) $(OBJ) -L$(LIBFT_DIR) $(LIB_FLAG) -o $(NAME)
	@echo "$(NAME) $(GREEN)created !$(NC)"
	@mkdir -p .here_doc

run: $(NAME)
	@./$(NAME)
#
clean:
	rm -rf $(OBJ_DIR) $(DEPENDS)
	@echo "$(NAME) $(GREEN)$@ed !$(NC)"
#
libclean:
	$(MAKE) clean -C $(LIBFT_DIR)	
	rm -rf $(LIBFT)
#
fclean: clean
	rm -rf .here_doc
	rm -rf $(NAME)
	rm -rf $(addprefix debug_, $(NAME))
	$(MAKE) fclean -C $(LIBFT_DIR)	
	@echo "$(NAME) $(GREEN)$@ed !$(NC)"
#
ffclean: fclean libclean
#
re: ffclean all
#
debug: clean $(OBJ) $(LIBFT) 
	$(CC) $(CCFLAGS) $(OBJ) -L$(LIBFT_DIR) $(LIB_FLAG) -o $(NAME)
	@echo "$(NAME) created !"
#
-include $(DEPENDS)
#
.PHONY: all clean libclean fclean ffclean re debug
#----------------------------TEXT----------------------------------------------#

#
#----------------------------MISC----------------------------------------------#
#
