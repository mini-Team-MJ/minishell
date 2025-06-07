/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurtamo <mhurtamo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 16:27:16 by mhurtamo          #+#    #+#             */
/*   Updated: 2025/06/07 16:27:19 by mhurtamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/*
	1. count pipes;
	2. allocate memory 1 + pipecount for commands;
	3. go through tokens;
	4. if pipe make command from tokens that were present before pipe;
	5. go through commands and figure out what to ignore and what to not ignore;
	6. check syntax(might changle slot);
	7. pass commands to exec functions;
*/

t_com **handle_commands(t_token **tokens, size_t n)
{
	t_com	**coms;
	size_t	i;
	
	coms = (t_com **)malloc(n * sizeof(t_com *));
 	if (!coms)
 		return (NULL);
 	
 	 
}

size_t	count_commands(t_tokens **tokens)
{
	size_t	res;
	t_token	*current;
	
	res = 1;
	current = *tokens;
	while (current->next)
	{
		if (current->type == PIPE)
			res++;
		current = current->next;
	}
	return (res);
}

void	setup_commands(token_t **tokens)
{
	size_t	n;
	t_com	**commands;
		
	n = count_commands(tokens);
	commands = make_commands(tokens, n)
}
