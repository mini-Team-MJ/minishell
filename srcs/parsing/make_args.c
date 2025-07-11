/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurtamo <mhurtamo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 18:10:18 by mhurtamo          #+#    #+#             */
/*   Updated: 2025/07/10 18:10:21 by mhurtamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*make_arg(char *str, t_shell *shell)
{
	size_t	i;
	char	*arg;
	char	*name;
	bool	got_envs;

	got_envs = false;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '$')
		{
			name = make_name(&str[i + 1]);
			if (got_envs)
				arg = env_parse_handler(str, name, shell, got_envs);
			else
				arg = env_parse_handler(arg, name, shell, got_envs);
			got_envs = true;
			if (!arg)
				return (arg);
			i += arg_mover(&str[i]);
		}
	}
	if (!got_envs)
		arg = custom_dup(str);
	return (arg);
}

char	**args_creation_loop(t_token **tokens, char **args, t_shell
*shell, size_t ac)
{
	size_t	i;
	t_token	*current;

	i = 0;
	current = *tokens;
	while (i < ac)
	{
		if (current->sq)
			args[i] = custom_dup(current->str);
		else
			args[i] = make_arg(current->str, shell);
		if (!args[i])
		{
			free_args(args);
			return (NULL);
		}
		current = current->next;
		i++;
	}
	return (args);
}

char	**make_args(t_token **tokens, t_shell *shell)
{
	size_t	ac;
	char	**args;

	ac = count_args(tokens);
	args = (char **)malloc(ac * sizeof(char *));
	if (!args)
		return (NULL);
	args = args_creation_loop(tokens, args, shell, ac);
	return (args);
}
