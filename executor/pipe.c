/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 03:57:42 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/04/05 05:46:42 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	err(int *fd_in, int *fd_out)
{
	(fd_in) && (close(*fd_in), 0);
	(fd_out) && (close(*fd_out), 0);
	my_malloc(0, 0);
}

void	w_err(char *str)
{
	write(2, "[-] ", 5);
	write(2, str, ft_strlen(str));
	write(2, "\n", 2);
	my_malloc(0, 0);
}

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
	(!path) && (w_err("PATH not found"), 0);
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

int	buddha(char **cmd)
{
	int	fd[2];
	int	forked;

	(pipe(fd) < 0) && (perror("pipe"), my_malloc(0, 0), 0);
	forked = fork();
	(forked < 0) && (close(fd[0]), close(fd[1]), perror("fork"), 0);
	if (!forked)
	{
		close(fd[0]);
		(dup2(fd[1], STDOUT_FILENO) < 0) && (perror("dup2"), my_malloc(0, 0));
		close(fd[1]);
		execve(add_path(cmd[0]), cmd, NULL);
		w_err("Command not found");
	}
	else
	{
		close(fd[1]);
		(dup2(fd[0], STDIN_FILENO) < 0) && (perror("dup2"), my_malloc(0, 0), 0);
		close(fd[1]);
	}
	return (0);
}

void	_pipe_(int argc, char *argv[], t_node *cmd)
{
	int	fd_in;
	int	fd_out;

	fd_in = open(argv[1], O_RDONLY, 0777);
	fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	(fd_in < 0 || fd_out < 0) && (perror("open"), my_malloc(0, 0));
	
	if (dup2(fd_in, STDIN_FILENO) < 0)
		(perror("dup2"), err(&fd_in, &fd_out), 0);
	close(fd_in);
	
	(buddha(cmd->lchild->cmd)) && (err(NULL, &fd_out), 0);
	
	if (dup2(fd_out, STDOUT_FILENO) < 0)
		(perror("dup2"), err(NULL, &fd_out), 0);
	close(fd_out);
	
	execve(add_path(cmd->rchild->cmd[0]), cmd->rchild->cmd, NULL);
	w_err("Command not found");
}