/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_coms.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyeonl <juhyeonl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 19:30:08 by mhurtamo          #+#    #+#             */
/*   Updated: 2025/08/20 23:39:43 by juhyeonl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_com	*make_com(t_token **tokens, t_shell *shell)
{
	t_com	*new;

	if (!*tokens)
		exit(1);
	new = (t_com *)malloc(1 * sizeof(t_com));
	if (!new)
	{
		print_mem_error("memory allocation error", shell);
		return (NULL);
	}
<<<<<<< HEAD
	current = *tokens;
=======
	new->next = NULL;
	new->prev = NULL;
	new->infile = NULL;
	new->outfile = NULL;
>>>>>>> 6982ba3cdbb775d63e5dc65197bbee0cddd40f2a
	new->args = make_args(tokens, shell);
	setup_directors(new, tokens);
	return (new);
}

void	add_com(t_com *new, t_com **coms)
{
	t_com	*current;

	if (!new->args)
	{
		free(new);
		return ;
	}
	set_com_type(new->args[0], new);
	current = *coms;
	if (!*coms)
	{
		*coms = new;
		return ;
	}
	while (current->next)
		current = current->next;
	current->next = new;
	new->prev = current;
}

t_com	*make_coms(t_token **tokens, t_com **coms, t_shell *shell)
{
	t_token	*current;
	t_com	*new;

	current = *tokens;
	new = make_com(tokens, shell);
	if (!new)
		return (NULL);
	add_com(new, coms);
	while (current->next)
	{
		if (current->type == PIPE)
		{
			new = make_com(&current->next, shell);
			if (!new)
			{
				free_coms(coms);
				return (NULL);
			}
			add_com(new, coms);
		}
		current = current->next;
	}
	return (*coms);
}

bool	path_checker(t_com **coms, t_shell *shell)
{
	t_com	*current;
	if (!*coms)
		return (true);
	current = *coms;
	while (current->next)
	{
		if (current->type == PATH && current->args[0])
			return (check_if_exists(current->args[0], shell, current));
		if (current->type == CD && current->args[1])
			return (check_if_exists(current->args[1], shell, current));
		current = current->next;
	}
	if (current->type == PATH && current->args[0])
		return (check_if_exists(current->args[0], shell, current));
	if (current->type == CD && current->args[1])
		return (check_if_exists(current->args[1], shell, current));
	return (true);
}

void	expand_env_com_types(t_com **coms)
{
	t_com	*current;

	if (!*coms)
		return ;
	current = *coms;
	while (current->next)
	{
		if (current->type == EV)
			set_com_type(current->args[0], current);
		current = current->next;
	}
	if (current->type == EV)
		set_com_type(current->args[0], current);
}

t_com	*init_coms(t_token **tokens, t_com **coms, t_shell *shell)
{
	size_t	cc;
	if (!tokens)
		return (NULL);
	cc = count_coms(tokens);
	*coms = make_coms(tokens, coms, shell);
	if (!path_checker(coms, shell))
	{
		free_coms(coms);
		return (NULL);
	}
	return (*coms);
}
