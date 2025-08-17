/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_and_file_validators.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurtamo <mhurtamo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 18:20:36 by mhurtamo          #+#    #+#             */
/*   Updated: 2025/08/08 18:20:41 by mhurtamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	handle_dollar(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] && !is_separator(line[i]))
		i++;
	i++;
	return (i);
}

bool	is_valid_dir(char *path)
{
	DIR	*dir;

	dir = opendir(path);
	if (!dir)
	{
		return (false);
	}
	closedir(dir);
	return (true);
}

bool	is_valid_file(char *str)
{
	int	fd;

	fd = open(str, O_RDONLY);
	if (fd == -1)
	{
		return (false);
	}
	close(fd);
	return (true);
}
