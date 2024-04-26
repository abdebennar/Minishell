/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_lst2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 00:23:33 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/04/26 00:23:44 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstaddback(t_env **alst, t_env *new)
{
	t_env *ptr;

	if (alst && *alst)
	{
		ptr = *alst;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
	}
	else if (alst)
		*alst = new;
}
