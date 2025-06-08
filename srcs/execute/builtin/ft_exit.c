/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyeonl <juhyeonl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 22:44:27 by ljh3900           #+#    #+#             */
/*   Updated: 2025/06/07 16:19:18 by juhyeonl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_str_isalpha(char *str)
{
	int	i;

	if (*str == '\0' || str == NULL)
		return (FALSE);
	i = 0;
	while (str[i])
	{
		if (('a' <= str[i] && str[i] <= 'z')
			|| ('A' <= str[i] && str[i] <= 'Z'))
			return (TRUE);
	}
	return (FALSE);
}

int exit_error(char **argv)
{
	int cnt;
	
	cnt = 0;
	while (argv[cnt])
		cnt++;
	if (cnt == 1)
		return (0);
	if (2 < cnt)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (1);
	}
	else if (ft_str_isalpha(argv[1]))
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd("numeric argument required\n", 2);
		return (2);
	}
	else
	{
		ft_putstr_fd("exit: unknown error\n", 2);
		return (1);
	}
	return (0);
}

void	ft_exit(char **argv)
{
	int	exit_code;

	exit_code = 0;
	printf("exit\n");
	exit_code = exit_error(argv);
	if (exit_code == 1)
		return ;
	exit(exit_code);
}
