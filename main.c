/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 08:22:24 by abennar           #+#    #+#             */
/*   Updated: 2024/06/01 00:45:08 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig = 0;

void	term_attr(struct termios *att)
{
	if (isatty(STDIN_FILENO) && tcgetattr(STDIN_FILENO, att))
		perror("termios");
}

int	main(void)
{
	char			*line;
	t_node			*node;
	struct termios	att;

	add_env();
	while (666)
	{
		sig_ign();
		my_malloc(0, 0, 0);
		line = readline(PROMPT);
		if (!line)
			break ;
		node = parsing(line);
		if (handle_heredoc(node))
			node = NULL;
		term_attr(&att);
		_exec_arch_(node);
		g_sig = 0;
		if (isatty(STDIN_FILENO) && tcsetattr(0, TCSANOW, &att))
			perror("termios");
	}
	put_err("exit\n");
	rl_clear_history();
	my_malloc(0, 0, 1);
	my_malloc(0, 0, 0);
}
