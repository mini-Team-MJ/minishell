/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurtamo <mhurtamo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:25:28 by mhurtamo          #+#    #+#             */
/*   Updated: 2025/07/10 17:25:32 by mhurtamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	free_args(char **args)
{
	size_t	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void	free_coms(t_com **coms)
{
	t_com	*current;
	t_com	*temp;

	if (!coms)
		return ;
	current = *coms;
	while (current->next)
	{
		temp = current;
		current = current->next;
		free_args(temp->args);
		free(temp->path);
		temp->prev = NULL;
		free(temp);
		current = current->next;
	}
	free_args(current->args);
	free(current->path);
	current->prev = NULL;
	free(current);
	*coms = NULL;
}

void	free_tokens(t_token **tokens)
{
	t_token	*current;
	t_token	*temp;

	if (!tokens)
		return ;
	current = *tokens;
	while (current->next)
	{
		temp = current;
		current = current->next;
		free(temp->str);
		temp->prev = NULL;
		free(temp);
	}
	free(current->str);
	current->prev = NULL;
	free(current);
	*tokens = NULL;
}

void	free_both(t_shell *shell)
{
	free_tokens(&shell->tokens);
	free_coms(&shell->commands);
}
