/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:53:26 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/05/07 11:21:55 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	 my_execve(t_node *node)
{
	extern char	**environ;

	sig_allow();
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
	{
		dup2(bk_fd[1], STDIN_FILENO);
		return ;
	}
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
