/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyeonl <juhyeonl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 15:20:00 by you               #+#    #+#             */
/*   Updated: 2025/08/20 04:51:44 by juhyeonl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Assumed prototypes declared in minishell.h:
**   int   _name(const char *name);
**   int   run_builtin_parent(t_shell *sh, t_com *cmd);
**   int   run_builtin_parent_with_redirs(t_shell *sh, t_com *cmd);
**   int   exec_pipeline(t_shell *sh, t_com **first, int ncmds);
**
** Data model assumption:
**   t_com is a linked list node for a pipeline:
**     cmd -> next -> next ...
**   Parser stores the head at sh->commands.
*/

/* count how many commands are chained in a pipeline (linked list) */
static int	count_pipeline(const t_com *head)
{
	int	count;

	count = 0;
	while (head)
	{
		++count;
		head = head->next;
	}
	return (count);
}

/* detect if this command has any redirection to apply in its own context */
static int	has_redirs(const t_com *cmd)
{
	if (!cmd)
		return (0);
	if (cmd->infile && cmd->infile[0])
		return (1);
	if (cmd->outfile && cmd->outfile[0])
		return (1);
	if (cmd->append) /* append flag (>>), if the project uses it */
		return (1);
	/* if you have heredoc or other flags, add checks here */
	return (0);
}

/*
** Single command policy:
** - builtin:
**     * without redirs -> run in parent (keeps shell state)
**     * with redirs    -> run in parent with FD backup/restore
** - external: delegate to exec_pipeline with n=1 (unified child/exec path)
**
** exec_pipeline() is expected to set sh->last_exit after wait().
*/
static int	exec_single(t_shell *sh, t_com *cmd)
{
	int		status;
	char	*name;

	if (!cmd || !cmd->args || !cmd->args[0])
	{
		sh->last_exit = 0;
		return (0);
	}
	name = cmd->args[0];
	if (is_builtin_name(name))
	{
		if (has_redirs(cmd))
			status = run_builtin_parent_with_redirs(cmd, sh);
		else
			status = run_builtin_parent(cmd, sh);
		sh->last_exit = status;
		return (status);
	}
	return (exec_pipeline(sh, cmd, 1));
}


/*
** Entry point:
** - sh->commands is the head of a linked list (pipeline)
** - 0 cmd  -> last_exit = 0
** - 1 cmd  -> exec_single()
** - >=2 cmd-> exec_pipeline()
*/
int	execute(t_shell *sh)
{
	int		ncmds;
	t_com	*first;

	if (!sh)
		return (1);
	first = sh->commands;
	ncmds = count_pipeline(first);
	if (ncmds <= 0)
	{
		sh->last_exit = 0;
		return (0);
	}
	if (ncmds == 1)
		return (exec_single(sh, first));
	/* multi-command pipeline */
	return (exec_pipeline(sh, first, ncmds));
}
