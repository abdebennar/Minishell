/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 05:50:24 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/05/31 00:08:49 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*random_f(void)
{
	char	*file_name;
	int		file_len;
	int		fd_rd;
	int		fd_tmp;

	fd_rd = open("/dev/urandom", O_RDONLY, 0777);
	if (fd_rd < 0)
		return (perror("cannot open /dev/urandom"), NULL);
	file_len = 21;
	file_name = my_malloc(file_len + 1, 1, 0);
	file_name[0] = '/';
	file_name[1] = 't';
	file_name[2] = 'm';
	file_name[3] = 'p';
	file_name[4] = '/';
	read(fd_rd, file_name + 5, 16);
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

static char	*fill_file(t_redir *alter)
{
	char	*line;
	char	*content;

	content = NULL;
	while (1)
	{
		line = readline("heredoc>");
		if (!line || !doc_strcmp(line, alter->file) || g_sig == 2)
		{
			(1) && (free(line), line = NULL);
			break ;
		}
		if (line)
			content = ft_strjoin(content, ft_strjoin(line, "\n", 0), 0);
		(line) && (free(line), line = NULL);
	}
	if (g_sig == 2)
		return (NULL);
	return (content);
}

char	*_heredoc_(t_redir *alter)
{
	char	*content;
	int		fd;

	fd = dup(STDIN_FILENO);
	signal(SIGINT, heredoc_h);
	content = fill_file(alter);
	if (!content)
	{
		g_sig = 1;
		dup2(fd, STDIN_FILENO);
		close(fd);
		return (NULL);
	}
	close(fd);
	return (content);
}
