/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 09:51:05 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/04/18 14:36:50 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	_pwd_(char **cmd)
{
	char cwd[PATH_MAX];
	
	if (cmd[1])
	{
		printf("pwd: too many arguments");
		exit(1);
	}
	getcwd(cwd, PATH_MAX);
	printf("%s\n", cwd);
	exit(0);
}
