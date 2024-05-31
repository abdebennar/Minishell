/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:53:26 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/05/31 23:46:25 by bel-oirg         ###   ########.fr       */
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

char	**trim_cmd(char **cmd, int raw_len)
{
	char	**w_cmd;
	char	**splited;
	int		v_index;

	(1) && (w_cmd = NULL, v_index = -1);
	while (cmd && ++v_index < raw_len)
	{
		find_replace(cmd[v_index], '\177', '\a');
		splited = ft_split(cmd[v_index], "\a", 0);
		if (splited && !splited[0])
		{
			splited = my_malloc(sizeof(char *) * 2, 1, 0);
			splited[0] = ft_strdup("", 0);
			splited[1] = NULL;
		}
		w_cmd = concatenate_strings(w_cmd, splited);
	}
	return (w_cmd);
}

void	my_execve(t_node *node, int raw_len)
{
	char	*path;

	sig_allow();
	node->cmd = trim_cmd(node->cmd, raw_len);
	if (!(node->cmd))
		exit(0);
	reset_sp(node->cmd);
	if (!((node)->cmd[0]) || !((node)->cmd[0][0]))
		(put_str_err(NOCMD_ERR, node->cmd[0]), exit(127));
	if (!ft_strcmp("echo", node->cmd[0]))
		return (_echo_(node), exit(0));
	path = add_path((node)->cmd[0]);
	execve(path, (node)->cmd, environ);
	exit (exec_err(errno, path, node->cmd[0]));
}

void	_exec_(t_node *node)
{
	int	forked;
	int	bk_fd[2];
	int	exit_stat;
	int	raw_len;

	bk_fd[0] = dup(0);
	bk_fd[1] = dup(1);
	raw_len = count_strings(node->cmd);
	node->cmd = _expanding_(&node);
	if (_redirections_(&node) || is_builtin(node, raw_len))
		return (reset_fds(&node, bk_fd));
	forked = fork();
	if (forked < 0)
	{
		close(bk_fd[0]);
		close(bk_fd[1]);
		perror("fork");
		exit(1);
	}
	if (!forked)
		my_execve(node, raw_len);
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
