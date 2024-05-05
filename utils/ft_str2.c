/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 02:44:18 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/05/05 16:21:52 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	doc_strcmp(char *s1, char *s2)
{
	if (!*s2 && !s1)
		return (0);
	if (!s2 || !s1)
		return (1);
	while (*s1 == *s2 && *s1)
	{
		s1++;
		s2++;
	}
	if (*s1 == '\n' && !*s2)
		return (0);
	return (*s1 - *s2);
}

char    *ft_strcpy(char *s1, char *s2)
{
	int	i;
	
	i = 0;
	while (s2[i])
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = s2[i];
	return (s1);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0 ;
	while ((s1[i] || s2[i]) && n > i)
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

char	*ft_strdup_len(char *s1, int len, int group)
{
	char	*str;
	size_t	len_s1;
	int		index;

	len_s1 = ft_strlen(s1);
	str = my_malloc((len + 1) * (sizeof(char)), 1, group);
	if (!str)
		return (NULL);
	index = -1;
	while (s1[++index] && len--)
		str[index] = s1[index];
	str[index] = 0;
	return (str);
}

int	find_c(char *str, char c)
{
	while (str && *str)
		if (*(str++) == c)
			return (1);
	return (0);
}
