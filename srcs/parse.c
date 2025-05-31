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

enum	Type
{
	WORD,
	CAT,
	PIPE,
	CD,
	EXPORT,
	ENV,
	ECHO,
	UNSET,
	EXIT,
    	N,
	PWD,
	EV,
	RD_O,
	RD_O_APPEND,
	RD_I,
	READ_I,
};

typedef struct	t_token 
{
	size_t	id;
	enum	Type t;
	char	*str;
	int	int_val;
}   t_token ;

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
        token->t = ECHO;
    if (ftstrcmp("cat", token->str))
        token->t = CAT;
    if (ftstrcmp("pwd", token->str))
        token->t = PWD;
    if (ftstrcmp("exit", token->str))
        token->t = EXIT;
    if (ftstrcmp("|", token->str))
        token->t = PIPE;
    if (ftstrcmp("unset", token->str))
        token->t = UNSET;
    if (ftstrcmp("export", token->str))
        token->t = EXPORT;
    if (ftstrcmp("-n", token->str))
        token->t = N;
    if (ftstrcmp("env", token->str))
        token->t = EV;
    if (ftstrcmp(">", token->str))
        token->t = RD_O;
    if (ftstrcmp(">>", token->str))
        token->t = RD_O_APPEND;
    if (ftstrcmp("<", token->str))
        token->t = RD_I;
    if (ftstrcmp("<<", token->str))
        token->t = READ_I;
}


t_token *make_token(char *str)
{
    t_token *token;
    token = (t_token *)malloc(sizeof(t_token *));
    if (!token)
        return (NULL);
    token->t = WORD;
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
    		tc++;
    		while (line[i] && !is_whitespace(line[i]))
    			i++;
    	}
    	else
    		i++;
    }
    return (tokens);
}

int main(int argc, char **argv)
{
    t_token **t;
    size_t  i = 0;
    t = tokenize(">> cat hello");
    printf("%d", t[0]->t);
    return (0);
}
