/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:11:05 by abennar           #+#    #+#             */
/*   Updated: 2024/06/04 14:06:56 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Signal handler for SIGINT (Ctrl+C).
** This function handles the interrupt signal by setting the exit status to 1
** and printing a new line, and updating the readline prompt.
** I used the global variable to control the behavior of signals in multiple cases. For example :
**	in the case of a heredoc, I use a different handler, so I need to skip this one.
*/

/*
**	i.  `rl_on_new_line()`: Inform readline that the cursor is on a new line.
**	ii. `rl_replace_line("", 0)`: Clear the current line buffer.
**	iii.`rl_redisplay()`: Refresh the prompt display to show the updated prompt.
*/

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

/*
**	This function changes the behavior of specific signals:
**	1. SIGINT (interrupt signal): This signal is commonly sent when the user
**	  types Ctrl+C. The function sets the signal handler to `sigint_h`, which
**	  will display a new prompt when the signal is received.
**	2. SIGQUIT (quit signal): This signal is commonly sent when the user types
**    Ctrl+\ (backslash). The function sets the handler to ignore this signal
**    as specified by the requirements.
**
**	If either signal setup fails, an error message is printed using perror.
*/


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
