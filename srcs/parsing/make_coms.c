/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_coms.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurtamo <mhurtamo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 18:11:27 by mhurtamo          #+#    #+#             */
/*   Updated: 2025/07/10 18:11:29 by mhurtamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_com	*make_com(t_token **tokens, t_shell *shell)
{
	size_t	ac;
	t_token	*current;
	t_com	*new;
	size_t	i;

	if (!*tokens)
		exit(1);
	new = (t_com *)malloc(1 * sizeof(t_com));
	if (!new)
		return (NULL);
	current = *tokens;
	new->type = current->type;
	new->args = make_args(tokens, shell);
	return (new);
}

void	add_com(t_com *new, t_com **coms)
{
	t_com	*current;

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

void	expand_env_com_types(t_com **coms)
{
	t_com	*current;

	if (!coms)
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

	cc = count_coms(tokens);
	*coms = make_coms(tokens, coms, shell);
	expand_env_com_types(coms);
	return (*coms);
}
