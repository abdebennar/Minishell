/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:11:05 by abennar           #+#    #+#             */
/*   Updated: 2024/05/31 21:45:08 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_h(int sigN)
{
	extern int	g_sig;

	if (g_sig == 0)
	{
		(void)sigN;
		_setenv("?", ft_itoa(1));
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sig_ign(void)
{
	if (signal(SIGINT, sigint_h) == SIG_ERR
		|| signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		perror("shell -- signals err");
}

void	sig_allow(void)
{
	if (signal(SIGINT, SIG_DFL) == SIG_ERR
		|| signal(SIGQUIT, SIG_DFL) == SIG_ERR)
		perror("shell -- signals err");
}

void	heredoc_h(int n)
{
	extern int	g_sig;

	(void)n;
	g_sig = 2;
	close(STDIN_FILENO);
}
