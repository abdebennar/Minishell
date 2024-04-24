/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 03:49:25 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/04/24 05:02:34 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	_or_(t_node *node, int exit_stat)
{
	if (!node)
		exit(-1);
	if (exit_stat)
		executor(node->left);
}

void	_and_(t_node *node, int exit_stat)
{
	if (!node)
		exit(-1);
	if (!exit_stat)
		executor(node->left);
}