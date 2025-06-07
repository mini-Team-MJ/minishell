/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurtamo <mhurtamo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 18:04:08 by mhurtamo          #+#    #+#             */
/*   Updated: 2025/06/05 18:04:15 by mhurtamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

bool	check_if_rd(t_token *token)
{
	if (!token)
		return (false);
	if (token->type == RD_O || RD_O_APPEND)
	{
		if (!current->next)
			//handle_error
		current->next->type = FILENAME;
		return (true);
	}
	return (false);
}	

void	handle_pwd(t_token **tokens)
{
	t_token *current;
	
	current = *tokens;
	if (current->next)
		//handle_error
	else
		//exec pwd
}

void	handle_exit(t_token **tokens)
{
	//handle_exit
}

void	handle_cat(t_token **tokens)
{
	t_token	*current;

	while (current->next)
	{
		//check_if_file_exists
		//read_file
		current = current->next
	}
}

void	handle_echo(t_token **tokens)
{
	t_token *current;
	
	current = (*tokens)->next;
	while (current->next)
	{
		if (current->type = PIPE)
		{
			if (current->next)
				parser(&current->next);
		}
		if (check_if_rd(current) || (current->type == FILENAME && check_if_rd(current->prev)))
			current = current->next;
		else
		{
			current->type = WORD;
			current = current->next;
		}		
	}
	//format args to exec and pass them to it
}


void	parser(t_token **tokens)
{
	if ((*tokens)->type == ECHO)
		handle_echo(tokens->next, com);
}

