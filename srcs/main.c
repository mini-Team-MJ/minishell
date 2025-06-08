/* srcs/main.c */
#include "../includes/minishell.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

volatile sig_atomic_t g_signal = 0;

/* SIGINT 핸들러: 새 프롬프트만 출력 */
static void sigint_handler(int sig)
{
	g_signal = sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void setup_signals(void)
{
	struct sigaction sa;

	sa.sa_handler = sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

int main(int argc, char **argv, char **envp)
{
	char	*line;
	t_env	*env_list;
	char	**args;


	(void)argc;
	(void)argv;
	(void)args;
	setup_signals();
	env_list = env_init(envp);
	while (1)
	{
		line = readline(GRN "minishell> " RESET);
		if (!line)
			break ;                   /* Ctrl+D */
		if (*line)
			add_history(line);
		// args = tokenize(line);
		execute(line, &env_list);
		// free_tokens(args);
		free(line);
	}
	rl_clear_history();
	return 0;
}
