/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 00:29:18 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/05/13 01:21:08 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*b_b_expanding_(char *m_cmd)
{
	int		index;
	char	*clean;

	index = 0;
	clean = NULL;
	while (m_cmd && m_cmd[index])
	{
		if (m_cmd[index] == '\'')
			clean = ft_strjoin(clean, s_q(&m_cmd[index], &index), 0);
		else if (m_cmd[index] == '"')
			clean = ft_strjoin(clean, d_q(&m_cmd[index], &index), 0);
		else if (m_cmd[index] == '$')
			clean = ft_strjoin(clean, dollar(&m_cmd[index], &index), 0);
		else
			clean = add_c(clean, m_cmd[index++], 0);
	}
	return (clean);
}

static char	**b_expanding_(char **cmd)
{
	int		v_index;

	v_index = -1;
	while (cmd[++v_index])
	{
		if (count_c(prep_w(cmd[v_index]), '*'))
		{
			if (_wildcard_(prep_w(cmd[v_index])))
				cmd[v_index] = _wildcard_(prep_w(cmd[v_index]));
			else
				cmd[v_index] = alter_expanding_(cmd[v_index]);
		}
		else
		{
			if (!alter_expanding_(cmd[v_index]))
				cmd[v_index] = ft_strdup("\177", 0);
			else
				cmd[v_index] = b_b_expanding_(cmd[v_index]);
		}
	}
	return (cmd);
}

char	**_expanding_(t_node **node)
{
	char	**w_cmd;
	char	**cmd;
	int		v_index;

	cmd = b_expanding_((*node)->cmd);
	(1) && (w_cmd = NULL, v_index = -1);
	while (cmd && cmd[++v_index])
		w_cmd = concatenate_strings(w_cmd, ft_split(cmd[v_index], "\a", 0));
	return (w_cmd);
}

char	*alter_expanding_(char *f_name)
{
	char	*clean;
	int		index;

	(1) && (index = 0, clean = NULL);
	while (f_name && f_name[index])
	{
		if (f_name[index] == '\'')
			clean = ft_strjoin(clean, s_q(&f_name[index], &index), 0);
		else if (f_name[index] == '"')
			clean = ft_strjoin(clean, d_q_heredoc(&f_name[index], &index), 0);
		else
			clean = add_c(clean, f_name[index++], 0);
	}
	return (clean);
}
