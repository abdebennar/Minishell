/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lendupcmp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 06:21:55 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/04/17 01:50:20 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strlen(char *str)
{
	if (!str || !*str)
		return (0);
	return (1 + ft_strlen(++str));
}

int	ft_strcmp(char *s1, char *s2)
{
	if (!s1 || !s2)
		return (INT_MIN);
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

char	*ft_strdup(char *s1)
{
	char	*str;
	size_t	len_s1;
	int		index;

	len_s1 = ft_strlen(s1);
	str = my_malloc((len_s1 + 1) * (sizeof(char)), 1);
	if (!str)
		return (NULL);
	index = -1;
	while (s1[++index])
		str[index] = s1[index];
	str[index] = 0;
	return (str);
}