/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 09:51:05 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/04/24 05:24:06 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	_pwd_(t_node *node)
{
	char cwd[PATH_MAX];
	char	**cmd;

	cmd = node->cmd;
	if (cmd[1])
	{
		printf("pwd: too many arguments");
		exit(1);
	}
	getcwd(cwd, PATH_MAX);
	printf("%s\n", cwd);
	exit(0);
}
