/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 05:50:24 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/04/23 00:03:35 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*random_f(void)
{
	char	*file_name;
	int		file_len;
	int		fd_rd;
	int		fd_tmp;

	file_len = 16;
	file_name = my_malloc(file_len + 1, 1);


	
	fd_rd = open("/dev/urandom", O_RDONLY, 0777);
	(fd_rd < 0) && (w_err("cannot open /dev/urandom"), 0);
	read(fd_rd, file_name, file_len);
	close(fd_rd);
	file_name[file_len] = 0;


	
	

	fd_tmp = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd_tmp < 0)
		return (random_f());
	close(fd_tmp);
	unlink(file_name);
	return (file_name);
}

static int	fill_file(t_redir *alter, char *file_name)
{
	char	*line;
	char	*content;
	int		fd_file;

	content = NULL;
	while (1)
	{
		write(1, "heredoc> ", 10);
		line = readline(STDIN_FILENO);
		if (!my_strcmp(line, alter->file))
		{
			(1) && (free(line), line = NULL);
			break ;
		}
		content = ft_strjoin(content, line);
		(line) && (free(line), 0);
	}
	fd_file = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0777);
	(fd_file < 0) && (perror("open"), my_malloc(0, 0), 0);
	write(fd_file, content, ft_strlen(content));
	return (fd_file);
}

int	_heredoc_(t_redir *alter)
{
	char	*file_name;
	int		fd_in;
	
	file_name = random_f();
	fd_in = fill_file(alter, file_name);
	(fd_in < 0) && (perror("open"), my_malloc(0, 0));
	unlink(file_name);
	return (fd_in);
}
