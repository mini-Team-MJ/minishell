/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurtamo <mhurtamo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:53:40 by mhurtamo          #+#    #+#             */
/*   Updated: 2025/07/10 17:53:42 by mhurtamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

size_t	custom_len(char *line)
{
	size_t	i;

	if (!line)
		return (0);
	i = 0;
	while (line[i] && !is_whitespace(line[i]))
	{
		if (line[i] == 39)
			i += handle_sq(&line[i + 1]);
		if (line[i] == 34)
			i += handle_dq(&line[i + 1]);
		i++;
	}
	return (i);
}

char	*custom_dup(char *line)
{
	size_t	i;
	char	*res;
	size_t	l;

	if (!line)
		return (0);
	l = custom_len(line);
	res = (char *)malloc((l + 1) * sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (i <= l)
	{
		res[i] = line[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

size_t	count_args(t_token **tokens)
{
	size_t	i;
	t_token	*current;

	current = *tokens;
	i = 1;
	while (current->next && current->next->type != PIPE)
	{
		i++;
		current = current->next;
	}
	return (i);
}

size_t	get_arg_len(char *arg)
{
	size_t	l;
	size_t	i;
	bool	detected;

	l = 0;
	i = 0;
	detected = false;
	if (!arg)
		return (l);
	while (arg[i])
	{
		if (arg[i] == '$' && !detected)
		{
			while (arg[i] && !is_whitespace(arg[i]))
				i++;
			detected = true;
		}
		else
		{
			l++;
			i++;
		}
	}
	return (l);
}

size_t	arg_mover(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i] && !is_whitespace(str[i]))
		i++;
	return (i);
}
