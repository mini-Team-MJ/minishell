/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurtamo <mhurtamo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 17:01:22 by mhurtamo          #+#    #+#             */
/*   Updated: 2025/06/28 17:01:27 by mhurtamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	move_env(char *res, char *env)
{
	size_t	i;
	
	i = 0;
	while (env[i])
	{
		res[i] = env[i];
		i++;
	}
}

void	joiner(char *arg, char *env, char *res)
{
	bool	detected;
	size_t	i;
	size_t	j;
	size_t  e;

	detected = false;
	i = 0;
	j = 0;
	while (arg[i])
	{
		if (arg[i] == '$' && !detected)
		{
			detected = true;
		    e = 0;
		    while(env[e])
		    {
		        res[j] = env[e];
		        j++;
		        e++;
		    }
			while (arg[i] && !is_whitespace(arg[i]))
				i++;
		}
		else
		{
			res[j] = arg[i];
			i++;
			j++;
		}
	}
	res[j] = '\0';
}

char	*custom_join(char *arg, char *env, bool is_first)
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
		return (NULL);
	joiner(arg, env, res);
	if (!is_first)
		free(arg);
	return (res);
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
	i = 0;
	while (str[i] && !is_whitespace(str[i]))
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

char	*parse_env(char *str, char *name,  t_env **envs, bool is_first, int lsig)
{
	char	*ret;
	t_env	*env;
	char    *sig_val;
	
	if(ftstrcmp(name, "?"))
	{
		ret = custom_join(str, get_sig_val(lsig), is_first);
	}
	else
	{
		env = find_env(name, envs);
		if (!env)
			return (NULL);
		ret = custom_join(str, env->val, is_first);
	}
	if (!is_first)
		free(str);
	return (ret);
}
