/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 00:15:01 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/05/31 00:16:40 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_io(t_node *node)
{
	if ((node)->fd[0] != 0)
	{
		if (dup2((node)->fd[0], STDIN_FILENO) < 0)
			return (perror("dup2"), close((node)->fd[0]), -1);
		close((node)->fd[0]);
	}
	if ((node)->fd[1] != 1)
	{
		if (dup2((node)->fd[1], STDOUT_FILENO) < 0)
			return (perror("dup2"), close((node)->fd[1]), -1);
		close((node)->fd[1]);
	}
	return (0);
}
