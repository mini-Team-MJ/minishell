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

size_t	count_coms(t_token **tokens)
{
	size_t	res;
	t_token	*current;

	res = 1;
	current = *tokens;
	while (current->next)
	{
		if (current->type == PIPE)
			res++;
	}
	return (res);
}

size_t	count_args(t_token **tokens)
{
	size_t	i;
	t_token *current;
	i = 1;
	
	while (current->next && current->type != pipe)
	{
		i++;
		current = current->next;
	}
	return (i);
}

char	**setup_echo_args(t_token **tokens)
{
	size_t	ac;
	size_t	i;
	t_token *current;
	char	**args;

	ac = count_args(&current);
	i = 0;
	args = (char **)malloc(ac * sizeof(char *));	
	current = *tokens;
	while (i < ac)
	{
		args[i] = ft_strdup(current->str);
		current = current->next;
		i++;
	}
	return (args);
}

t_com	*make_com_echo(t_token **tokens)
{
	t_token	*current;
	t_com	*com;
	
	com = (t_com *)malloc(1 * sizeof(t_com));
	if (!com)
		return (NULL);
	current = *tokens;
	com->type = ECHO;
	if (current->next->type == N)
		com->has_flag = true;
	current = current->next->next;
	com->args = setup_echo_args(&current); 
	if (!com->args)
		return (NULL);
	return (com);
}

void	add_coms(t_com **com_lst, t_com *new)
{
	t_com	*current;

	if (!*com_lst)
		(*com_lst) = new;
	current = *com_lst;
	while (current->next)
		current = current->next;
	current->next = new;
	new->prev = current;

}

tcom *make_coms(t_token **tokens, t_com **commands)
{
	size_t	n;
	
	
}
