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

#include "parse.h"

bool	is_valid_dir(char *path)
{
	DIR *dir;

	dir = opendir(path);
	if (!dir)
	{
		printf("invalid folder");
		return (false);
	}
	closedir(dir);
	return (true);
}

bool	is_valid_file(t_token *token)
{
	int	fd;

	fd = open(token->str, O_RDONLY);
	if (fd == -1)
	{
		printf("invalid file");
		return (false);
	}
	close(fd);
	return (true);
}
