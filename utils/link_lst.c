/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:45:49 by abennar           #+#    #+#             */
/*   Updated: 2024/05/07 17:22:18 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	lst_iter(t_node	*lst, void (*f)(t_node *))
{
	while (lst)
	{
		if (lst->tok == NOT)
			f(lst);
		lst = lst->right;
	}
}

t_node	*new_node(char *cmd, t_redir *redir, t_token tok, int pre)
{
	t_node	*new;

	new = my_malloc(sizeof(t_node), ALLOC, 0);
	new->full_cmd = cmd;
	new->redir = redir;
	new->tok = tok;
	new->pre = pre;
	new->fd[0] = 0;
	new->fd[1] = 1;
	new->right = NULL;
	new->left = NULL;
	return (new);
}


t_redir	*new_redir(char *file, t_token tok)
{
	t_redir	*new;
	
	new = my_malloc(sizeof(t_redir), ALLOC, 0);
	new->file = file;
	new->tok = tok;
	new->next = NULL;
	new->prev = NULL;
	
	return (new);
}

void	add_redir_back(t_redir *node, t_redir **list)
{
	t_redir	*tmp;

	if (!node || !list)
		return;
	if (!*list)
	{
		*list = node;
	}
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
		node->prev = tmp;
	}
}

void	add_node_back(t_node *node, t_node **list)
{
	t_node	*tmp;

	if (!node || !list)
		return ;
	if (!*list)
	{
		*list = node;
	}
	else
	{
		tmp = *list;
		while (tmp->right)
			tmp = tmp->right;
		tmp->right = node;
		node->left = tmp;
	}
}
