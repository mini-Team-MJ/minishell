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

int	is_whitespace(char c)
{
	return((c == ' ' || c == 9));
}

char *custom_dup(char *line)
{
    size_t  i;
    char    *res;

    i = 0;
    while (!is_whitespace(line[i]) && line[i])
        i++;
    res = (char *)malloc((i + 1) * sizeof(char));
    i = 0;
    while(!is_whitespace(line[i]) && line[i])
    {
        res[i] = line[i];
        i++;
    }
    res[i] = '\0';
    return (res);
}

t_token *make_token(char *line)
{
    t_token *token;
    
    token = (t_token *)malloc(1 * sizeof(t_token));
    token->str = custom_dup(line);
    token->next = NULL;
    token->prev = NULL;
    token->type = WORD;
    set_type(token);
    return (token);
}
void    add_token(t_token **stack, t_token *new)
{
    t_token *current;

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

t_token *tokenize(char *line, t_token **stack)
{
    t_token *new;
    size_t  i;
    
    i = 0;
    while (line[i])
    {
        if (!is_whitespace(line[i]))
        {
            new = make_token(&line[i]);
            add_token(stack, new);
            while (!is_whitespace(line[i]) && line[i])
                i++;
        }
        else
            i++;
    }
    return (*stack);
}

int main()
{
	t_token *t;
    t = NULL;
	t = tokenize("echo hello asd", t);
    printf("%s", t->next->next->prev->str);
}

/*
char    **tokenize(char *line)
{
    size_t  cap;
    size_t  cnt;
    char    **tokens;
    cap = INITIAL_CAP;
    cnt = 0;
    if (!line || !*line || line[0] == '\0')
        return NULL;
    tokens = (char **)malloc(cap * sizeof(char *));
    if (!tokens)
        return NULL;
    while (line[0])
    {
        
    }
    return NULL;
}
*/

