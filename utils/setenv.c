/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 00:01:17 by abennar           #+#    #+#             */
/*   Updated: 2024/05/01 03:43:45 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	get_c(char *s)
{
	int	i;

	i = 0;
	while (*s && *s != '=')
	{
		i++;
		s++;
	}
	return (i);
}

void	find_env(int *offset, char *name)
{
	extern char **environ;

	*offset = 0;
	
	while (environ[*offset])
	{
		if (ft_strncmp(name, (environ[*offset]) , get_c(environ[*offset])) == 0)
			break;
		(*offset)++;
	}
}

void	_exist(char *name , char *new_value)
{
	char		**tmp;
	extern char **environ;
	int			offset;
	
	find_env(&offset, name);

	environ[offset] = ft_strjoin(ft_substr(environ[offset], 0,
	get_c(environ[offset]) + 1, 0), new_value, 1);
}

void	non_exist(char *name, char *new_value)
{
	char **new;
	extern char **environ;
	new = copy(environ, true, 1);
	int	i = 0;
	new[i] = ft_strjoin(ft_strjoin(name, "=", 0), new_value, 1);
	environ = new;
}

void	_setenv(char *name, char *new_value)
{
	if (getenv(name))
		_exist(name , new_value);
	else 
		non_exist(name, new_value);
}