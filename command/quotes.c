/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:33:42 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/04/17 03:09:50 by bel-oirg         ###   ########.fr       */
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

char	*add_c(char *str, char c)
{
	char	*new;
	char	*save;
	
	// if (!str || !c)
	// 	return (NULL);
	new = malloc(ft_strlen(str) + 2);
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
	(*index)++;
	while (raw[*index])
	{
		
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
		else if (raw[*index] == '"')
			return (new);
		else 
			new = add_c(new, raw[(*index)++]);
	}
	return (new);
}

char	*s_q(char *raw, int *index)
{
	char	*clean;
	int		ind;

	ind = -1;
	clean = my_malloc(ft_strlen(raw - 1), 1);
	if (count_c(raw, '\'') % 2)
	{
		printf("unclosed quote\n");
		exit (1);
	}
	(*index)++;
	while (raw[*index])
	{
		// printf("%s\n", &raw[*index]);
		if (raw[(*index)] == '\'')
		{
			(*index)++;
			clean[++ind] = 0;
			return (clean);
		}
		// if (raw[(*index)] != '\'')
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