/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 08:47:25 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/05/08 20:12:19 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

static int check_var(char *str)
{
	char	*save;
	
	save = str;
	if (!((*str >= 'a' && *str <= 'z')
		|| (*str >= 'A' && *str <= 'Z') || (*str == '_')))	
		return (-1);
	while(*str)
	{
		if (!(is_alphanum(*str) && (*str != '_')))
			return (-1) ;
		str++;
	}
	return (0);
}

static void	unset_args(char *env)
{	
	extern char **environ;
	char		**tmp;

	tmp = environ;
	if (check_var(env))
	{
		printf("unset: %s : not a valid identifier\n", env);
		_setenv("?", ft_itoa(1));
		return ;
	}
	if (getenv(env))
		while (*tmp)
		{
			if (!ft_strncmp(env, *tmp, get_c(*tmp)))
			{
				while (*(++tmp))
					*(tmp - 1) = *tmp;
				*(--tmp) = NULL;
				break;
			}
			tmp++;
		}
	else 
		_setenv("?", ft_itoa(1));
}

void	_unset_(t_node *node)
{
	char	**cmd;

	cmd = node->cmd;
	_setenv("?", ft_itoa(0));
	while(*(++cmd))
		unset_args(*cmd);
}
