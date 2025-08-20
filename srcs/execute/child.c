/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyeonl <juhyeonl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 16:23:15 by juhyeonl          #+#    #+#             */
/*   Updated: 2025/08/20 05:28:16 by juhyeonl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	connect_pipes(int i, int n, int prev[2], int next[2])
{
	if (i > 0 && prev[0] != -1)
	{
		if (dup2(prev[0], STDIN_FILENO) < 0)
		{
			perror("dup2 stdin");
			exit(1);
		}
	}
	if (i < n - 1 && next[1] != -1)
	{
		if (dup2(next[1], STDOUT_FILENO) < 0)
		{
			perror("dup2 stdout");
			exit(1);
		}
	}
	close_pipe_pair(prev);
	close_pipe_pair(next);
}

void	child_exec(t_com *cmd, t_shell *sh, int i, int n,
			int prev[2], int next[2])
{
	int	exit_code;

	set_child_signals();
	connect_pipes(i, n, prev, next);
	if (apply_redirs(cmd, sh) < 0)
		exit(1);
	if (!cmd->args || !cmd->args[0])
		exit(0);
	if (is_builtin_name(cmd->args[0]))
	{
		exit_code = handle_builtin_child(cmd->args, &sh->envs, sh);
		exit(exit_code);
	}
	run_external(cmd->args, sh->envs, sh);
	exit(sh->last_exit);
}