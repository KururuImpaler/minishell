# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmalt <cmalt@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/22 12:50:02 by cmalt             #+#    #+#              #
#    Updated: 2020/10/22 19:35:03 by cmalt            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CLANG = gcc

FLAGS = -Wall -Werror -Wextra

INCLUDE = include/

SRCS =	source/cat_args.c \
		source/checkk_func.c \
		source/cmd.c \
		source/commands_get.c \
		source/commands_ut.c \
		source/env.c \
		source/errors.c \
		source/exit.c \
		source/func_cd_2.c \
		source/func_cd.c \
		source/func_echo.c \
		source/func_env.c \
		source/func_exit.c \
		source/func_export_2.c \
		source/func_export.c \
		source/func_pwd.c \
		source/func_unset.c \
		source/minishel.c \
		source/next_cmd.c \
		source/parse_command.c \
		source/path.c \
		source/pipe_2.c \
		source/pipe.c \
		source/read_anv.c \
		source/read_command.c \
		source/run_comand.c \
		source/signals.c \
		source/skip_symbols.c \
		source/syntax.c \
		source/write.c \
		source/zero.c

OBJS = $(SRCS:.c=.o)

DIR_LIBFT = libft/

LIBFT = $(DIR_LIBFT)libft.a

all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(DIR_LIBFT)

$(NAME): $(OBJS) $(LIBFT)
	$(CLANG) $(FLAGS) -o $@ $^

%.o: %.c 
	$(CLANG) $(FLAGS) -c $< -I $(INCLUDE) -o $@

clean:
	rm -f $(OBJS)
	$(MAKE) clean -C $(DIR_LIBFT)

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(DIR_LIBFT)

re: fclean all

.PHONY: all clean fclean re