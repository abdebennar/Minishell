/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 17:37:42 by abennar           #+#    #+#             */
/*   Updated: 2024/05/28 19:55:50 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*tree(t_node	*node)
{
	if (!node)
		return (NULL);
	if (node->tok == NOT)
	{
		if (node->right && node->left)
		{
			node->right->left = node->left;
			node->left->right = node->right;
			if (node->right->right)
				node->left->right = node->right->right;
		}
		node->right = NULL;
		node->left = NULL;
	}
	else
	{
		node->right = tree(node->left);
		node->left = tree(node->left);
	}
	return (node);
}
