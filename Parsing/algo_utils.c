/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:59:40 by abennar           #+#    #+#             */
/*   Updated: 2024/05/28 19:55:50 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*postfix_to_prefix(t_node *node)
{
	while (node->right)
		node = node->right;
	return (node);
}

void	top_push(t_node **src, t_node **dest)
{
	t_node	*trget;

	if (!*src)
		return ;
	trget = *src;
	*src = (*src)->right;
	trget->right = *dest;
	if (*dest)
		(*dest)->left = trget;
	*dest = trget;
	trget->left = NULL;
}

void	back_push(t_node **src, t_node **dest)
{
	t_node	*trget;

	if (!*src)
		return ;
	trget = *src;
	*src = (*src)->right;
	if (*src)
		(*src)->left = NULL;
	trget->right = NULL;
	trget->left = NULL;
	add_node_back(trget, dest);
}
