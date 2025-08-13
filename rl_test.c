/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_test.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurtamo <mhurtamo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 17:52:31 by mhurtamo          #+#    #+#             */
/*   Updated: 2025/07/11 18:05:53 by mhurtamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main()
{
	char *c;
	while(1)
	{
		rl_replace_line("ayy", 0);
		rl_redisplay();
		c = readline("asd: ");
		printf("%s\n", c);
		add_history(c);
	}
	return (1);

}


