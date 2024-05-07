/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:11:05 by abennar           #+#    #+#             */
/*   Updated: 2024/05/07 11:08:26 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_h(int sigN)
{
	if (g_sig == 0)
	{
		(void)sigN;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sig_ign()
{
	struct sigaction sig;
	
	sig.sa_handler = &sigint_h;
	sigemptyset(&sig.sa_mask);
	sigaddset(&sig.sa_mask, SIGINT | SIGQUIT);
	if (sigaction(SIGINT, &sig, NULL) == -1 || signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		perror("shell -- signals err");
}

void	sig_allow()
{
	if (signal(SIGINT, SIG_DFL) == SIG_ERR || signal(SIGQUIT, SIG_DFL) == SIG_ERR)
		perror("shell -- signals err");
}

void	heredoc_h(int n)
{
	(void)n;
	g_sig = 2;
	close(STDIN_FILENO);
}
