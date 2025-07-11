/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurtamo <mhurtamo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:26:14 by mhurtamo          #+#    #+#             */
/*   Updated: 2025/07/10 17:26:17 by mhurtamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

bool	is_rd(char c)
{
	return ((c == '>' || c == '<'));
}

int	is_whitespace(char c)
{
	return ((c == ' ' || c == 9));
}

bool	ftstrcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (false);
		i++;
	}
	return (true);
}

bool	ftstrncmp(char *s1, char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((i < n) && (s1[i] && s2[i]))
	{
		if (s1[i] != s2[i])
			return (false);
		i++;
	}
	return (true);
}
