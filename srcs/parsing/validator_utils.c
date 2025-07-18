/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurtamo <mhurtamo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:32:53 by mhurtamo          #+#    #+#             */
/*   Updated: 2025/07/10 17:32:59 by mhurtamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

size_t	q_count_handler(char *line, char q)
{
	size_t	ret;

	if (q == 39)
		ret = handle_sq(line);
	else
		ret = handle_dq(line);
	return (ret);
}

bool	check_next(char *str)
{
	size_t	i;

	i = 0;
	while (is_whitespace(str[i]))
		i++;
	if (str[i] == '|' || !str[i])
		return (false);
	if (str[i] == '<' || str[i] == '>')
		return (false);
	return (true);
}

bool	pipe_check(char *str)
{
	size_t	i;

	i = 0;
	if (!str || !str[i])
		return (false);
	if (str[i] != '|')
		return (true);
	while (is_whitespace(str[i]))
		i++;
	if (str[i] == '|' || is_meta(str[i]))
		return (false);
	if (!str[i])
		return (false);
	return (true);
}
