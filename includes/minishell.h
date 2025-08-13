/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh3900 <ljh3900@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 23:18:18 by ljh3900           #+#    #+#             */
/*   Updated: 2025/06/11 22:14:46 by ljh3900          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <errno.h>
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>

# define INITIAL_CAP 16
# define TRUE 1
# define FALSE 0

#define GRN  "\033[1;32m"
#define RESET "\033[0m"


enum	Types
{
	WORD,
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
	HERE_DOC,
	PATH,
	REL_PATHF,
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
}	t_token;

typedef struct	t_com
{
	int	pipe_fd[2];
	char	**args;
	char	*path;
	char	*infile;
	char	*outfile;
	enum Types	type;
	bool	is_piped;
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
	int				last_exit;		// LEE: added it for 'echo $?'
}	t_shell;

// Temporary
typedef struct t_cmd
{
	char **argv;
	int    fd_in;
	int    fd_out;
	int    append;
}   t_cmd;

extern volatile sig_atomic_t g_signal;

// t_token    **tokenize(char *line);
void    free_tokens(t_token **args);

void    setup_signals(void);

void	execute(char *line, t_shell *sh);

/* utils */
void	ft_free_2d_array(char **arr);
void	err_with_cmd(char *prefix, char *arg, char *suffix);


/********** execute **********/
/***** builtin *****/
/* built-in-command */
int		ft_cd(char **argv, t_env **env_list);
int		ft_echo(char **argv, t_env *env_list, int last_exit);
int		ft_env(char **argv, t_env *env_list);
int		ft_export(char **argv, t_env **env_list);
int		ft_pwd(char **argv);
int		ft_unset(char **argv, t_env **env_list);
void	ft_exit(char **argv);
int		ft_str_isalpha(char *str);

/***** exe_utils_dir *****/
/* env_utils */
t_env	*env_new(const char *name, const char *value);
int		env_add_back(t_env **lst, t_env *new_node);
void	env_clear(t_env **lst);
t_env	*env_init(char **envp);
t_env	*env_find(t_env *lst, const char *name);

/* export_unset_utils */
int		export_cleanup(char *name, char *value, t_env *node, int ret_code);
int		is_valid_name(const char *s);
void	print_export_list(t_env *env);
int		env_remove(t_env **lst, const char *name);

/* cd_resolve_path.c */
char	*resolve_path(char *arg, t_env *env_list, int *alloc_flag);

/* execute_utils.c */
bool	is_builtin(const char *cmd);
int		handle_builtin(char **argv, t_env **env_list, t_shell *sh);

/* stub_pipline.c */
int		execute_stub_line(const char *line, t_shell *sh);


bool	does_contain_meta(t_token *token);
bool	is_pipe_or_rd(t_token *token);
bool	token_validator(t_token **tokens, t_shell *shell);
size_t	increment_index(char *line);

void	set_type(t_token *token);
ssize_t	count_token_amount(char *line);
size_t	handle_rd(char *line);
size_t	rd_loop(char *line);
size_t	defloop(char *line);

size_t	token_len(char *line, t_token *token);
char	*token_dup(char *line, t_token *token);
t_token	*make_token(char *line, t_shell *shell);
void	add_token(t_token **stack, t_token *new);
t_token	*tokenize(char *line, t_token **stack, t_shell *shell);

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
void	free_sh_tokens(t_token **tokens);
void	free_both(t_shell *shell);

char	*joiner(char *arg, char *env, char *res, char *name);
char	*custom_join(char *arg, char *env, bool got_envs, char *name);
char	*get_sig_val(int lsig);
char	*parse_env(char *str, char *name, t_shell *shell, bool got_envs);
char	*env_parse_handler(char *str, char *name, t_shell *shell, bool got_envs);

size_t	count_args(t_token **tokens);
size_t	count_coms(t_token **tokens);
void	fill_o_dir(t_com *new, t_token *d);
void	fill_in_dir(t_com *new, t_token *d);
void	setup_directors(t_com *new, t_token **tokens);

t_env	*find_env(char *name, t_env **envs);
char	*make_name(char *str);
size_t	get_arg_len(char *arg);
bool	check_if_exists(t_token *token, t_shell *shell);
bool	is_valid_dir(char *path, t_shell *shell);
bool	is_valid_file(t_token *token, t_shell *shell);
size_t	get_len(char *str);
size_t	move_env(char *res, char *env);
void	write_syntax_error(char *msg, t_shell *shell);
void	print_mem_error(char *msg, t_shell *shell);
#endif

