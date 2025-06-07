/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyeonl <juhyeonl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 23:14:33 by ljh3900           #+#    #+#             */
/*   Updated: 2025/05/28 14:28:08 by juhyeonl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minishell.h"

int	is_whitespace(char c)
{
	return((c == ' ' || c == 9));
}

int	handle_quotes(char c)
{
	if (c == '/')
		return (0);
	if (c == '"' || c == 39)
		return (0);
	return (1);
}

bool set_quote_status(char *str, size_t i)
{
	if (str[i] == '"' && str[0] == '"')
		return (true);
	if (str[i] == 39 && str[0] == 39)
		return (true);
	return (false);
}

char    *extract_param(char *str)
{
	size_t  i;
	char    *res;
	bool	is_quotes;

	i = 0;
	while (!is_whitespace(str[i]) && str[i])
		i++;
	is_quotes = set_quote_status(str, i);
	res = (char *)malloc((i + 1) * sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (!is_whitespace(str[i]) && str[i])
	{
		if (!is_quotes && str[i] == ';')
			i++;
		else if (!is_quotes && !handle_quotes(str[i]))
		{
			free(res);
			return(NULL);
		}
		else
		{	res[i] = str[i];
			i++;
		}
	}
	res[i] = '\0';
	return (res);
}

int ftstrcmp(char *s1, char *s2)
{
	size_t  i;
	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

void set_type(t_token *token)
{
	if (ftstrcmp("echo", token->str))
		token->type = ECHO;
	if (ftstrcmp("cat", token->str))
		token->type = CAT;
	if (ftstrcmp("pwd", token->str))
		token->type = PWD;
	if (ftstrcmp("exit", token->str))
		token->type = EXIT;
	if (ftstrcmp("|", token->str))
		token->type = PIPE;
	if (ftstrcmp("unset", token->str))
		token->type = UNSET;
	if (ftstrcmp("export", token->str))
		token->type = EXPORT;
	if (ftstrcmp("-n", token->str))
		token->type = N;
	if (ftstrcmp("env", token->str))
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

t_token *make_token(char *st)
{
	t_token *token;
	char *c;
	int    i = 0;
	token = (t_token *)calloc(1, sizeof(t_token *));
	if (!token)
		return (NULL);
	token->type = WORD;
	token->str = st;
	token->next = NULL;
	token->prev = NULL;
	set_type(token);
	return (token);
}

void	make_list(t_token **tokens, size_t tc)
{
	size_t	i;

	i = 0;
	if (tc == 1)
		return ;
	while (i)
	{
		tokens[i]->next = tokens[i + 1];
		i++;
	}
}

ssize_t	count_token_amount(char *line)
{
	size_t	i;
	ssize_t	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (!is_whitespace(line[i]))
		{
			count++;
			while (line[i] != '\0' && !is_whitespace(line[i]))
				i++;
		}
		else
			i++;
	}
	return (count);
}

void	delete_tokens(t_token **tokens, size_t count)
{
	while (count > 0)
	{
		free(tokens[count]->str);
		free(tokens[count]);
		count--;
	}
	free(tokens);

}

char    **init_params(char *line, size_t cap)
{
	size_t  i;
	size_t  p_count;
	char    **params;

	p_count = 0;
	i = 0;
	params = (char **)malloc((i + 1) * sizeof(char *));
	while (line[i])
	{
		if (!is_whitespace(line[i]))
		{
			params[p_count] = extract_param(&line[i]);
			p_count++;
			while (!is_whitespace(line[i]) && line[i])
				i++;

		}
		else
			i++;
	}
	params[cap] = NULL;
	return (params);

}
void    add_token(t_token *new, t_token **stack)
{
	t_token *last;
	t_token *current;

	if (!*stack)
	{
		*stack = new;
		return;
	}
	current = *stack;
    while (current->next)
		current = current->next;
    current->next = new;
}

void    link(t_token **stack)
{
    t_token *current;
    t_token *n;

    current = *stack;    
    if (!current->next)
        return ;
    while (current->next)
    {
            n = current->next;
            n->prev = current;
            current = current->next;
    }
}

void    init_token_list(t_token **tokens, char **params, size_t cap)
{
	t_token *token;
	size_t  i;
	i = 0;

	while (i < cap)
	{
		token = make_token(params[i]);
		add_token(token, tokens);
		i++;
	}
	link(tokens);
}

t_token    *tokenize(char *line, t_token *tokens)
{
	size_t  cap;
	char    **params;
	cap = count_token_amount(line);

	params = init_params(line, cap);
	int i = 0;
	init_token_list(&tokens, params, cap);
	return (tokens);
}

int main()
{
	t_token *t;
    	t = NULL;
	t = tokenize("echo hello asd", t);
    printf("%s", t->next->next->prev->str);
}
