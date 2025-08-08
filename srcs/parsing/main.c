/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurtamo <mhurtamo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 17:57:59 by mhurtamo          #+#    #+#             */
/*   Updated: 2025/08/08 17:58:35 by mhurtamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parse.h"
int main()
{
	t_token *t;
	t_com *c;
	t_env *e = NULL;
	t_shell	shell;
	shell.envs = e;
	shell.lsig = 240;
	char *abc = "/home/mhurtamo/ms2/minishell/srcs/parsin > asd > $world";
	t = NULL;
	c = NULL;
	shell.tokens = tokenize(abc, &t);
	if(!shell.tokens)
		return(1);
	e = (t_env *)malloc(1 * sizeof(t_env));
	e->name = "world";
	e->value = "echo";
	t_env *b = (t_env *)malloc(1 * sizeof(t_env));
	b->name = "a";
	b->value = "abcd123";
	e->next = b;
	shell.envs = e;
	shell.commands = init_coms(&t, &c, &shell);
	printf("%s", shell.commands->args[4]);
	free(b);
	free(shell.envs);
}
