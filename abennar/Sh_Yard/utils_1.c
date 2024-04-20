/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:59:40 by abennar           #+#    #+#             */
/*   Updated: 2024/04/19 17:08:41 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	push(t_node **src, t_node **dest)
// {
// 	t_node	*trget;

// 	trget = *src;
// 	trget->right = NULL;
// 	trget->left = NULL;
// 	if (!*dest)
// 	{
// 		*dest = trget;
// 		return;
// 	}

// 	(*src)->left = NULL;
// 	(*src) = (*src)->right;
// 	trget->right = *dest;

// 	(*dest)->left = trget;
// }



void push(t_node **src, t_node **dest) {
    if (!*src) // If source stack is empty, there's nothing to push
        return;

    t_node *trget = *src; // Get the node to be pushed
    *src = (*src)->right; // Move the source stack pointer to the next node

    trget->right = *dest; // Link trget to the top of destination stack
    if (*dest) // If destination stack is not empty
        (*dest)->left = trget; // Update the left pointer of the previous top node
    *dest = trget; // Update the destination stack pointer to trget
    trget->left = NULL; // Since trget is at the top of the destination stack, its left pointer should be NULL
}
