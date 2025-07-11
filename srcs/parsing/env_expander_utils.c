/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expander_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurtamo <mhurtamo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 18:06:48 by mhurtamo          #+#    #+#             */
/*   Updated: 2025/07/10 18:06:49 by mhurtamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char	*joiner(char *arg, char *env, char *res, char *name)
{
	bool	detected;
	size_t	i;
	size_t	j;

	detected = false;
	i = 0;
	j = 0;
	if (!res)
		return (NULL);
	while (arg[i])
	{
		if (arg[i] == '$' && !detected)
		{
			detected = true;
			j += move_env(&res[j], env);
			i += get_len(name);
			i++;
		}
		else
			res[j++] = arg[i++];
	}
	res[j] = '\0';
	return (res);
}

char	*custom_join(char *arg, char *env, bool got_envs, char *name)
{
	size_t	i;
	size_t	j;
	char	*res;

	if (!env)
		return (NULL);
	i = get_arg_len(arg);
	j = get_len(env);
	res = (char *)malloc((i + j + 1) * sizeof(char));
	if (!res)
	{
		if (got_envs)
			free(arg);
		return (NULL);
	}
	res = joiner(arg, env, res, name);
	if (got_envs)
		free(arg);
	return (res);
}

char	*get_sig_val(int lsig)
{
	int		copy;
	char	*ret;
	size_t	len;

	copy = lsig;
	len = 1;
	while (copy >= 10)
	{
		len++;
		copy /= 10;
	}
	ret = (char *)malloc((len + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	ret[len] = '\0';
	len--;
	while (len > 0 && lsig >= 10)
	{
		ret[len] = (lsig % 10) + 48;
		lsig /= 10;
		len--;
	}
	ret[len] = lsig + 48;
	return (ret);
}
