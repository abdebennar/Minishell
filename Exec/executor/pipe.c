/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 03:57:42 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/04/26 06:37:37 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	rbuddha(t_node *node, int *piped)
{
	int		forked;

	forked = fork();
	if (forked < 0)
	{
		perror("fork");
		return (-1);
	}
	if (!forked)
	{
		close(piped[0]);
		dup2(piped[1], STDOUT_FILENO);
		close(piped[1]);
		_exec_(&node);
		perror("Command not found");
	}
	return (forked);
}

int	lbuddha(t_node *node, int *piped)
{
	int	forked;

	forked = fork();
	if (forked < 0)
	{
		perror("fork");
		return (-1);
	}
	if (!forked)
	{
		close(piped[1]);
		dup2(piped[0], STDIN_FILENO);
		close(piped[0]);
		_exec_(&node);
		perror("Command not found");
	}
	return (forked);
}

void	_pipe_(t_node *node)
{
	pid_t		pid[2];
	int			piped[2];

	if (pipe(piped) < 0)
		perror("pipe");
	node->fd[1] = 1;
	pid[0] = lbuddha(node, piped);
	if (pid[0] < 0)
	{
		close(pid[0]);
		close(pid[1]);
		return ;
	}
	pid[1] = rbuddha(node, piped);
	if (pid[1] < 0)
	{
		close(pid[0]);
		close(pid[1]);
		return ;
	}
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
	close(piped[1]);
	close(piped[0]);
}
