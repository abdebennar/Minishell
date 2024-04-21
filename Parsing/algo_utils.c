/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:59:40 by abennar           #+#    #+#             */
/*   Updated: 2024/04/21 19:34:35 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*postfix_to_prefix(t_node *node)
{
	while (node->right)
		node = node->right;
	return (node);
}


void top_push(t_node **src, t_node **dest)
{
	t_node	*trget;
    if (!*src)
        return;

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

	*src  = (*src)->right;
	if (*src)
		(*src)->left = NULL;

	trget->right = NULL;
	trget->left = NULL;

	add_node_back(trget, dest);
}
