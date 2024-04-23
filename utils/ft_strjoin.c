/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 22:16:11 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/04/23 19:54:49 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

static char	*one_null(char *s1, char *s2, int group)
{
	if (!s1 && !s2)
		return (NULL);
	if (s1)
		return (ft_strdup(s1, group));
	return (ft_strdup(s2, group));
}

char	*ft_strjoin(char *s1, char *s2, int group)
{
	char	*join;
	int		index;
	int		index2;

	if (!s1 || !s2)
		return (one_null(s1, s2, group));
	join = my_malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char), 1, group);
	if (!join)
		return (NULL);
	index = -1;
	while (s1[++index])
		join[index] = s1[index];
	index2 = -1;
	while (s2[++index2])
		join[index++] = s2[index2];
	join[index] = 0;
	return (join);
}