/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 05:50:24 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/05/21 22:07:53 by abennar          ###   ########.fr       */
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
	file_name = my_malloc(file_len + 1, 1, 0);
	fd_rd = open("/dev/urandom", O_RDONLY, 0777);
	if (fd_rd < 0)
		return (perror("cannot open /dev/urandom"), NULL);
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

char	*expand_heredoc(char *line)
{
	char	*clean;
	char	*dollar_out;
	int		index;

	index = 0;
	clean = NULL;
	dollar_out = NULL;
	while (line[index])
	{
		if (line[index] == '$' && only_identifier(&line[index + 1]))
		{
			dollar_out = dollar(&line[index], &index, 1);
			clean = ft_strjoin(clean, dollar_out, 0);
		}
		else
			clean = add_c(clean, line[index++], 0);
	}
	return (clean);
}

static int	fill_file(t_redir *alter, char *file_name)
{
	char	*line;
	char	*content;
	char	*exp_line;
	int		fd_file;

	content = NULL;
	signal(SIGINT, heredoc_h);
	while (1)
	{
		line = readline("heredoc>");
		if (!line || !doc_strcmp(line, alter->file) || g_sig == 2)
		{
			(1) && (free(line), line = NULL);
			break ;
		}
		exp_line = expand_heredoc(line);
		(line) && (free(line), line = NULL);
		content = ft_strjoin(content, ft_strjoin(exp_line, "\n", 0), 0);
	}
	if (g_sig == 2)
		return (-1);
	fd_file = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd_file < 0)
		return (perror("open"), -1);
	write(fd_file, content, ft_strlen(content));
	return (close(fd_file), fd_file);
}

int	_heredoc_(t_redir *alter)
{
	char	*file_name;
	int		fd_in;

	fd_in = 0;
	file_name = random_f();
	fd_in = fill_file(alter, file_name);
	if (fd_in < 0)
	{
		unlink(file_name);
		g_sig = 1;
		return (-1);
	}
	fd_in = open(file_name, O_RDWR | O_CREAT, 0777);
	unlink(file_name);
	return (fd_in);
}
