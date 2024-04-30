/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 00:01:17 by abennar           #+#    #+#             */
/*   Updated: 2024/04/30 00:57:31 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **copy(char **str, int extra_size);

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
		if (strncmp(name, (environ[*offset]) , get_c(environ[*offset])) == 0)
			break;
	}
}

void	_exist(char *name , char *new_value)
{
	char		**tmp;
	extern char **environ;
	int			offset;
	
	find_env(&offset, name);

	environ[offset] = ft_strjoin(ft_substr(environ[offset], 0, get_c(environ[offset]) + 1, 0), new_value, 1);
}

void	non_exist(char *name, char *new_value)
{
	char **new;
	extern char **environ;
	new = copy(environ, 1);
	int	i = 0;
	while (new[i])
		i++;
	new[i] = ft_strjoin(ft_strjoin(name, "=", 0), new_value, 1);
	new[++i] = NULL;
	environ = new;
}

void	_setenv(char *name, char *new_value)
{
	if (getenv(name))
		_exist(name , new_value);
	else 
		non_exist(name, new_value);
}