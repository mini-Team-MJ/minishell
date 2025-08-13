# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ljh3900 <ljh3900@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/29 15:00:00 by JuHyeon           #+#    #+#              #
#    Updated: 2025/06/11 20:59:25 by ljh3900          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = minishell
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -Iincludes -Ilibft
LDFLAGS = -lreadline
RM      = rm -f

OBJDIR  = objs

SRCS = srcs/main.c \
	srcs/utils.c \
	srcs/execute/exe_utils_dir/cd_resolve_path.c \
	srcs/execute/exe_utils_dir/env_utils.c \
	srcs/execute/exe_utils_dir/execute_utils.c \
	srcs/execute/exe_utils_dir/export_unset_utils.c \
	srcs/execute/builtin/ft_cd.c \
	srcs/execute/builtin/ft_echo.c \
	srcs/execute/builtin/ft_env.c \
	srcs/execute/builtin/ft_exit.c \
	srcs/execute/builtin/ft_export.c \
	srcs/execute/builtin/ft_pwd.c \
	srcs/execute/builtin/ft_unset.c \
	srcs/execute/stub_pipline.c \
	srcs/parsing/arg_utils.c \
	srcs/parsing/com_utils.c \
	srcs/parsing/env_expansion.c \
	srcs/parsing/error_printers.c \
	srcs/parsing/free_functions.c \
	srcs/parsing/line_validator.c \
	srcs/parsing/make_args.c \
	srcs/parsing/make_coms.c \
	srcs/parsing/path_and_file_validators.c \
	srcs/parsing/print_tokens.c \
	srcs/parsing/random_utils.c \
	srcs/parsing/str_utils.c \
	srcs/parsing/tokenization.c \
	srcs/parsing/token_utils.c \
	srcs/parsing/token_validator.c \
	srcs/execute/execute.c

OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS) libft/libft.a
	$(CC) $(CFLAGS) $(OBJS) libft/libft.a $(LDFLAGS) -o $(NAME)

libft/libft.a:
	$(MAKE) -C libft

$(OBJDIR)/%.o: %.c includes/minishell.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -r $(OBJDIR)
	$(MAKE) -C libft clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re
.SECONDARY: $(OBJS)
