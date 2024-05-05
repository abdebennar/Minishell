/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 01:44:16 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/05/05 23:26:07 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool check_pattern(char* s, char* p) 
{
    char *s_star = NULL, *p_star = NULL;
    
    while (*s != '\0')
	{
        if (*p == *s)
		{
            s++;
            p++;
        }
        else if (*p == '*')
		{
            p_star = p;
            s_star = s;
            p++;
        }
        else if (p_star != NULL)
		{
            p = p_star + 1;
            s = ++s_star;
        }
        else 
            return false;
    }
    while (*p == '*')
        p++;
    return *p == '\0';
}

char	*_wildcard_(char *pattern)
{
	struct dirent	*entry;
    char			*extracted;
    DIR				*dir;

    dir = opendir(".");
	if (!pattern || !*pattern)
		return (NULL);
    if (!dir)
        return (perror("opendir"), NULL);
    extracted = NULL;
    while (1)
    {
        entry = readdir(dir);
        if (!entry)
            break ;
        if (check_pattern(entry->d_name, pattern))
        {
			if (*(entry->d_name) == '.' && *pattern != '.')
				continue ;
            if (extracted)
                extracted = ft_strjoin(extracted, " ", 0);
            extracted = ft_strjoin(extracted, entry->d_name, 0);
        }
    }
	if (extracted)
		return (extracted);
	return (pattern);
}

// cd ../current/*.c 