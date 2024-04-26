/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:53:26 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/04/26 02:47:45 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		return (_pwd_(node), true);
	else if (!ft_strcmp(str, "unset"))
		return (_unset_(node), true);
	return (false);
}

//TODO env -> **str to give it to execve 
//TODO add an architecture based on token

void    _exec_(t_node **node)
{
    int forked;
	
	_expanding_(node);
	// _redirection_(node);
	if (is_builtin(*node))
		return ;
    forked = fork();
    if (forked < 0)
        perror("fork");
    if (!forked)
    {
		//TODO till using NULL not env
		execve(add_path((*node)->cmd[0]), (*node)->cmd, NULL);
		perror("Command not found bitch");
    }
}

void	_exec_arch_(t_node **node)
{
	t_token	tok;
	int		exit_stat;
	
	tok = (*node)->tok;
	exit_stat = 1;
	if (tok == OR)
		_or_(*node, exit_stat);
	else if (tok == AND)
		_and_(*node, exit_stat);
	else if (tok == PIPE)
		_pipe_(*node);
	else if (tok == NOT)
		_exec_(node);
	else
		perror("No token provided");
}

