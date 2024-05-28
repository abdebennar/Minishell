/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:53:26 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/05/28 16:34:55 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_execve(t_node *node)
{
	char	*path;

	sig_allow();
	if (!node->cmd)
		exit(0);
	if (!(node)->cmd[0])
		(put_str_err(NOCMD_ERR, node->cmd[0]), exit (127));
	path = add_path((node)->cmd[0]);
	execve(path, (node)->cmd, environ);
	exit (exec_err(errno, path, node->cmd[0]));
}

void	_exec_(t_node *node)
{
	int	forked;
	int	bk_fd[2];
	int	exit_stat;

	bk_fd[0] = dup(0);
	bk_fd[1] = dup(1);
	node->cmd = _expanding_(&node);
	if (_redirections_(&node) || is_builtin(node))
		return (reset_fds(&node, bk_fd));
	forked = fork();
	if (forked < 0)
	{
		close(bk_fd[0]);
		close(bk_fd[1]);
		perror("fork on _exec_");
		exit(1);
	}
	if (!forked)
		my_execve(node);
	waitpid(forked, &exit_stat, 0);
	_setenv("?", ft_itoa(_exit_stat_(exit_stat)));
	reset_fds(&node, bk_fd);
}

void	_exec_arch_(t_node *node)
{
	t_token	tok;

	if (!node)
		return ;
	tok = (node)->tok;
	if (tok == OR)
		_or_(node);
	else if (tok == AND)
		_and_(node);
	else if (tok == PIPE)
		_pipe_(node);
	else if (tok == NOT)
		_exec_(node);
}
