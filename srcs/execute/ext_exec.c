/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ext_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyeonl <juhyeonl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 17:58:30 by you               #+#    #+#             */
/*   Updated: 2025/08/20 02:34:57 by juhyeonl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_dir(const char *path)
{
	struct stat	st;

	if (stat(path, &st) == -1)
		return (0);
	return (S_ISDIR(st.st_mode));
}

static char	*join_path(const char *dir, const char *cmd)
{
	char	*tmp;
	char	*full;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	full = ft_strjoin(tmp, cmd);
	free(tmp);
	return (full);
}

void	ext_exec_direct_path(char **argv, char **envp, t_shell *sh)
{
	const char	*path = argv[0];

	if (access(path, F_OK) != 0)
	{
		ext_print_no_such_file(path);
		sh->last_exit = 127;
		return ;
	}
	if (is_dir(path))
	{
		ext_print_is_directory(path);
		sh->last_exit = 126;
		return ;
	}
	if (access(path, X_OK) != 0)
	{
		ext_print_perm_denied(path);
		sh->last_exit = 126;
		return ;
	}
	(void)ext_try_exec(path, argv, envp);
	sh->last_exit = ext_errno_to_exit(errno);
}

void	ext_exec_with_path_search(char **argv, t_env *env_list, char **envp, t_shell *sh)
{
	char		*pathvar;
	char		**dirs;
	char		*full;
	int			i;
	int			saw_perm;

	pathvar = ext_get_path_value(env_list);
	if (!pathvar || !*pathvar)
	{
		ext_print_cmd_not_found(argv[0]);
		sh->last_exit = 127;
		return ;
	}
	dirs = ext_split_paths(pathvar);
	if (!dirs)
	{
		sh->last_exit = 1;
		return ;
	}
	i = 0;
	saw_perm = 0;
	while (dirs[i])
	{
		full = join_path(dirs[i], argv[0]);
		if (full)
		{
			if (access(full, F_OK) == 0 && !is_dir(full))
			{
				if (access(full, X_OK) == 0)
				{
					(void)ext_try_exec(full, argv, envp);
					sh->last_exit = ext_errno_to_exit(errno);
					free(full);
					ft_free_2d_array(dirs);
					return ;
				}
				saw_perm = 1;
			}
			free(full);
		}
		i++;
	}
	ft_free_2d_array(dirs);
	if (saw_perm)
	{
		ext_print_perm_denied(argv[0]);
		sh->last_exit = 126;
	}
	else
	{
		ext_print_cmd_not_found(argv[0]);
		sh->last_exit = 127;
	}
}
