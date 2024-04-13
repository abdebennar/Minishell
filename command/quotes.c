/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:33:42 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/04/13 19:37:34 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_alphanum(char c)
{
	return ((c >= 'a' && c <= 'z')
			|| (c >= 'A' && c <= 'Z')
			|| (c >= '0' && c <= '9'));
}

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

char	*add_c(char *str, char c)
{
	char	*new;
	char	*save;
	
	if (!str || !c)
		return (NULL);
	new = malloc(ft_strlen(str) + 2);
	save = new;
	while (*str)
		*new++ = *str++;
	*new++ = c;
	*new = 0;
	return (save);
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

char	*d_q(char *raw, int *index)
{
	char	*tmp;
	char	*new;
	char	*possible;
	size_t		ident;

	(*index)++;
	new = ft_strdup("");
	tmp = malloc(ft_strlen(raw) + 2);
	while (raw[*index] != '"')
	{
		if (!raw[*index])
		{
			printf("unclosed quote\n");
			return (NULL);
		}
		if (raw[*index] == '$')
		{
			ident = only_identifier(&raw[*index + 1]);
			if (ident)
			{
				possible = malloc(ident + 1);
				ft_strncpy(possible, &raw[*index + 1], ident);
				if (getenv(possible)) //you can remove this
					new = ft_strjoin(new, getenv(possible));
				index += ident + 1;
			}
		}
		else 
			new = add_c(new, raw[*(index++)]);
	}
	return (new);
}

char	*s_q(char *raw)
{
	char	*clean;
	int		index;

	index = -1;
	clean = my_malloc(ft_strlen(raw - 1), 1);
	raw++;
	while (*raw != '\'')
	{
		if (!*raw)
		{
			printf("unclosed quote\n");
			return (NULL);
		}
		clean[++index] = *raw++;
	}
	clean[++index] = 0;
	return (clean);
}

// char *clean_str(char *str)
// {
// 	char	*clean;
// 	int		index;
	
// 	index = -1;
// 	while (str[++index])
// 	{
// 		if (str[index] == '"')
// 			d_q(str, ++index);
// 	}
// }
int main()
{
	char *raw;
	int	index;

	index = 0;
	raw = ft_strdup("\"$SHELL\"");
	printf("|||%s|||\n", d_q(raw, &index));
}