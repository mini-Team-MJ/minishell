/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurtamo <mhurtamo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:39:00 by mhurtamo          #+#    #+#             */
/*   Updated: 2025/06/10 16:39:06 by mhurtamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

size_t  count_coms(t_token **tokens)
{
    size_t  res;
    t_token *current;
    
    res = 1;
    current = *tokens;
    while(current->next)
    {
        if(current->type == PIPE)
            res++;
        current = current->next;
    }
    return (res);
}

t_com *make_com(t_token **tokens, t_env **envs, int lsig)
{
	size_t  ac;
	t_token *current;
	t_com   *new;
	size_t  i;

	if (!*tokens)
		exit(1);
	ac = count_args(tokens);
	new = (t_com *)malloc(1 * sizeof(t_com));
	new->args = (char **)malloc(ac *sizeof(char *));
	current = *tokens;
	i = 0;
	while (i < ac)
	{
		if (current->sq)
			new->args[i] = custom_dup(current->str);
		else
			new->args[i] = make_arg(current->str, envs, lsig);
		current = current->next;
		i++;
	}
	return (new);
}

void    add_com(t_com *new, t_com **coms)
{
	t_com *current;

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

t_com   *make_coms(t_token **tokens, t_com **coms, t_env **envs, int lsig)
{
	t_token *current;
	t_com   *new;

	current = *tokens;
	new = make_com(tokens, envs, lsig);
	add_com(new, coms);
	while (current->next)
	{
		if (current->type == PIPE)
		{
			new = make_com(&current->next, envs, lsig);
			add_com(new, coms);
		}
		current = current->next;
	}
	return (*coms);
}

t_com   *init_coms(t_token **tokens, t_com **coms, t_env **envs, int lsig)
{
	t_token *current;
	size_t  cc;

	cc = count_coms(tokens);
	current = *tokens;
	*coms = make_coms(tokens, coms, envs, lsig);
	return (*coms);
}

