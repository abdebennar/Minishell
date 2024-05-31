/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 04:00:45 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/06/01 00:45:19 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_right_(t_node **node)
{
	t_redir	*alter;
	int		fd;

	fd = 1;
	alter = (*node)->redir;
	while (alter)
	{
		if (alter->tok == OUT)
		{
			if (fd > 1)
				close(fd);
			fd = open(alter->file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		}
		else if (alter->tok == APPEND)
		{
			if (fd > 1)
				close(fd);
			fd = open(alter->file, O_WRONLY | O_APPEND | O_CREAT, 0644);
		}
		if (fd < 0)
			return (perror("open"), -1);
		alter = alter->next;
	}
	(*node)->fd[1] = fd;
	return (0);
}

void	find_replace2(char *str, char find, char rep)
{
	if (!str)
		return ;
	while (*str)
	{
		if (*str == find && *(str + 1) == find)
		{
			str++;
			*str = rep;
		}
		str++;
	}
}

int	heredoc_file(char *content)
{
	int		fd;
	char	*line;
	char	*file_name;
	char	**her_cnt;
	char	*new_cnt;

	file_name = random_f();
	new_cnt = NULL;
	if (content)
	{
		her_cnt = ft_split(content, "\v", 0);
		while (*her_cnt)
		{
			line = expand_heredoc(*her_cnt);
			new_cnt = ft_strjoin(new_cnt, line, 0);
			line = NULL;
			her_cnt++;
		}
	}
	fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0777);
	write(fd, new_cnt, ft_strlen(new_cnt));
	close(fd);
	fd = open(file_name, O_RDWR);
	return (unlink(file_name), fd);
}

int	_left_(t_node **node)
{
	t_redir	*alter;
	int		fd;

	fd = 0;
	alter = (*node)->redir;
	while (alter)
	{
		if (alter->tok == IN)
		{
			if (fd > 0)
				close(fd);
			fd = open(alter->file, O_RDONLY, 0644);
		}
		else if (alter->tok == HEREDOC)
		{
			if (fd > 0)
				close(fd);
			fd = heredoc_file(alter->content);
		}
		if (fd < 0)
			return (perror("open"), -1);
		alter = alter->next;
	}
	(*node)->fd[0] = fd;
	return (0);
}

int	_redirections_(t_node **node)
{
	t_redir	*alter;

	alter = (*node)->redir;
	while (alter)
	{
		if (alter->tok != HEREDOC)
			alter->file = alter_exp(alter->file);
		if (!alter->file)
			return (_setenv("?", "1"), -1);
		if (alter->fd == -1)
			return (-1);
		alter = alter->next;
	}
	if (_left_(node) || _right_(node))
		return (_setenv("?", "1"), -1);
	return (redir_io(*node));
}
