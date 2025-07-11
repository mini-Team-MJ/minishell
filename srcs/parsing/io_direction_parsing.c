/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_direction_parsing.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurtamo <mhurtamo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:38:13 by mhurtamo          #+#    #+#             */
/*   Updated: 2025/07/10 17:38:17 by mhurtamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

bool	handle_i(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '>')
			return (false);
		if (str[i] != '<')
			break ;
		i++;
	}
	if (i > 2 || !str[i])
		return (false);
	return (check_next(&str[i]));
}

bool	handle_o(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '<')
			return (false);
		if (str[i] != '>')
			break ;
		i++;
	}
	if (i > 2 || !str[i])
		return (false);
	return (check_next(&str[i]));
}

bool	validate_directors(char *str)
{
	size_t	i;

	if (*str == '<')
		return (handle_i(str));
	else
		return (handle_o(str));
}

size_t	d_mover(char *line)
{
	size_t	res;
	char	c;

	res = 0;
	if (!line)
		return (res);
	c = line[res];
	while (line[res] == c)
		res++;
	res--;
	return (res);
}
