/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 01:34:18 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/05/30 00:09:31 by abennar          ###   ########.fr       */
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

	if (!root)
		return (0);
	alter = root->redir;
	while (alter)
	{
		if (alter->tok == HEREDOC)
		{
			alter->file = beta_expanding(alter->file);
			if (!alter->file)
				alter->file = ft_strdup("\0", 0);
			alter->content = _heredoc_(alter);
			if (alter->content == NULL)
			return (1);
		}
		alter = alter->next;
	}
	if (root->left && handle_heredoc(root->left))
		return (1);
	if (root->right && handle_heredoc(root->right))
		return (1);
	return (0);
}
