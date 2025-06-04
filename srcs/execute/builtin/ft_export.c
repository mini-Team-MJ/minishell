/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh3900 <ljh3900@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:39:28 by juhyeonl          #+#    #+#             */
/*   Updated: 2025/06/04 23:38:11 by ljh3900          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
/*
	export VAR1=value1        
	# Expected: VAR1=value1 registered

	export VAR1=new_value     
	# Expected: VAR1 changed to new_value

	export EMPTY_VAR=         
	# Expected: EMPTY_VAR="" (empty string)

	export SP_VAR="hello world"   
	# Expected: SP_VAR="hello world"

	export ESC_VAR=hello\ world    
	# Expected: ESC_VAR="hello world"

	export BASE=foo             
	# Expected: BASE=foo
	export NEW_VAR="$BASE""bar" 
	# Expected: NEW_VAR="foobar"

	export DATE_VAR=$(date +%Y-%m-%d)  
	# Expected: DATE_VAR="<current date>"

	export A=1 B=2 C=3        
	# Expected: A=1, B=2, C=3 all registered

	export                    
	# Expected: Prints current environment variables

	export 1BAD=oops          
	# Expected: export: '1BAD': not a valid identifier

	export BAD!VAR=oops       
	# Expected: export: 'BAD!VAR': not a valid identifier

	export JUST_NAME          
	# Expected: JUST_NAME="" assigned

	export WITH_SPACE =value  
	# Expected: bad assignment or “export: 'WITH_SPACE': 
	 								not a valid identifier”
	export NXT= value         
	# Expected: NXT=" value" (leading space included)

	export LIT_VAR='hello $USER $(date)'  
	# Expected: LIT_VAR="hello $USER $(date)"

	export BROKEN="unclosed    
	# Expected: parse error (syntax error)

	export X=foo              
	# Expected: X=foo
	export Y="$X"             
	# Expected: Y="foo"
	export X=bar              
	# Expected: X="bar"

	arr=(one two three)
	export ARR="${(j: :)arr}"  
	# Expected: ARR="one two three"

	export GOOD=okay 1BAD=fail SECOND=two BAD!NAME=fail2
	# Expected:
	#   GOOD=okay registered
	#   export: '1BAD': not a valid identifier
	#   SECOND=two registered
	#   export: 'BAD!NAME': not a valid identifier

	export PATH                 
	# Expected: No change, PATH remains

	export ?                    
	# Expected: export: '?': not a valid identifier
	export $$                   
	# Expected: export: '<number>': not a valid identifier

	export TEMP_VAR=tmp         
	# Expected: TEMP_VAR=tmp
	unset TEMP_VAR              
	# Expected: TEMP_VAR removed

	export A=1;; export B=2     
	# Expected: A=1 registered, then syntax error or second export ignored
	export C=3 | export D=4     
	# Expected: C=3 registered, pipe error prevents D

	export E=5 && echo ok       
	# Expected: E=5 registered, then prints ok
	export F=6 || echo should_not_print  
	# Expected: F=6 registered, echo not executed

	touch export_file           
	# Expected: file created
	echo "export" > export_file 
	# Expected: writes "export" into file

	LONG_NAME=$(printf 'A%.0s' {1..5000})
	export "$LONG_NAME"=value   
	# Expected: Error for name too long or memory allocation failure
*/

static int	ft_env_len(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

static int	ft_arg_len(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

static void	input_tmp(char **env, char **argv, char **tmp)
{
	int	i;
	int	j;
	int	env_len;
	int	arg_len;

	env_len = ft_env_len(env);
	arg_len = ft_arg_len(argv);
	i = -1;
	while (++i < env_len)
		tmp[i] = strdup(env[i]);
	j = -1;
	while (++j < arg_len)
		tmp[env_len + j] = strdup(argv[j]);
	tmp[env_len + arg_len] = NULL;
}

static int	ft_export_error(char **argv)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	while (argv[i])
	{
		s = argv[i];
		if (!(('A' <= s[0] && s[0] <= 'Z') || ('a' <= s[0] && s[0] <= 'z')
				|| s[0] == '_'))
			return (1);
		j = 1;
		while (s[j] && s[j] != '=')
		{
			if (!((s[j] >= 'A' && s[j] <= 'Z') || (s[j] >= 'a' && s[j] <= 'z')
					|| (s[j] >= '0' && s[j] <= '9') || s[j] == '_'))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_export(char **argv, char ***env)
{
	int		env_len;
	int		arg_len;
	char	**tmp;

	if (ft_export_error(argv))
	{
		fprintf(stderr, "export: invalid identifier\n");
		return (1);
	}
	env_len = ft_env_len(*env);
	arg_len = ft_arg_len(argv);
	tmp = malloc(sizeof(char *) * (env_len + arg_len + 1));
	if (!tmp)
	{
		fprintf(stderr, "malloc failed\n");
		return (-1);
	}
	input_tmp(*env, argv, tmp);
	*env = tmp;
	ft_free_2d_array(tmp);
	return (0);
}
