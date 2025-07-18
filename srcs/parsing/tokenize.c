/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurtamo <mhurtamo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:19:56 by mhurtamo          #+#    #+#             */
/*   Updated: 2025/07/10 17:19:59 by mhurtamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*token_dup(char *line, t_token *token)
{
	size_t	i;
	char	*res;
	size_t	l;

	l = token_len(line, token);
	res = (char *)malloc((l + 1) * sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (i < l)
	{
		res[i] = line[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

t_token	*make_token(char *line)
{
	t_token	*token;

	token = (t_token *)malloc(1 * sizeof(t_token));
	if (!token)
		return (NULL);
	token->sq = false;
	token->dq = false;
	token->str = token_dup(line, token);
	if (!token->str)
	{
		free(token);
		return (NULL);
	}
	token->next = NULL;
	token->prev = NULL;
	token->type = WORD;
	set_type(token);
	return (token);
}

void	add_token(t_token **stack, t_token *new)
{
	t_token	*current;

	if (!*stack)
	{
		*stack = new;
		return ;
	}
	current = *stack;
	while (current->next)
	{
		current = current->next;
	}
	current->next = new;
	new->prev = current;
}

t_token	*tokenize(char *line, t_token **stack)
{
	t_token	*new;
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (!is_whitespace(line[i]))
		{
			new = make_token(&line[i]);
			if (!new)
			{
				free_tokens(stack);
				return (NULL);
			}
			add_token(stack, new);
			if (is_rd(line[i]))
				i += rd_loop(&line[i]);
			else
				i += default_loop(&line[i]);
		}
		else
			i++;
	}
	return (*stack);
}
