/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:53:26 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/04/23 18:21:15 by abennar          ###   ########.fr       */
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
	path_v = ft_split(path, ":"); // FIX add the group
	index = -1;
	while (path_v[++index])
	{
		out = ft_strjoin(path_v[index], "/");
		out = ft_strjoin(out, cmd);
		if (!access(out, X_OK))
			return (out);
	}
	return (NULL);
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
        execve(add_path((*node)->cmd[0]), (*node)->cmd, NULL);
        perror("Command not found");
    }
}