/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:53:26 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/04/15 17:56:05 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*add_path(char *cmd)
{
	int		index;
	char	*path;
	char	*out;
	char	**path_v;

	if (is_it_in(cmd, '/'))
		return (cmd);
	index = -1;
	path = getenv("PATH");
	(!path) && (perror("PATH not found"), 0);
	path_v = ft_split(path, ":");
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

void    _exec_(t_node *node)
{
    int forked;

    forked = fork();
    if (forked < 0)
        perror("fork");
    if (!forked)
    {
        execve(add_path(node->cmd[0]), node->cmd, NULL);
        perror("Command not found");
    }
}