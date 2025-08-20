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

#include "../../includes/minishell.h"

size_t	token_len(char *line, t_token *token)
{
	size_t	i;

	i = 0;
	if (line[i] == '|')
		return (1);
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
		if (line[i] == '$')
			return (i+= handle_dollar(&line[i + 1]));
		if (is_rd(line[i]))
			break ;
		i++;
	}
	return (i);
}

void	sq_dub(char *line, char *res, size_t l)
{
	size_t	i;
	size_t	j;

	if (!line)
		return ;
	i = 0;
	j = 0;
	while(i < l)
	{
		if (line[i] == 39)
			i++;
		else
		{
			res[j] = line[i];
			i++;
			j++;
		}
	}
	res[j] = '\0';
}


void	dq_dub(char *line, char *res, size_t l)
{
	size_t	i;
	size_t	j;

	if (!line)
		return ;
	i = 0;
	j = 0;
	while(i < l)
	{
		if (line[i] == 34)
			i++;
		else
		{
			res[j] = line[i];
			i++;
			j++;
		}
	}
	res[j] = '\0';
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
	if (token->sq)
	{
		sq_dub(line, res, l);
		return (res);
	}
	if (token->dq)
	{
		dq_dub(line, res, l);
		return (res);
	}
	while (i < l)
	{
		res[i] = line[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

t_token	*make_token(char *line, t_shell *shell)
{
	t_token	*token;

	token = (t_token *)malloc(1 * sizeof(t_token));
	if (!token)
	{
		print_mem_error("memory allocation failed", shell);
		return (NULL);
	}
	init_token_vals(token);
	token->str = token_dup(line, token);
	if (!token->str)
	{
		print_mem_error("memory allocation failed", shell);
		free(token);
		return (NULL);
	}
	token->type = WORD;
	set_type(token);
	if (token->type == EV)
		token->does_exist = does_env_exist(token, &shell->envs);
	return (token);
}

void	add_token(t_token **stack, t_token *new)
{
	t_token	*current;

	if (new->type == EV && !new->does_exist)
	{
		free(new);
		return ;
	}
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

t_token	*tokenize(char *line, t_token **stack, t_shell *shell)
{
	t_token	*new;
	size_t	i;

	if (!line_validator(line))
	{
		printf("syntax_error");
		return (NULL);
	}
	i = -1;
	while (line[++i])
	{
		if (!is_whitespace(line[i]))
		{
			new = make_token(&line[i], shell);
			if (!new)
			{
				free_sh_tokens(stack);
				return (NULL);
			}
			add_token(stack, new);
			i += increment_index(&line[i]);
		}
	}
	if (!token_validator(stack, shell))
		free_sh_tokens(stack);
	return (*stack);
}
