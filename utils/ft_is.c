/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 19:54:18 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/04/23 05:31:30 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

int	is_alphanum(char c)
{
	return ((c >= 'a' && c <= 'z')
			|| (c >= 'A' && c <= 'Z')
			|| (c >= '0' && c <= '9'));
}

int is_it_in(t_env *raw_env, char *new_var)
{
	while (raw_env)
	{
		if (!ft_strcmp(raw_env->var, new_var))
			return (1);
		raw_env = raw_env->next;
	}
	return (0);
}
