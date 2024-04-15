/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 03:57:42 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/04/15 15:56:36 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	err(int *fd_in, int *fd_out)
{
	(fd_in) && (close(*fd_in), 0);
	(fd_out) && (close(*fd_out), 0);
	my_malloc(0, 0);
}

void	w_err(char *str)
{
	write(2, "[-] ", 5);
	write(2, str, ft_strlen(str));
	write(2, "\n", 2);
	my_malloc(0, 0);
}

int	rbuddha(t_node *node, int *piped)
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
		close(piped[0]);
		dup2(piped[1], STDOUT_FILENO);
		close(piped[1]);
		execve(node->cmd[0], node->cmd, NULL);
		w_err("Command not found");
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
		execve(node->cmd[0], node->cmd, NULL);
		w_err("Command not found");
	}
	return (forked);
}

void	_pipe_(t_node *cmd)
{
	pid_t		pid[2];
	int			piped[2];

	if (pipe(piped) < 0)
		perror("pipe");
	pid[0] = lbuddha(cmd->lchild, piped);
	if (pid[0] < 0)
	{
		close(pid[0]);
		close(pid[1]);
		return ;
	}
	pid[1] = rbuddha(cmd->rchild, piped);
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
