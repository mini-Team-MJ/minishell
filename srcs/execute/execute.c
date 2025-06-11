/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: ljh3900 <ljh3900@student.42.fr>            +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/05/28 16:29:35 by juhyeonl          #+#    #+#             */
// /*   Updated: 2025/06/11 08:31:22 by ljh3900          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../../includes/minishell.h"

// // DONE : exit, pwd, env, export, unset, cd
// // TODO : echo($?)

// void	init_external()
// {
// 	return ;
// }

// static int	external_command(char **argv, t_env **env_list)
// {
// 	int	exit_code;

// 	(void) argv;
// 	(void) env_list;
// 	init_external();
// 	exit_code = 0;
// 	return (exit_code);
// }

// void	execute(char *line, t_env **env_list)
// {
// 	char	**argv;
// 	int		exit_code;

// 	argv = ft_split(line, ' ');
// 	if (!argv || !argv[0])
// 		return (ft_free_2d_array(argv));
// 	exit_code = 0;
// 	if (is_builtin(argv[0]))
// 		exit_code = handle_builtin(argv, env_list);
// 	else
// 		exit_code = external_command(argv, env_list);
// 	(void)exit_code;		// TODO: init exit_code function?
// 	ft_free_2d_array(argv);
// }


#include "../../includes/minishell.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

static t_com *create_stub_cmds(char *line)
{
	t_com *node = ft_calloc(1, sizeof(t_com));
	if (!node)
		return NULL;

	node->pipe_fd[0] = node->pipe_fd[1] = -1;
	node->args = ft_split(line, ' ');
	if (!node->args || !node->args[0])
		return (ft_free_2d_array(node->args), free(node), NULL);

	node->type = WORD;
	return node;
}
static int run_external(char **argv)
{
	int status;
	int exit_code;
	pid_t pid = fork();
	if (pid < 0)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		execvp(argv[0], argv);
		perror("execvp");
		_exit(127);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		exit_code = 128 + WTERMSIG(status);
	else
		exit_code = 1;
	return exit_code;
}

static int execute_single(t_com *cmd, t_env **env, t_shell *sh)
{
	if (is_builtin(cmd->args[0]))
		return handle_builtin(cmd->args, env, sh);
	return run_external(cmd->args);
}

void    execute(char *line, t_shell *sh)
{
	if (ft_strchr(line, '|') || ft_strchr(line, '<') || ft_strchr(line, '>'))
	{
		execute_stub_line(line, sh);
		return ;
	}
	t_com *cmd = create_stub_cmds(line);
	if (!cmd)
		return ;
	int exit_code = execute_single(cmd, &sh->envs, sh);
	sh->last_exit = exit_code;
	ft_free_2d_array(cmd->args);
	free(cmd);
}