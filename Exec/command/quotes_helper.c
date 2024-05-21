/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 21:42:49 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/05/21 05:50:05 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*add_c(char *str, char c, int group)
{
	char	*new;
	char	*save;

	new = my_malloc(ft_strlen(str) + 2, 1, group);
	save = new;
	while (str && *str)
		*new++ = *str++;
	*new++ = c;
	*new = 0;
	return (save);
}

int	only_identifier(char *str)
{
	char	*save;

	save = str;
	if (!((*str >= 'a' && *str <= 'z')
			|| (*str >= 'A' && *str <= 'Z') || (*str == '_')))
		return (0);
	while (*str)
	{
		if (!(is_alphanum(*str) || (*str == '_')))
			break ;
		str++;
	}
	return ((int)(str - save));
}

int	count_c(char *str, char c)
{
	int	counter;

	counter = 0;
	if (!str || !c)
		return (0);
	while (*str)
		if (*(str++) == c)
			counter++;
	return (counter);
}

char	*check_envar(char *raw, int *index)
{
	size_t	ident;
	char	*new;
	char	*possible;

	new = NULL;
	ident = only_identifier(raw);
	if (ident)
	{
		possible = ft_strdup_len(raw, ident, 0);
		new = ft_strjoin(new, getenv(possible), 0);
		*index += ident;
	}
	return (new);
}

void	find_replace(char *str, char find, char rep)
{
	if (!str)
		return ;
	while (*str)
	{
		if (*str == find)
			*str = rep;
		str++;
	}
}
