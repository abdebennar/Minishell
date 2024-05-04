/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 09:32:42 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/05/04 17:19:25 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	_env_()
{
	extern char **environ;
	char 		**tmp;

	tmp = environ;
	while (*tmp)
	{
		if (ft_strchr(*tmp, '='))
			printf("%s\n", *tmp);
		tmp++;
	}
	_setenv("?", ft_itoa(0));
}
