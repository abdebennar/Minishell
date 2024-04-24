/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:53:26 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/04/24 04:54:35 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

static char	*add_path(char *cmd)
{
	int		index;
	char	*path;
	char	*out;
	char	**path_v;

	if (find_c(cmd, '/'))
		return (cmd);
	index = -1;
	path = getenv("PATH");
	(!path) && (perror("PATH not found"), 0);
	path_v = ft_split(path, ":", 0); // FIX add the group
	index = -1;
	while (path_v[++index])
	{
		out = ft_strjoin(path_v[index], "/", 0);
		out = ft_strjoin(out, cmd, 0);
		if (!access(out, X_OK))
			return (out);
	}
	return (NULL);
}

bool	is_builtin(char *str)
{
	if (!ft_strcmp(str, "cd"))
		return (1);
	else if (!ft_strcmp(str, "echo"))
		return (1);
	else if (!ft_strcmp(str, "env"))
		return (1);
	else if (!ft_strcmp(str, "exit"))
		return (1);
	else if (!ft_strcmp(str, "export"))
		return (1);
	else if (!ft_strcmp(str, "pwd"))
		return (1);
	else if (!ft_strcmp(str, "unset"));
		return (1);
	return (0);
}

void    _exec_(t_node **node)
{
    int forked;

	_expanding_(node);
	_wildcard_(node);
	_redirection_(node);
    forked = fork();
    if (forked < 0)
        perror("fork");
    if (!forked)
    {
		if (is_builtin((*node)->cmd[0]))
			exec_builtin((*node));
		else
		{
			execve(add_path((*node)->cmd[0]), (*node)->cmd, NULL);
			perror("Command not found");
		}
    }
}