/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 01:34:18 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/05/28 02:25:53 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_doc(t_node *root)
{
	t_redir	*alter;

	if (!root)
		return ;
	alter = root->redir;
	while (alter)
	{
		if (alter->tok == HEREDOC)
			close(alter->fd);
		alter = alter->next;
	}
	if (root->left)
		close_doc(root->left);
	if (root->right)
		close_doc(root->right);
}

int	handle_heredoc(t_node *root)
{
	t_redir	*alter;
	int		fd;

	if (!root)
		return (0);
	fd = dup(STDIN_FILENO);
	alter = root->redir;
	while (alter)
	{
		alter->file = beta_expanding(alter->file);
		if (!alter->file)
			alter->file = ft_strdup("\0", 0);
		if (alter->tok == HEREDOC)
			alter->fd = _heredoc_(alter);
		if (alter->fd == -1)
			return (dup2(fd, 0), close(fd), 1);
		alter = alter->next;
	}
	close(fd);
	if (root->left && handle_heredoc(root->left))
		return (1);
	if (root->right && handle_heredoc(root->right))
		return (1);
	return (0);
}