/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 23:50:48 by abennar           #+#    #+#             */
/*   Updated: 2024/05/28 19:55:50 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_the_set(char c, const char *set)
{
	int		i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(const char *s1, const char *set, int group)
{
	int		start;
	int		end;
	int		trk;
	char	*str;

	start = 0;
	end = 0;
	trk = 0;
	if (!set || !s1)
		return (NULL);
	while (s1[start] && check_the_set(s1[start], set))
		start++;
	end = ft_strlen(s1);
	while (end > start && check_the_set(s1[end - 1], set))
		end--;
	str = (char *)my_malloc(sizeof(char) * (end - start + 2), 1, group);
	while (start < end && s1[start])
	{
		str[trk++] = s1[start++];
	}
	str[trk] = '\0';
	str[++trk] = '\0';
	return (str);
}
