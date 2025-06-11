/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh3900 <ljh3900@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 12:16:59 by ljh3900           #+#    #+#             */
/*   Updated: 2025/06/11 19:11:39 by ljh3900          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

bool	is_builtin(const char *cmd)
{
	return (ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0
		|| ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "exit") == 0);
}

int	handle_builtin(char **argv, t_env **env_list, t_shell *sh)
{
	int			exit_code;
	const char	*cmd;

	exit_code = 0;
	cmd = argv[0];
	if (ft_strcmp(cmd, "cd") == 0)
		exit_code = ft_cd(argv, env_list);
	else if (ft_strcmp(cmd, "echo") == 0)
		exit_code = ft_echo(argv, *env_list, sh->last_exit);
	else if (ft_strcmp(cmd, "env") == 0)
		exit_code = ft_env(argv, *env_list);
	else if (ft_strcmp(cmd, "export") == 0)
		exit_code = ft_export(argv, env_list);
	else if (ft_strcmp(cmd, "unset") == 0)
		exit_code = ft_unset(argv, env_list);
	else if (ft_strcmp(cmd, "pwd") == 0)
		exit_code = ft_pwd(argv);
	else if (ft_strcmp(cmd, "exit") == 0)
		ft_exit(argv);
	return (exit_code);
}
