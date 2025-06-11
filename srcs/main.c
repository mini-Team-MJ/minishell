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
	t_shell	sh;

	(void)argc;
	(void)argv;
	sh.commands   = NULL;
	sh.tokens     = NULL;
	sh.envs       = env_init(envp);
	sh.lines      = NULL;
	sh.last_exit  = 0;
	setup_signals();
	while ((line = readline(GRN "minishell> " RESET)))
	{
		if (*line)
			add_history(line);
		execute(line, &sh);
		free(line);
	}
	rl_clear_history();
	return 0;
}
