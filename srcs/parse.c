/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh3900 <ljh3900@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 23:14:33 by ljh3900           #+#    #+#             */
/*   Updated: 2025/06/05 00:09:10 by ljh3900          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_whitespace(char c)
{
	return((c == ' ' || c == 9));
}

int	handle_quotes(char c)
{
	if (c == '\')
		return (0);
	if (c == '"' || c == 39)
		return (0);
	return (1);
}

bool set_quote_stats(char *str, size_t i)
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
    while (!is_whitespace(str[i]))
        i++;
    is_quotes = set_quote_status(str, i);
    res = (char *)malloc((i + 1) * sizeof(char));
    if (!res)
        return (NULL);
    i = 0;
    while (!is_whitespace(str[i]))
    {
    	if (!is_quotes && str[i] == ';')
    		i++;
    	else if (!is_quotes && !handle_quotes(str[i])
    	{
    		free(res)
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

t_token *make_token(char *str)
{
    t_token *token;
    token = (t_token *)malloc(sizeof(t_token *));
    if (!token)
        return (NULL);
    token->type = WORD;
    token->str = extract_param(str);
    if (!token->str)
        return (NULL);
    set_type(token);
    return (token);
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
	while(count > 0)
	{
		free(tokens[count]->str);
		free(tokens[count]);
		count--;
	}
	free(tokens);

}
t_token    **tokenize(char *line)
{
    size_t  cap;
    size_t  tc;
    size_t	i;
    t_token   **tokens;
    cap = count_token_amount(line);
    tc = 0;
    i = 0;

    if (!line || !*line || line[0] == '\0')
        return NULL;
    tokens = (t_token **)malloc(cap * sizeof(t_token *));
    if (!tokens)
        return NULL;
    while (line[i])
    {
    	if (!is_whitespace(line[i]))
    	{
    		tokens[tc] = make_token(&line[i]);
    		if(!tokens[tc])
    		{
    			delete_tokens(tokens, tc);
    			return (NULL);
    		}
    		tc++;
    		while (line[i] && !is_whitespace(line[i]))
    			i++;
    	}
    	else
    		i++;
    }
    return (tokens);
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

