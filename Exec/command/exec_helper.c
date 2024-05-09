/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 21:35:07 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/05/08 23:01:46 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_exit_stat_(int oldx)
{
	if (WIFSIGNALED(oldx))
	{
		if (WTERMSIG(oldx) == SIGINT)
			return (printf("\n"), 128 + SIGINT);
		else if (WTERMSIG(oldx) == SIGQUIT)
			return (printf("Quit: 3\n"), 128 + SIGQUIT);
		else 
			return (WTERMSIG(oldx) + 128);
	}
	else if (WIFEXITED(oldx))
		return (WEXITSTATUS(oldx));
	return (0);
}

void	reset_fds(t_node **node, int *bk_fd)
{
		// dup2(bk_fd[0], STDIN_FILENO);

	dup2(bk_fd[0], STDIN_FILENO);
	close(bk_fd[0]);	
	if ((*node)->fd[0] != 0)
		close((*node)->fd[0]);
	dup2(bk_fd[1], STDOUT_FILENO);
	close(bk_fd[1]);
	if ((*node)->fd[1] != 1)
		close((*node)->fd[1]);
}

bool	is_builtin(t_node *node)
{
	char *str;

	str = node->cmd[0];
	if (!ft_strcmp(str, "cd"))
		return (_cd_(node), true);
	else if (!ft_strcmp(str, "echo"))
		return (_echo_(node), true);
	else if (!ft_strcmp(str, "env"))
		return (_env_(node), true);
	else if (!ft_strcmp(str, "exit"))
		return (_exit_(node), true);
	else if (!ft_strcmp(str, "export"))
		return (_export_(node), true);
	else if (!ft_strcmp(str, "pwd"))
		return (_pwd_(), true);
	else if (!ft_strcmp(str, "unset"))
		return (_unset_(node), true);
	return (false);
}

char	*add_path(char *cmd)
{
	int		index;
	char	*path;
	char	*out;
	char	**path_v;

	if (!cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (cmd);
	index = -1;
	path = getenv("PATH");
	if (!path)
		return (NULL);
	path_v = ft_split(path, ":", 0);
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
