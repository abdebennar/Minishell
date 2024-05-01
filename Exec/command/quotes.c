/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:33:42 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/05/01 10:55:26 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	only_identifier(char *str)
{
	char *save;
	
	save = str;
	if (!((*str >= 'a' && *str <= 'z')
		|| (*str >= 'A' && *str <= 'Z') || (*str == '_')))	
		return (0);
	while(*str)
	{
		if (!(is_alphanum(*str) || (*str == '_')))
			break ;
		str++;
	}
	return ((int)(str - save));
}

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		++i;
	}
	while (i < n)
		dest[i++] = '\0';
	return (dest);
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

char	*d_q(char *raw, int *index)
{
	char	*new;
	char	*possible;
	size_t		ident;

	new = NULL;
	if (count_c(raw, '"') % 2)
	{
		printf("unclosed quote\n");
		exit(1);
	}
	if (raw[*index] == '"')
		(*index)++;
	while (raw[*index])
	{
		if (raw[*index] == '$')
		{
			// printf("checked $\n");
			ident = only_identifier(&raw[*index + 1]);
			if (ident)
			{
				possible = malloc(ident + 1);
				ft_strncpy(possible, &raw[*index + 1], ident);
				if (getenv(possible)) //you can remove this
					new = ft_strjoin(new, getenv(possible), 0);
				*index += ident + 1;
			}
		}
		else if (raw[*index] == '"' || !raw[*index])
			break ;
		else 
			new = add_c(new, raw[(*index)++], 0);
	}
	return (new);
}

char	*s_q(char *raw, int *index)
{
	char	*clean;
	int		ind;

	ind = -1;
	clean = my_malloc(ft_strlen(raw - 1), 1, 0); // FIX add the group
	if (count_c(raw, '\'') % 2)
	{
		printf("unclosed quote\n");
		exit (1);
	}
	(*index)++;
	while (raw[*index])
	{
		if (raw[(*index)] == '\'')
		{
			(*index)++;
			clean[++ind] = 0;
			return (clean);
		}
		clean[++ind] = raw[(*index)];
		(*index)++;
	}
	clean[++ind] = 0;
	return (clean);
}

// int main()
// {
// 	char *raw;
// 	int	index;

// 	printf("HELLLLL\n");
// 	index = 0;
// 	raw = ft_strdup("\"$SHELL\"");
// 	printf("|||%s|||\n", d_q(raw, &index));
// }