/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:49:19 by abennar           #+#    #+#             */
/*   Updated: 2024/05/15 17:49:19 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_cd_home_last_(char **cmd)
{
	if (!cmd[1])
		cmd[1] = getenv("HOME");
	else if (!ft_strcmp(cmd[1], "-"))
	{
		cmd[1] = getenv("OLDPWD");
		if (cmd[1])
			printf("%s\n", cmd[1]);
		else
		{
			put_err("bash: cd: OLDPWD not set\n");
			_setenv("?", ft_itoa(1));
			return (1);
		}
	}
	return (0);
}

void	_cd_(t_node *node)
{
	char	old_pwd[PATH_MAX];
	char	pwd[PATH_MAX];
	int		exit_err;
	char	*err;
	char	**cmd;

	cmd = node->cmd;
	if (_cd_home_last_(cmd))
		return ;
	getcwd(old_pwd, PATH_MAX);
	exit_err = chdir(cmd[1]);
	if (exit_err)
	{
		perror("bash: cd: ");
		_setenv("?", ft_itoa(1));
		return ;
	}
	err = getcwd(pwd, PATH_MAX);
	if (!err)
		perror("cd: error retrieving current directory");
	_setenv("OLDPWD", old_pwd);
	_setenv("PWD", pwd);
	_setenv("?", ft_itoa(0));
}
