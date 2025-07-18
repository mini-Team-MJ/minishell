/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_parsing_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurtamo <mhurtamo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:28:57 by mhurtamo          #+#    #+#             */
/*   Updated: 2025/07/10 17:28:59 by mhurtamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

bool	q_check_handler(char *line, char q)
{
	bool	ret;

	if (q == 34)
		ret = check_dq(line);
	else
		ret = check_sq(line);
	return (ret);
}

size_t	handle_sq(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] != 39 && line[i])
		i++;
	i++;
	return (i);
}

size_t	handle_dq(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] != 34 && line[i])
		i++;
	i++;
	return (i);
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
	print_error("error: open quotes aren't supported\n");
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
	print_error("error: open quotes aren't supported\n");
	return (false);
}
