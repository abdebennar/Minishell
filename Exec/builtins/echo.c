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

static int	check_flags(char *cmd)
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

void	_echo_(t_node *node)
{
	int		flag;
	char	**cmd;

	flag = 0;
	cmd = node->cmd;
	cmd++;
	while (check_flags(*(cmd)))
	{
		flag = 1;
		cmd++;
	}
	while(*cmd)
    {
        write(1, *cmd, ft_strlen(*cmd));
        if (*(++cmd))
            write(1, " ", 1);
    }
	if (!flag)
		write(1, "\n", 1);
	_setenv("?", ft_itoa(0));
}
