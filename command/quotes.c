/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:33:42 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/04/12 22:33:54 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_c(char *str, char c)
{
	int counter;

	counter = 0;
	while (*str)
	{
		if (*str++ == c)
			counter++;
	}
	return (counter);
}

char	*include_var(char *raw, t_env *raw_env)
{
	char	*splited;

	splited = ft_split(raw);
	if (!ft_strcmp(splited[0], "$"))
		return ("$");
	if (is_it_in(raw_env, splited[0]))
		return (getenv(splited[0]));
	return (NULL);
}

int is_it_space(char c)
{
	return (c == ' ' || c == '\t');
}

void	d_q(char *raw, t_env *raw_env)
{
	char	*splited;
	char	*clean;
	char	*simple;
	int		index;
	
	simple = malloc(ft_strlen(raw - 2));
	*raw++;
	while (*raw && *raw != '"')
	{
		if (*raw == '$')
		{
			if (*(raw + 1) == '?')
				last_exit_stat();
			else if (*(raw + 1))
			{
				clean = ft_strjoin(clean, include_var(raw, raw_env));
				while (*raw && *raw != '$' && !is_it_space(*raw))
					raw++;
			}
		}
		index = -1;
		while (*raw && *raw != '$')
			simple[++index] = *raw++;
		simple[++index] = 0;
		clean = ft_strjoin(clean, simple);
	}
	return (clean);
}

void	s_q(char *raw)
{
	char	*clean;
	int		index;

	*raw++;
	index = -1;
	clean = my_malloc(ft_strlen(raw - 2), 1);
	while (*raw && *raw != '\'')
		clean[++index] = *raw++;
	return (clean);
}
