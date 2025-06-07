/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh3900 <ljh3900@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 23:18:18 by ljh3900           #+#    #+#             */
/*   Updated: 2025/06/05 00:12:11 by ljh3900          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
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
	FILENAME,
};

typedef struct t_com
{
	size_t	pipe_count;
	_Atomic bool	has_rd;
	t_token *tokens;
}

typedef struct	t_token 
{
	size_t	id;
	enum	Types type;
	char	*str;
	int	int_val;
	_Atomic	bool	has_quotes;
	struct t_token *next;
	struct t_token *prev;
}   t_token ;

typedef struct	t_env
{
	char	*name;
	char	*value;
}	t_env;

extern volatile sig_atomic_t g_signal;

token_t    *tokenize(char *line, t_token *tokens);
void    free_tokens(char **args);

void    setup_signals(void);

void	execute(char *line, char ***env);

/* built-in command */
int		ft_cd(char **argv, char ***env);
int		ft_echo(char **argv);
int		ft_env(char **argv, char ***env);
int		ft_export(char **argv, char ***env);
int		ft_pwd(char **argv);
int		ft_unset(char **argv, char ***env);
int     ft_exit(char **argv, char ***env);

/* utils */
void	ft_free_2d_array(char **arr);

#endif
