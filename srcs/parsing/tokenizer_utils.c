/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurtamo <mhurtamo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 16:37:11 by mhurtamo          #+#    #+#             */
/*   Updated: 2025/06/28 16:37:19 by mhurtamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void set_type(t_token *token)
{
	if (ftstrcmp("echo", token->str))
		token->type = COMMAND;
	if (ftstrcmp("cat", token->str))
		token->type = COMMAND;
	if (ftstrcmp("pwd", token->str))
		token->type = COMMAND;
	if (ftstrcmp("exit", token->str))
		token->type = COMMAND;
	if (ftstrcmp("|", token->str))
		token->type = PIPE;
	if (ftstrcmp("unset", token->str))
		token->type = COMMAND;
	if (ftstrcmp("export", token->str))
		token->type = COMMAND;
	if (ftstrcmp("-n", token->str))
		token->type = N;
	if (token->str[0] == '$')
		token->type = EV;
	if (ftstrcmp(">", token->str))
		token->type = RD_O;
	if (ftstrcmp(">>", token->str))
		token->type = RD_O_APPEND;
	if (ftstrcmp("<", token->str))
		token->type = RD_I;
	if (ftstrcmp("<<", token->str))
		token->type = READ_I;
}

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
				i++;
			}
		}
		else
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

size_t	token_len(char *line, t_token *token)
{
	size_t	i;

	i = 0;
	if(is_rd(line[i]))
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
			break; 
		i++;
	}
	return (i);
}


char *token_dup(char *line, t_token * token)
{
    size_t  i;
    char    *res;
    size_t	l;

    l = token_len(line, token);
    res = (char *)malloc((l + 1) * sizeof(char));
    i = 0;
    while (i < l)
    {
        res[i] = line[i];
        i++;
    }
    res[i] = '\0';
    return (res);
}

