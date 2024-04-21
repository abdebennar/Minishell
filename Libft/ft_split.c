/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:47:24 by abennar           #+#    #+#             */
/*   Updated: 2024/04/21 17:30:08 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	*free_words(char **words, int i)
{
	while (i--)
		free(words[i]);
	free(words);
	return (NULL);
}

static int	count_words(const char *s, char c)
{
	int		count;
	size_t	i;

	count = 0;
	if (s[0] != c && s[0])
		count++;
	i = 1;
	while (i < ft_strlen(s))
	{
		if (s[i] != c && s[i - 1] == c)
			count++;
		i++;
	}
	return (count);
}

static char	*ft_strcut(const char *s, char c, int *index)
{
	char	*str;
	int		l;
	int		i;

	l = 0;
	i = 0;
	while (s[l] && s[l] != c)
		l++;
	str = (char *)my_malloc(sizeof(char) * (l + 1), ALLOC);
	if (!str)
		return (NULL);
	while (i < l)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	*index += i;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**words;
	int		index;
	int		c_words;
	int		i;

	index = 0 ;
	i = 0;
	if (!s)
		return (NULL);
	c_words = count_words(s, c);
	words = (char **)my_malloc((c_words + 1) * sizeof(char *), ALLOC);
	if (!words)
		return (NULL);
	while (i < c_words && s[index] != '\0')
	{
		while (s[index] == c)
			index++;
		words[i] = ft_strcut((s + index), c, &index);
		if (!words[i])
			return (free_words(words, i));
		i++;
	}
	words[i] = (NULL);
	return (words);
}
