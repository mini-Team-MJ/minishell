/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurtamo <mhurtamo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 20:36:34 by mhurtamo          #+#    #+#             */
/*   Updated: 2025/08/07 20:36:36 by mhurtamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
t_env	*find_env(char *name, t_env **envs)
{
	t_env	*current;

	current = *envs;
	if (!current)
		return (false);
	while (current->next)
	{
		if (ftstrcmp(name, current->name))
			return (current);
		current = current->next;
	}
	if (ftstrcmp(name, current->name))
		return (current);
	return (NULL);
}

char	*make_name(char *str)
{
	size_t	i;
	char	*ret;

	i = 0;
	if (!str)
		return (NULL);
	if (*str == '?')
		return (custom_dup("?"));
	while (str[i])
		i++;
	ret = (char *)malloc((1 + i) * sizeof(char));
	if (!ret)
		return (NULL);
	i = -1;
	while (str[i++] && !is_whitespace(str[i]))
		ret[i] = str[i];
	ret[i] = '\0';
	return (ret);
}

size_t	get_arg_len(char *arg)
{
	size_t	l;
	size_t	i;
	bool	detected;

	l = 0;
	i = 0;
	detected = false;
	if (!arg)
		return (l);
	while (arg[i])
	{
		if (arg[i] == '$' && !detected)
		{
			while (arg[i] && !is_whitespace(arg[i]))
				i++;
			detected = true;
		}
		else
		{
			l++;
			i++;
		}
	}
	return (l);
}

size_t	get_len(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i])
		i++;
	return (i);
}

size_t	move_env(char *res, char *env)
{
	size_t	i;

	i = 0;
	while (env[i])
	{
		res[i] = env[i];
		i++;
	}
	return (i);
}
