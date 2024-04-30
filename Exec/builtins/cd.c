/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 11:17:06 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/04/12 11:17:06 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void    _cd_(t_node *node)
{
    char    old_pwd[PATH_MAX];
    char    pwd[PATH_MAX];
    int 	exit_err;
	char	**cmd;

	cmd = node->cmd;
    if (!cmd[1])
        cmd[1] = getenv("HOME");
    else if (!ft_strcmp(cmd[1], "-"))
	{
        cmd[1] = getenv("OLDPWD");
		printf("%s\n", cmd[1]);
	}
    getcwd(old_pwd, PATH_MAX);
    exit_err = chdir(cmd[1]);
    if (exit_err)
    {
        perror(NULL);
        exit(exit_err);
    }
    getcwd(pwd, PATH_MAX);
	_setenv("OLDPWD", old_pwd);
	_setenv("PWD", pwd);
}
