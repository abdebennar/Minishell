/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 08:47:25 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/04/03 09:31:08 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int check_var(char *str)
{
	if (!((*str >= 'a' && *str <= 'z')
		|| (*str >= 'A' && *str <= 'Z') || (*str == '_')))	
		return (-1);
	while(++*str)
	{
		if (!((*str >= 'a' && *str <= 'z')
			|| (*str >= 'A' && *str <= 'Z')
			|| (*str >= '0' && *str <= '9')
			|| (*str == '_')))
			return (-1);
	}
	return (0);
}

static void	unset_args(char *arg, t_env **raw_env)
{
	t_env	*tmp;
	
	if (check_var(arg))
	{
		printf("unset: %s: invalid parameter name", arg);
		exit(1);
	}
	while(ft_strcmp((*raw_env)->value, arg))
	{
		tmp = *raw_env;
		(*raw_env) = (*raw_env)->next;
	}
	tmp->next = (*raw_env)->next;
	if (*raw_env)
	{
		free((*raw_env)->env);
		free((*raw_env)->var);
		free((*raw_env)->value);
		free(*raw_env);
	}
}

void	_unset_(char **cmd, t_env **raw_env)
{
	if (!cmd[1])
	{
		printf("unset: not enough arguments");
		exit(1);
	}
	while(*(++cmd))
		unset_args(*cmd, raw_env);
}
