/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:43:59 by abennar           #+#    #+#             */
/*   Updated: 2024/06/04 12:36:56 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy(char **str, bool extra_size, int group)
{
	int		l_cnt;
	char	**new;
	int		i;
	int		j;

	l_cnt = 0;
	while (str[l_cnt])
		l_cnt++;
	new = my_malloc((l_cnt + 1 + extra_size) * sizeof (char *), ALLOC, group);
	i = 0;
	j = 0;
	(extra_size) && (j++);
	while (str[i])
	{
		l_cnt = ft_strlen(str[i]);
		new[j] = my_malloc(l_cnt + 1, ALLOC, 1);
		ft_strcpy(new[j], str[i]);
		i++;
		j++;
	}
	new[j] = NULL;
	return (new);
}

/*
**	Here i copy the existing environment variables to a new 
**	environment in heap. you will understand later why.
**	Disable readline signal handling. `rl_catch_signals = 0;`
**	as the readline has its own signals handlers.
*/

/*
**	Note: Be cautious when running the shell without a defined environment, as
**	this can cause a segmentation fault (`env -i ./minishell`).
*/

void	add_env(void)
{
	extern int	rl_catch_signals;
	int			sh_lvl;
	int			err;

	environ = copy(environ, false, 1);
	rl_catch_signals = 0;
	if (!getenv("SHLVL"))
		sh_lvl = 0;
	else
		sh_lvl = ft_atoll(getenv("SHLVL"), &err);
	_setenv("SHLVL", ft_itoa(sh_lvl + 1));
	_setenv("?", ft_itoa(0));
}
