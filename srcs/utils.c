/* srcs/utils.c */
/* 토큰화(tokenize)와 실행(execute)은 직접 구현하세요 */
#include "../includes/minishell.h"

void    free_tokens(char **args)
{
    (void)args;
}

void	ft_free_2d_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
