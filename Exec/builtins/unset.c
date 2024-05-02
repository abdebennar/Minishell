/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 08:47:25 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/05/02 14:36:06 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

// static int check_var(char *str)
// {
// 	if (!((*str >= 'a' && *str <= 'z')
// 		|| (*str >= 'A' && *str <= 'Z') || (*str == '_')))	
// 		return (-1);
// 	while(++*str)
// 	{
// 		if (!((*str >= 'a' && *str <= 'z')
// 			|| (*str >= 'A' && *str <= 'Z')
// 			|| (*str >= '0' && *str <= '9')
// 			|| (*str == '_')))
// 			return (-1);
// 	}
// 	return (0);
// }

static void	unset_args(char *env)
{	
	extern char **environ;
	char		**tmp;

	tmp = environ;
	// if (check_var(env))
	// {
	// 	printf("unset: %s : not a valid identifier\n", env);
	// 	exit(1);
	// }
	if (getenv(env))
		while (*tmp)
		{
			if (!ft_strncmp(env, *tmp, get_c(*tmp)))
			{
				while (*(++tmp))
				{
					*(tmp - 1) = *tmp;
				}
				*(--tmp) = NULL;
				break;
			}
			tmp++;
		}
}

void	_unset_(t_node *node)
{
	char	**cmd;

	cmd = node->cmd;
	if (!cmd[1])
	{
		printf("unset: not enough arguments");
		exit(1);
	}
	while(*(++cmd))
		unset_args(*cmd);
}
