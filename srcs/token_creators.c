/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_creators.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurtamo <mhurtamo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:05:04 by mhurtamo          #+#    #+#             */
/*   Updated: 2025/05/28 16:05:35 by mhurtamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "minishell.h"

char *make_word(char *line)
{
	size_t	i;
	char	 *word;
	
	i = 0;
	while (line[i] != '\0' || !is_whitespace(line[i]))
		i++;
	word = (char *)malloc((i + 1) * sizeof(char));
	if (!word)
		return (NULL);
	i = 0;
	while (line[i] != '\0' || !is_whitespace(line[i]))
	{
		word[i] = line[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}


t_token	make_word_token(char *line)
{
	size_t	i;
	char	*word;
		
	i = 0;
	word = make_word(line);
	if (!word)
		return (NULL);
	token->type = WORD;
	token->str = word;
	return (token);
}
