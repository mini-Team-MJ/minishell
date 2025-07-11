/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurtamo <mhurtamo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:30:11 by mhurtamo          #+#    #+#             */
/*   Updated: 2025/07/10 17:30:13 by mhurtamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

ssize_t	count_token_amount(char *line)
{
	size_t	i;
	ssize_t	count;

	count = 0;
	i = 0;
	while (line[i])
	{
		if (!is_whitespace(line[i]))
		{
			count++;
			while (!is_whitespace(line[i]) && line[i])
			{
				if (line[i] == 39)
					i += handle_sq(&line[i + 1]);
				else if (line[i] == 34)
					i += handle_dq(&line[i + 1]);
				if (is_rd(line[i]) && !is_whitespace(line[i - 1]))
					count++;
			    if (!is_rd(line[i]) && is_rd(line[i - 1]))
					count++;
			}
		}
		i++;
	}
	return (count);
}

size_t	handle_rd(char *line)
{
	size_t	i;
	
	i = 0;
	while (is_rd(line[i]))
		i++;
	return (i);
}

size_t  rd_loop(char *line)
{
    size_t  i;
    
    i = 0;
    while (is_rd(line[i]))
        i++;
    return (i);
}


size_t	token_len(char *line, t_token *token)
{
	size_t	i;

	i = 0;
	if (is_rd(line[i]))
	{	i = handle_rd(line);
		return (i);
	}
	while (!is_whitespace(line[i]) && line[i])
	{
		if (line[i] == 39)
		{
			i += handle_sq(&line[i + 1]);
			token->sq = true;
		}
		if (line[i] == 34)
		{
			i += handle_dq(&line[i + 1]);
			token->dq = true;
		}
		if (is_rd(line[i]))
			break ; 
		i++;
	}
	return (i);
}

size_t default_loop(char *line)
{
	size_t  i;

	i = 0;
	while (!is_whitespace(line[i]) && line[i])
	{
		if (line[i] == 39)
			i += handle_sq(&line[i + 1]);
		if (line[i] == 34)
			i += handle_dq(&line[i + 1]);
		if (is_rd(line[i]))
		    break ;
		i++;
	}
	return (i);
}

