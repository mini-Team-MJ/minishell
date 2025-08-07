/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurtamo <mhurtamo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 20:37:54 by mhurtamo          #+#    #+#             */
/*   Updated: 2025/08/07 20:37:58 by mhurtamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

size_t	token_len(char *line, t_token *token)
{
	size_t	i;

	i = 0;
	if (is_rd(line[i]))
	{
		i = handle_rd(line);
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

	if (!line_validator(line))
		return (NULL);
	i = -1;
	while (line[++i])
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
			i += increment_index(&line[i]);
		}
	}
	if (!token_validator(stack))
		free_tokens(stack);
	return (*stack);
}
