/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_validator_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurtamo <mhurtamo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 17:03:36 by mhurtamo          #+#    #+#             */
/*   Updated: 2025/06/28 17:03:41 by mhurtamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

bool	q_check_handler(char *line, char q)
{
    	bool    ret;
	if (q == 34)
		ret = check_dq(line);
	else
	    ret = check_sq(line);
	return (ret);
}

size_t	q_count_handler(char *line, char q)
{
	size_t	ret;
	if(q == 39)
		ret = handle_sq(line);
	else
	    ret = handle_dq(line);
	return (ret);
}
