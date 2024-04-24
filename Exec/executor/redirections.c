/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 04:00:45 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/04/24 14:56:11 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_right_(t_node *node)
{
	t_redir *alter;
	int		fd;

	alter = node->redir;
	fd = 1;
	while (alter)
	{
		if (alter->tok == OUT)
		{
			if (fd > 1)
				close(fd);
			fd = open(alter->file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		}
		else if (alter->tok == APPEND)
		{
			if (fd > 1)
				close(fd);
			fd = open(alter->file, O_WRONLY | O_APPEND | O_CREAT, 0644);
		}
		if (fd < 0)
			return (perror("open"), -1);
		alter = alter->next;
	}
	node->fd[1] = fd;
	return (0);
}

int	_left_(t_node *node)
{
	t_redir *alter;
	int		fd;

	fd = 0;
	alter = node->redir;
	while (alter)
	{
		if (alter->tok == IN)
		{
			if (fd > 0)
				close(fd);
			fd = open(alter->file, O_RDONLY , 0644);
		}
		else if (alter->tok == HEREDOC)
		{
			if (fd > 0)
				close(fd);
			fd = alter->fd;
		}
		if (fd < 0)
			return (perror("open"), -1);
		alter = alter->next;
	}
	node->fd[0] = fd;
	return (0);
}
 
//TODO expand inside heredoc 

void	_redirections_(t_node *node)
{
	t_redir *alter;

	alter = node->redir;
	while (alter)
	{
		if (alter->tok == HEREDOC)
			alter->fd = _heredoc_(alter);
		alter = alter->next;
	}
	if (_left_(node) || _right_(node))
		perror("left || right");
	if (node->fd[0] != 0)
		dup2(node->fd[0], STDIN_FILENO);
	if (node->fd[1] != 1)
		dup2(node->fd[1], STDOUT_FILENO);
}
