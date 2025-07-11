/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurtamo <mhurtamo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:55:08 by mhurtamo          #+#    #+#             */
/*   Updated: 2025/07/10 17:55:09 by mhurtamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char	*parse_env(char *str, char *name, t_shell *shell, bool got_envs)
{
	char	*ret;
	t_env	*env;
	char	*sig_val;

	if (ftstrncmp(name, "?", 1))
	{
		sig_val = get_sig_val(shell->lsig);
		ret = custom_join(str, sig_val, got_envs, "?");
		free(sig_val);
	}
	else
	{
		env = find_env(name, shell->envs);
		if (!env)
			return (NULL);
		ret = custom_join(str, env->value, got_envs, name);
	}
	if (got_envs)
		free(str);
	return (ret);
}

char	*env_parse_handler(char *str, char *name, t_shell *shell, bool
got_envs)
{
	char	*ret;

	if (!name)
	{
		if (arg)
			free(arg);
		return (NULL);
	}
	ret = parse_env(str, name, &shell->envs, got_envs, shell->lsig);
	free(name);
	return (ret);
}
