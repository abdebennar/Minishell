/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:53:26 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/05/05 20:49:33 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	(!path) && (perror("PATH not found"), 0);
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

static bool	is_builtin(t_node *node)
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

static void	reset_fds(t_node **node, int *bk_fd)
{
	if ((*node)->fd[0] != 0)
	{
		close((*node)->fd[0]);
		dup2(bk_fd[0], STDIN_FILENO);
		close(bk_fd[0]);	
	}
	if ((*node)->fd[1] != 1)
	{
		close((*node)->fd[1]);
		dup2(bk_fd[1], STDOUT_FILENO);
		close(bk_fd[1]);
	}
}

void	my_execve(t_node *node)
{
	extern char	**environ;

	execve(add_path((node)->cmd[0]), (node)->cmd, environ);
	printf("bash: %s: Command not found bitch\n", (node)->cmd[0]);
	if (errno == ENOENT)
		exit(127);
	if (errno == EACCES)
		exit(126);
	exit(1);
}

void    _exec_(t_node *node)
{
    int			forked;
	int			bk_fd[2];
	int			out_exit;

	bk_fd[0] = dup(STDOUT_FILENO);
	bk_fd[1]  = dup(STDIN_FILENO);
	_expanding_(&node);
	if (!(node)->cmd[0] || _redirections_(&node) || is_builtin(node))
		return ;
    forked = fork();
    if (forked < 0)
	{
        perror("fork");
		return ;
	}
    if (!forked)
		my_execve(node);
	waitpid(forked, &out_exit, 0);
	_setenv("?", ft_itoa(WEXITSTATUS(out_exit)));
	reset_fds(&node, bk_fd);
}

void	_exec_arch_(t_node *node)
{
	t_token	tok;
	int		exit_stat;
	
	if (!node)
		return ;
	exit_stat = 1;
	tok = (node)->tok;
	if (tok == OR)
		_or_(node);
	else if (tok == AND)
		_and_(node);
	else if (tok == PIPE)
		_pipe_(node);
	else if (tok == NOT)
		_exec_(node);
	else
		perror("No token provided");
}
