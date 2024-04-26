/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 09:32:42 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/04/24 05:23:01 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

int	find_c(char *str, char c)
{
	if (!str)
		return (0);
	while (*str)
		if (*str++ == c)
			return (1);
	return (0);
}
void	_env_(t_node *node)
{
	t_env	*raw_env;
	char	**cmd;

	cmd = node->cmd;
	raw_env = node->env;
	while(raw_env)
	{
		if (find_c((raw_env)->env, '='))
			printf("%s\n", (raw_env)->env);
		raw_env = (raw_env)->next;
	}
}