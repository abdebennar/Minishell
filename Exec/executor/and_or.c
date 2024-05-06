/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 03:49:25 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/05/06 16:28:12 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

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