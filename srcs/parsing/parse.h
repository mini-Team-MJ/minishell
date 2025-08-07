/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurtamo <mhurtamo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 21:16:56 by mhurtamo          #+#    #+#             */
/*   Updated: 2025/08/07 21:17:02 by mhurtamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

enum	Types
{
	WORD,
	COMMAND,
	PIPE,
	CD,
	EXPORT,
	ECHO,
	UNSET,
	EXIT,
	N,
	PWD,
	EV,
	RD_O,
	RD_O_APPEND,
	RD_I,
	HERE_DOC,
	REL_PATHF,
	PATH,
	LSIG,
};

typedef struct	t_token
{
	size_t	id;
	enum	Types type;
	char	*str;
	int	int_val;
	bool    sq;
	bool    dq;
	struct t_token *next;
	struct t_token *prev;
}	t_token ;

typedef struct	t_com
{
	int	pipe_fd[2];
	char	**args;
	char	*path;
	char	*infile;
	char	*outfile;
	enum Types	type;
	bool	is_piped;
	bool	is_empty;
	bool	redir_type_in;
	bool	redir_type_out;
	struct t_com	*next;
	struct t_com	*prev;
}	t_com;

typedef struct t_env
{
	char			*name;
	char			*value;
	struct t_env	*next;
}	t_env;

typedef struct	t_shell
{
	struct	t_com  *commands;
	struct	t_token *tokens;
	struct	t_env	*envs;
	char **lines;
	int	lsig;
}	t_shell;

bool	does_contain_meta(t_token *token);
bool	is_pipe_or_rd(t_token *token);
bool	token_validator(t_token **tokens);
size_t	increment_index(char *line);

void	set_type(t_token *token);
ssize_t	count_token_amount(char *line);
size_t	handle_rd(char *line);
size_t	rd_loop(char *line);
size_t	defloop(char *line);

size_t	token_len(char *line, t_token *token);
char	*token_dup(char *line, t_token *token);
t_token	*make_token(char *line);
void	add_token(t_token **stack, t_token *new);
t_token	*tokenize(char *line, t_token **stack);

bool	ftstrcmp(char *s1, char *s2);
int	ftstrncmp(char *s1, char *s2, size_t n);
bool	is_meta(char c);
size_t	custom_len(char *line);
char	*custom_dup(char *line);

void	setenv_type(t_token *t);
int	is_whitespace(char c);
size_t	handle_sq(char *line);
size_t	handle_dq(char *line);
bool	is_rd(char c);

void	write_str(char *str);
void	print_tokens(t_token **tokens);

t_com	*make_com(t_token **tokens, t_shell *shell);
void	add_com(t_com *new, t_com **coms);
t_com	*make_coms(t_token **tokens, t_com **coms, t_shell *shell);
void	expand_env_com_types(t_com **coms);
t_com	*init_coms(t_token **tokens, t_com **coms, t_shell *shell);

void	set_com_type(char *str, t_com *token);
size_t	arg_mover(char *str);
char	*make_arg(char *str, t_shell *shell);
char	**args_creation_loop(t_token **tokens, char **args,
	t_shell *shell, size_t ac);
char	**make_args(t_token **tokens, t_shell *shell);

bool	check_sq(char *line);
bool	check_dq(char *line);
bool	q_check_handler(char *line, char q);
size_t	q_count_handler(char *line, char q);
bool	line_validator(char *line);

void	free_args(char **args);
void	free_coms(t_com **coms);
void	free_tokens(t_token **tokens);
void	free_both(t_shell *shell);

char	*joiner(char *arg, char *env, char *res, char *name);
char	*custom_join(char *arg, char *env, bool got_envs, char *name);
char	*get_sig_val(int lsig);
char	*parse_env(char *str, char *name, t_shell *shell, bool got_envs);
char	*env_parse_handler(char *str, char *name, t_shell *shell, bool
got_envs);

size_t	count_args(t_token **tokens);
size_t	count_coms(t_token **tokens);
void	fill_o_dir(t_com *new, t_token *d);
void	fill_in_dir(t_com *new, t_token *d);
void	setup_directors(t_com *new, t_token **tokens);

t_env	*find_env(char *name, t_env **envs);
char	*make_name(char *str);
size_t	get_arg_len(char *arg);
size_t	get_len(char *str);
size_t	move_env(char *res, char *env);

#endif
