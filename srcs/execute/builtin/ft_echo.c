/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyeonl <juhyeonl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 08:21:02 by ljh3900           #+#    #+#             */
/*   Updated: 2025/08/21 01:07:44 by juhyeonl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	is_n_option(const char *s)
{
	int	i = 1;

	if (s[0] != '-' || s[1] != 'n')
		return (0);
	while (s[i] == 'n')
		i++;
	return (s[i] == '\0');
}

int ft_echo(char **argv)
{
	int	i;
	int	print_nl;

	i = 1;
	print_nl = 1;
	while (argv[i] && is_n_option(argv[i]))
	{
		print_nl = 0;
		i++;
	}
	while (argv[i])
	{
		ft_putstr_fd(argv[i], 1);
		if (argv[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (print_nl)
		ft_putchar_fd('\n', 1);
	return (0);
}
