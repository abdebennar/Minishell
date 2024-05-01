/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 06:21:55 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/05/01 11:18:05 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

int	ft_strlen(const char *str)
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

char	*ft_strdup(char *s1, int group)
{
	char	*str;
	size_t	len_s1;
	int		index;

	len_s1 = ft_strlen(s1);
	str = my_malloc((len_s1 + 1) * (sizeof(char)), 1, group);
	if (!str)
		return (NULL);
	index = -1;
	while (s1[++index])
		str[index] = s1[index];
	str[index] = 0;
	return (str);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)(s + i));
	return (NULL);
}

char	*ft_substr(char *str, unsigned int start, size_t len, int group)
{
	int		i;
	char	*s_str;

	i = 0 ;
	if (!str)
		return (NULL);
	if ((int)start > ft_strlen(str))
		return (ft_strdup("", group));
	if ((int)len > ft_strlen(str + start))
		len = ft_strlen(str + start);
	s_str = my_malloc(sizeof(char) * len + 1, 1, group);
	if (!s_str)
		return (NULL);
	while (len--)
	{
		s_str[i] = (start + str)[i];
		i++;
	}
	s_str[i] = '\0';
	return (s_str);
}
