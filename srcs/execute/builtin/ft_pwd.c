/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh3900 <ljh3900@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:39:26 by juhyeonl          #+#    #+#             */
/*   Updated: 2025/06/04 22:49:57 by ljh3900          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	ft_pwd_error(char **argv)
{
	if (argv[1])
	{
		fprintf(stderr, "pwd: too many arguments\n");
		return (1);
	}
	return (0);
}

int	ft_pwd(char **argv)
{
	char	*path;

	if (ft_pwd_error(argv))
		return (1);
	path = getenv("PWD");
	if (!path)
		return (1);
	printf("%s\n", path);
	return (0);
}
