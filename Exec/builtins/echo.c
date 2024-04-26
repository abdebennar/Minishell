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

#include "../Include/minishell.h"

static int  check_flags(char *cmd)
{
    if (!cmd || !*cmd)
        return (0);
    if (*cmd == '-')
    {
		cmd++;
        while (*cmd == 'n')
		{
        	if (!*(++cmd))
           		return (1);
		}
    }
    return (0);
}

void    _echo_(t_node *node)
{
    int		flag;
	char	**cmd;

    flag = 0;
	cmd = node->cmd;
	cmd++;
    while (check_flags(*(cmd)))
	{
		printf("inside checker");
        flag = 1;
		cmd++;
	}
    while(*cmd)
    {
        printf("%s", *(cmd++));
        if (*cmd)
            printf(" ");
    }
    if (!flag)
        printf("\n");
}

// #include <string.h>

// int main()
// {
// 	char **cmd;

// 	cmd = malloc(sizeof(char *) * 4);
// 	// const char *ss = "heel";

// 	cmd[0] = strdup("nnnnnnnnnnnnn");
// 	cmd[1] = strdup("nnnnn");
// 	cmd[2] = strdup("fuck you");
// 	cmd[3] = NULL;

// 	_echo_(cmd);
// }