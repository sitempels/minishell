# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sjacquet <sjacquet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/14 10:47:36 by stempels          #+#    #+#              #
#    Updated: 2025/06/05 17:14:56 by stempels         ###   ########.fr        #
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
debug: CCFLAGS = -g
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
LEXER_DIR = lexer
SRC_LEXER = $(addprefix $(LEXER_DIR)/, lexer lexer_utils)
#
PARSER_DIR = parser
SRC_PARSER = $(addprefix $(PARSER_DIR)/, parser parser_cmd parser_redirect parser_utils)
#
EXEC_DIR = exec
SRC_EXEC = $(addprefix $(EXEC_DIR)/, exec execute_cmd execute_redir)
#
EXPAND_DIR = expand
SRC_EXPAND = $(addprefix $(EXPAND_DIR)/, expander)
#
UTILS_DIR = utils
SRC_UTILS = $(addprefix $(UTILS_DIR)/, debug path env signal display)
#
SRCS ::= $(MAIN) $(SRC_LEXER) $(SRC_PARSER) $(SRC_EXEC) $(SRC_EXPAND) $(SRC_UTILS)
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
#----------------------------RULES---------------------------------------------#
all: $(NAME)
#
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CCFLAGS) $(CPPFLAGS) -c $< -o $@
#
lib:	$(LIBFT) 
$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)
#
$(NAME): $(OBJ) $(LIBFT) 
	$(CC) $(CCFLAGS) $(OBJ) -L$(LIBFT_DIR) $(LIB_FLAG) -o $(NAME)
	@echo "$(NAME) $(GREEN)created !$(NC)"

run: $(NAME)
	@./$(NAME)
#
clean:
	rm -rf $(OBJ_DIR)
	@echo "$(NAME) $(GREEN)$@ed !$(NC)"
#
libclean:
	$(MAKE) clean -C $(LIBFT_DIR)	
	rm -rf $(LIBFT)
#
fclean: clean
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
	@echo "$(NAME) created !$"
#
.PHONY: all clean libclean fclean ffclean re debug
#----------------------------TEXT----------------------------------------------#

#
#----------------------------MISC----------------------------------------------#
#
