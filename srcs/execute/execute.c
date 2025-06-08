/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh3900 <ljh3900@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:29:35 by juhyeonl          #+#    #+#             */
/*   Updated: 2025/06/08 17:17:12 by ljh3900          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// DONE : exit, pwd, env, export, unset, cd
// TODO : echo($?)

void	execute(char *line, t_env **env_list)
{
	int		i;
	char	**argv;
	int		exit_code;

	argv = ft_split(line, ' ');
	i = 0;
	exit_code = 0;
	while (line[i] != ' ')
		i++;
	if (ft_strncmp(line, "cd", i) == 0)
		exit_code = ft_cd(argv, env_list);
	if (ft_strncmp(line, "echo", i) == 0)
		exit_code = ft_echo(argv, *env_list);
	if (ft_strncmp(line, "env", i) == 0)
		exit_code = ft_env(argv, *env_list);
	if (ft_strncmp(line, "export", i) == 0)
		exit_code = ft_export(argv, env_list);
	if (ft_strncmp(line, "pwd", i) == 0)
		exit_code = ft_pwd(argv);
	if (ft_strncmp(line, "unset", i) == 0)
		exit_code = ft_unset(argv, env_list);
	if (ft_strncmp(line, "exit", i) == 0)
		ft_exit(argv);
	(void)exit_code;		// TODO: init exit_code function?
	ft_free_2d_array(argv);
}
