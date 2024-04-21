/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 23:58:29 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/04/21 17:14:46 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_in(char s, char *delim)
{
	while (*delim && *delim != s)
		delim++;
	if (!*delim)
		return (0);
	return (1);
}

static int	word_counter(char const *s, char *delim)
{
	int	counter;
	int	i;

	i = 0;
	counter = 0;
	while (s[i])
	{
		while (is_in(s[i], delim))
			i++;
		if (s[i])
			counter++;
		while (!is_in(s[i], delim) && s[i])
			i++;
	}
	return (counter);
}

static char	*char_counter(char const *s, char *delim)
{
	char		*str;
	int			counter;
	int			index;

	counter = 0;
	index = 0;
	while (!is_in(s[counter], delim) && s[counter])
		counter++;
	str = (char *)my_malloc(sizeof(char) * (counter + 1), 1);
	while (counter--)
	{
		str[index] = s[index];
		index++;
	}
	str[index] = '\0';
	return (str);
}

char	**ft_split(char *s, char *delim)
{
	char	**split;
	int		k;
	int		w_count;

	if (!s)
		return (NULL);
	w_count = word_counter(s, delim);
	split = (char **)my_malloc(sizeof(char *) * (w_count + 1), 1);
	if (!split)
		return (NULL);
	k = -1;
	while (++k < w_count)
	{
		while (is_in(*s, delim) && *delim)
			s++;
		split[k] = char_counter(s, delim);
		if (!split[k])
			return (perror(""), my_malloc(0, 0), NULL);
		s += ft_strlen(split[k]);
	}
	split[k] = NULL;
	return (split);
}