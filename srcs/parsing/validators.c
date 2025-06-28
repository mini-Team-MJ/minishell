/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validators.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurtamo <mhurtamo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 17:05:31 by mhurtamo          #+#    #+#             */
/*   Updated: 2025/06/28 17:05:35 by mhurtamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

bool	line_validator(char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (!is_whitespace(line[i]))
		{
			if (line[i] == 39 || line[i] == 34)
			{
				
				if (!q_check_handler(&line[i + 1], line[i]))
				    return(false);
				i += q_count_handler(&line[i + 1], line[i]);
			}		
			else
		    {
				if (is_invalid(line[i]))
				    return (false);
		    }
		}
		i++;
	}
	return (true);
}

