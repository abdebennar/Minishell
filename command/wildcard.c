/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 01:44:16 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/04/18 02:31:18 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool check_pattern(char *str, char *pattern)
{
    if (!*str && !*pattern)
        return true;

//     while (*pattern == '*' && *(pattern + 1) == '*')
//         pattern++;
//     if (!*str && *pattern == '*' && !*(pattern + 1))
//         return true;
//     if (*str == *pattern)
//         return check_pattern(str + 1, pattern + 1);
//     if (*pattern == '*')
//         return (check_pattern(str + 1, pattern)
// 		|| check_pattern(str, pattern + 1));
//     return false;
// }

bool isMatch(const char *text, const char *pattern)
{
    if (*pattern == '\0')
        return *text == '\0';

    if (*pattern == '*')
	{
        while (*text != '\0')
		{
            if (isMatch(text, pattern + 1))
                return true;
            text++;
        }
        return isMatch(text, pattern + 1);
    }
	else if (*pattern == *text)
        return *text != '\0' && isMatch(text + 1, pattern + 1);
    return false;
}


// char	*_wildcard_(char *pattern)
// {
//     struct dirent   *entry;
//     char            *extracted;
//     DIR             *dir;

//     dir = opendir(".");
//     if (!dir)
//     {
//         perror("opendir");
//         return (NULL);
//     }
//     extracted = NULL;
//     while (1)
//     {
//         entry = readdir(dir);
//         if (!entry)
//             break;
//         if (check_pattern(entry->d_name, pattern))
//         {
//             if (extracted)
//                 extracted = ft_strjoin(extracted, " ");
//             extracted = ft_strjoin(extracted, entry->d_name);
//         }
//     }
// 	return (extracted);
// }

int main()
{
    if (isMatch("quoe", "*q*ed"))
        printf("YEpA\n");
    // _wildcard_();
}