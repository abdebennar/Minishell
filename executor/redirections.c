/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 04:00:45 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/04/21 17:51:33 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_right_(t_node *node)
{
	t_redir *alter;
	int		fd;

	alter = node->redirections;
	while (alter)
	{
		if (alter->tok == OUT)
		{
			if (fd > 0)
				close(fd);
			fd = open(alter->file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		}
		else if (alter->tok == APPEND)
		{
			if (fd > 0)
				close(fd);
			fd = open(alter->file, O_WRONLY | O_APPEND | O_CREAT, 0644);
		}
		(fd < 0) && (perror("open"), 0);
		alter = alter->right;
	}
	node->fd[1] = fd;
	return (fd);
}

int	_left_(t_node *node)
{
	t_redir *alter;
	int		fd;

	alter = node->redirections;
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
		(fd < 0) && (perror("open"), 0);
		alter = alter->right;
	}
	node->fd[0] = fd;
	return (fd);
}

void	_redirections_(t_node *node)
{
	t_redir *alter;

	alter = node->redirections;
	while (alter)
	{
		if (alter->tok == HEREDOC)
			alter->fd = _heredoc_(alter);
		alter = alter->right;
	}
	node->fd[0] = alter->fd;
	_left_(node);
	_right_(node);
}
