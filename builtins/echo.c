/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 11:17:09 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/04/12 11:17:09 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int  check_flags(char *cmd)
{
    if (!*cmd)
        return (0);
    if (*cmd == '-')
    {
        while (*cmd == 'n')
            cmd++;
        if (!*cmd)
            return (1);
    }
    return (0);
}

void    _echo_(char **cmd)
{
    int flag;

    flag = 0;
    while (check_flags(*(++cmd)))
        flag = 1;
    while(*cmd)
    {
        printf("%s", *(cmd++));
        if (*cmd)
            printf(" ");
    }
    if (!flag)
        printf("\n");
}