/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 01:44:16 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/05/05 14:57:19 by abennar          ###   ########.fr       */
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
//reme to check .*.c
//test  l****l  and the pattern l*l

char	*b_wildcard_(char *pattern)
{
    struct dirent   *entry;
    char            *extracted;
    DIR             *dir;

    dir = opendir(".");
    if (!dir)
        return (perror("opendir"), NULL);
    extracted = NULL;
    while (1)
    {
        entry = readdir(dir);
        if (!entry)
            break;
        if (check_pattern(entry->d_name, pattern))
        {
			if (*(entry->d_name) == '.' && *pattern != '.') //I changed this check it
				continue ;
            if (extracted)
                extracted = ft_strjoin(extracted, " ", 0); // FIX 
            extracted = ft_strjoin(extracted, entry->d_name, 0);
        }
    }
	return (extracted);
}

void	_wildcard_(t_node **node)
{
	int	index;

	index = -1;
	while ((*node)->cmd[++index])
		(*node)->cmd[index] = b_wildcard_((*node)->cmd[index]);
}

// int main()
// {
// 	char pattern[] = "*/*.c";
	
//     printf("%s\n", b_wildcard_(pattern));
// }