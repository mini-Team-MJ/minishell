/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurtamo <mhurtamo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 16:58:11 by mhurtamo          #+#    #+#             */
/*   Updated: 2025/06/28 16:58:15 by mhurtamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char	*make_arg(char *str, t_env **envs)
{
	size_t	i;
	char	*arg;
	char	*name;
	bool	got_envs;
	
	got_envs = false;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			name = make_name(&str[i + 1]);
			if (!name)
				return (NULL);
			if (!got_envs)
				arg = parse_env(str, name, envs, true);
			else
				arg = parse_env(arg, name, envs, false);
			free(name);
			if (!arg)
				return (arg);
			got_envs = true;
			while (str[i] && !is_whitespace(str[i]))
				i++;
		}
		else
			i++;
	}
	if (!got_envs)
		arg = custom_dup(str);
	return (arg);
}

