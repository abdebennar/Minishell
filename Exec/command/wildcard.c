/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 01:44:16 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/04/28 10:26:02 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool check_pattern(char *str, char *pattern)
{
    if (!*pattern)
        return (!*str);
		
	if (*pattern == '*')
		return ((check_pattern(str, pattern + 1) ||
		(*str && check_pattern(str + 1, pattern))));
		
   else if (*str == *pattern)
        return check_pattern(str + 1, pattern + 1);
    return (false);
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
// 	char pattern[] = "../command/.*";
	
//     printf("%s\n", b_wildcard_(pattern));
// }