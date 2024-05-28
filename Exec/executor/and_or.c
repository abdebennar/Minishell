/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 03:49:25 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/05/28 19:55:50 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_or_(t_node *node)
{
	if (!node)
		exit(-1);
	_exec_arch_((node->left));
	if (ft_atoll(getenv("?"), NULL))
		_exec_arch_((node->right));
}

void	_and_(t_node *node)
{
	if (!node)
		exit(-1);
	_exec_arch_(node->left);
	if (!ft_atoll(getenv("?"), NULL))
		_exec_arch_(node->right);
}
