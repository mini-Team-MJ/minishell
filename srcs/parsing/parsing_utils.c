/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurtamo <mhurtamo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 16:45:30 by mhurtamo          #+#    #+#             */
/*   Updated: 2025/06/28 16:45:34 by mhurtamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	is_whitespace(char c)
{
	return((c == ' ' || c == 9));
}

bool	is_rd(char c)
{
	return ((c == '>' || c == '<'));
}

bool	is_meta(char c)
{
	if (c == 92)
		return (true);
	if (c == ';')
		return (true);
	if (c == '&')
		return (true);
	return (false);
}

bool	check_sq(char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 39)
		   return (true);
		i++;
	}
	return (false);
}

bool	check_dq(char *line)
{
	size_t	i;
	
	i = 0;
	while (line[i])
	{
		if (line[i] == 34)
			return (true);
		i++;	
	}
	return (false);
}

