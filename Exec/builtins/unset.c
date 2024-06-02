/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 22:33:06 by abennar           #+#    #+#             */
/*   Updated: 2024/05/28 19:55:50 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_var(char *str)
{
	char	*save;

	save = str;
	if (!((*str >= 'a' && *str <= 'z')
			|| (*str >= 'A' && *str <= 'Z') || (*str == '_')))
		return (-1);
	while (*str)
	{
		if (!is_alphanum(*str) && (*str != '_'))
			return (-1);
		str++;
	}
	return (0);
}

static void	unset_args(char *env)
{
	char		**tmp;
	int			offset;

	tmp = environ;
	if (check_var(env))
	{
		printf("unset: %s : not a valid identifier\n", env);
		_setenv("?", ft_itoa(1));
		return ;
	}
	if (find_env(&offset, env))
	{
		while (*tmp)
		{
			if (!ft_strncmp(env, *tmp, get_c(*tmp)))
			{
				while (*(++tmp))
					*(tmp - 1) = *tmp;
				*(--tmp) = NULL;
				break ;
			}
			tmp++;
		}
	}
}

void	_unset_(t_node *node)
{
	char	**cmd;

	cmd = node->cmd;
	_setenv("?", ft_itoa(0));
	while (*(++cmd))
		unset_args(*cmd);
}
