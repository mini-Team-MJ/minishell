/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyeonl <juhyeonl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 23:18:18 by ljh3900           #+#    #+#             */
/*   Updated: 2025/05/28 14:28:02 by juhyeonl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

# define INITIAL_CAP 16

enum	Types
{
	WORD,
	CAT,
	PIPE,
	CD,
	EXPORT,
	ENV,
	ECHO,
	UNSET,
	EXIT,
    	N,
	PWD,
	EV,
	RD_O,
	RD_O_APPEND,
	RD_I,
	READ_I,
};

typedef struct	t_token 
{
	size_t	id;
	enum	Types type;
	char	*str;
	int	int_val;
}   t_token ;

typedef struct	t_env
{
	char	*name;
	char	*value;
}	t_env;

/* 전역 시그널 플래그 (최대 1개) */
extern volatile sig_atomic_t g_signal;

/* 사용자 구현 부분 */
token_t    **tokenize(char *line);
void    execute(char **args);
void    free_tokens(char **args);

void    setup_signals(void);

#endif
