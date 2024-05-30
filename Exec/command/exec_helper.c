/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 21:35:07 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/05/30 23:30:24 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_exit_stat_(int oldx)
{
	if (WIFSIGNALED(oldx))
	{
		if (WTERMSIG(oldx) == SIGINT)
			return (write(2, "\n", 1), 128 + SIGINT);
		else if (WTERMSIG(oldx) == SIGQUIT)
			return (write(2, "Quit: 3\n", 8), 128 + SIGQUIT);
		else
			return (WTERMSIG(oldx) + 128);
	}
	else if (WIFEXITED(oldx))
		return (WEXITSTATUS(oldx));
	return (0);
}

void	reset_fds(t_node **node, int *bk_fd)
{
	dup2(bk_fd[0], STDIN_FILENO);
	close(bk_fd[0]);
	if (node && *node && (*node)->fd[0] != 0)
		close((*node)->fd[0]);
	dup2(bk_fd[1], STDOUT_FILENO);
	close(bk_fd[1]);
	if ((node && *node && (*node)->fd[1] != 1))
		close((*node)->fd[1]);
}

bool	b_is_builtin(t_node *node, char *str)
{
	if (!ft_strcmp(str, "cd"))
		return (_cd_(node), true);
	else if (!ft_strcmp(str, "echo"))
		return (_echo_(node), true);
	else if (!ft_strcmp(str, "env"))
		return (_env_(), true);
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

bool	check_builtin(char *str)
{
	if (!ft_strcmp(str, "cd"))
		return ( true);
	else if (!ft_strcmp(str, "echo"))
		return (true);
	else if (!ft_strcmp(str, "env"))
		return (true);
	else if (!ft_strcmp(str, "exit"))
		return (true);
	else if (!ft_strcmp(str, "export"))
		return ( true);
	else if (!ft_strcmp(str, "pwd"))
		return (true);
	else if (!ft_strcmp(str, "unset"))
		return (true);
	return (false);
}


bool	is_builtin(t_node *node)
{
	int		index;
	char	**splited;

	if (!node || !(node->cmd) || !(node->cmd[0]))
		return (false);
	index = -1;
	splited = NULL;
	if (check_builtin(node->cmd[0]))
	{
		while (node->cmd[++index])
		{
			find_replace(node->cmd[index], '\v', ' ');
			find_replace(node->cmd[index], '\177', ' ');
			// find_replace(node->cmd[index], '\a', ' ');
			printf("current : %s\n", node->cmd[index]);
			splited = concatenate_strings(splited, ft_split(node->cmd[index], "\a", 0));
		}
		node->cmd = splited;
		return (b_is_builtin(node, node->cmd[0]));
	}
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
		if (!access(out, F_OK))
			return (out);
	}
	return (NULL);
}
