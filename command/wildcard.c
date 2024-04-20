/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 01:44:16 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/04/20 01:32:55 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

char	*_wildcard_(char *pattern)
{
    struct dirent   *entry;
    char            *extracted;
    DIR             *dir;

    dir = opendir(".");
    if (!dir)
    {
        perror("opendir");
        return (NULL);
    }
    extracted = NULL;
    while (1)
    {
        entry = readdir(dir);
        if (!entry)
            break;
        if (check_pattern(entry->d_name, pattern))
        {
            if (extracted)
                extracted = ft_strjoin(extracted, "\t");
            extracted = ft_strjoin(extracted, entry->d_name);
        }
    }
	return (extracted);
}

int main()
{
    // if (check_pattern("quoe", "*q*ye"))
    //     printf("YEpA\n");
    printf("%s\n", _wildcard_("*.c"));
}
