# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sjacquet <sjacquet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/11 01:33:34 by sjacquet          #+#    #+#              #
#    Updated: 2025/07/30 15:45:30 by stempels         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -g -fPIC 
IFLAGS	=	-Iinc

INC = inc
SRC = src
OBJ = obj

BOOL_SRCS   = $(addprefix $(SRC)/bool/, ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_iseven.c ft_isintflow.c ft_islower.c ft_isprime.c ft_isprint.c ft_issign.c ft_isspace.c ft_isupper.c ft_isquote.c)
CRYPTO_SRCS = $(addprefix $(SRC)/crypto/, ft_adler32.c ft_bkdr.c ft_caesar.c ft_crc32.c ft_djb2.c ft_fnv1a.c ft_gcity.c ft_jenkins.c ft_murmur.c ft_rot13.c ft_sdbm.c ft_vigenere.c ft_xor.c)
FILE_SRCS   = $(addprefix $(SRC)/file/, ft_fappend.c ft_fcopy.c ft_fcountline.c ft_fcreate.c ft_fexists.c ft_getnextline.c)
GET_SRCS    = $(addprefix $(SRC)/get/, ft_getalpha.c ft_gethex.c)
LIST_SRCS   = $(addprefix $(SRC)/list/, ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c)
MATH_SRCS   = $(addprefix $(SRC)/math/, ft_abs.c ft_acos.c ft_acot.c ft_acsc.c ft_asec.c ft_asin.c ft_atan2.c ft_atan.c ft_cbrt.c ft_ceil.c ft_cos.c ft_cosh.c ft_cot.c ft_csc.c ft_exp2.c ft_exp.c ft_fact.c ft_fibon.c ft_floor.c ft_fract.c ft_gcd.c ft_hypot.c ft_iterfact.c ft_iterpow.c ft_lcm.c ft_ln.c ft_log10.c ft_log2.c ft_log.c ft_max.c ft_mean.c ft_min.c ft_pow2.c ft_pow.c ft_range.c ft_recfact.c ft_recpow.c ft_round.c ft_sec.c ft_sin.c ft_sinc.c ft_sinh.c ft_sqrt.c ft_tan.c ft_tanh.c ft_trunc.c ft_ultrange.c)
MEM_SRCS    = $(addprefix $(SRC)/mem/, ft_bzero.c ft_calloc.c ft_freeforall.c ft_memchr.c ft_memclear.c ft_memcmp.c ft_memcpy.c ft_memdup.c ft_memmove.c ft_memset.c ft_memswap.c ft_realloc.c)
NUM_SRCS    = $(addprefix $(SRC)/num/, ft_atoi_base.c ft_atoi.c ft_atol.c ft_atoul.c ft_itoa.c ft_numlen.c ft_ultoa.c ft_utoa.c ft_uitoa.c)
PUT_SRCS    = $(addprefix $(SRC)/put/, ft_printf.c ft_printf_fd.c ft_putaddr.c ft_putaddr_fd.c ft_putchar.c ft_putchar_fd.c ft_puthex.c ft_puthex_fd.c ft_putnbr_base_fd.c ft_putnbr.c ft_putnbr_fd.c ft_putstr.c ft_putstr_fd.c ft_putstrnl_fd.c)
STR_SRCS    = $(addprefix $(SRC)/str/, ft_strcap.c ft_strchr.c ft_strcmp.c ft_strcpy.c ft_strdup.c ft_strendw.c ft_striteri.c ft_strjoin.c ft_strjoin_var.c ft_strkcmp.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strlower.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strrem.c ft_strrev.c ft_strrpl.c ft_strsplit.c ft_strspn.c ft_strstartw.c ft_strsub.c ft_strtok.c ft_strtrim.c ft_strupper.c ft_stradup.c ft_stralen.c ft_strfmt.c ft_free_array_pos.c)
UTILS_SRCS  = $(addprefix $(SRC)/utils/, ft_baselen.c ft_getvalue.c ft_joinpath.c ft_process_fd.c ft_skipcset.c ft_tolower.c ft_toupper.c)

BOOL_OBJS	=	$(addprefix $(OBJ)/, $(BOOL_SRCS:.c=.o))
CRYPTO_OBJS	=	$(addprefix $(OBJ)/, $(CRYPTO_SRCS:.c=.o))
FILE_OBJS	=	$(addprefix $(OBJ)/, $(FILE_SRCS:.c=.o))
GET_OBJS	=	$(addprefix $(OBJ)/, $(GET_SRCS:.c=.o))
LIST_OBJS	=	$(addprefix $(OBJ)/, $(LIST_SRCS:.c=.o))
MATH_OBJS	=	$(addprefix $(OBJ)/, $(MATH_SRCS:.c=.o))
MEM_OBJS	=	$(addprefix $(OBJ)/, $(MEM_SRCS:.c=.o))
NUM_OBJS	=	$(addprefix $(OBJ)/, $(NUM_SRCS:.c=.o))
PUT_OBJS	=	$(addprefix $(OBJ)/, $(PUT_SRCS:.c=.o))
STR_OBJS	=	$(addprefix $(OBJ)/, $(STR_SRCS:.c=.o))
UTILS_OBJS	=	$(addprefix $(OBJ)/, $(UTILS_SRCS:.c=.o))

OBJS = $(BOOL_OBJS) $(CRYPTO_OBJS) $(FILE_OBJS) $(GET_OBJS) $(LIST_OBJS) $(MATH_OBJS) $(MEM_OBJS) $(NUM_OBJS) $(PUT_OBJS) $(STR_OBJS) $(UTILS_OBJS)

all: $(NAME)

$(NAME): $(OBJS)
	@ar rcs $@ $^

$(OBJ)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
