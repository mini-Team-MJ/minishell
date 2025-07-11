/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validators.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurtamo <mhurtamo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:41:04 by mhurtamo          #+#    #+#             */
/*   Updated: 2025/07/10 17:41:08 by mhurtamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

bool	line_validator(char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 39 || line[i] == 34)
		{
			if (!q_check_handler(&line[i + 1], line[i]))
				return (false);
			i += q_count_handler(&line[i + 1], line[i]);
		}
		else if (line[i] == '>' || line[i] == '<')
		{
			if (!validate_directors(&line[i]))
				return (false);
			i += d_mover(&line[i]);
		}
		if (is_meta(line[i]) || !pipe_check(&line[i]))
			return (false);
		i++;
	}
	return (true);
}
