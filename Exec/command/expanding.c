/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 00:29:18 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/05/30 22:14:39 by abennar          ###   ########.fr       */
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
		{
			clean = ft_strjoin(clean, s_q(&m_cmd[index], &index), 0);
			if (!clean)
				clean = ft_strdup("\0", 0);
		}
		else if (m_cmd[index] == '"')
		{
			clean = ft_strjoin(clean, d_q(&m_cmd[index], &index), 0);
			if (!clean)
				clean = ft_strdup("\0", 0);
		}
		else if (m_cmd[index] == '$')
			clean = ft_strjoin(clean, dollar(&m_cmd[index], &index, 0), 0);
		else
			clean = add_c(clean, m_cmd[index++], 0);
	}
	return (clean);
}

char	**b_expanding_(char **cmd)
{
	int		v_index;

	v_index = -1;
	while (cmd[++v_index])
	{
		if (_wildcard_(prep_w(cmd[v_index])))
			cmd[v_index] = _wildcard_(prep_w(cmd[v_index]));
		else
			cmd[v_index] = b_b_expanding_(cmd[v_index]);
	}
	return (cmd);
}

char	**_expanding_(t_node **node)
{
	char	**cmd;

	cmd = b_expanding_((*node)->cmd);
	return (cmd);
}

char	*beta_expanding(char *f_name)
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

char	*alter_exp(char *alter)
{
	char	**tmp_alter;

	if (!beta_expanding(alter))
	{
		put_str_err("No such file or directory", alter);
		return (NULL);
	}
	tmp_alter = b_expanding_(ft_split(alter, "\177", 0));
	if (!tmp_alter[0])
	{
		put_str_err(" ambiguous redirect", alter);
		return (NULL);
	}
	tmp_alter = ft_split(tmp_alter[0], "\a", 0);
	if (tmp_alter[1])
	{
		put_str_err(" ambiguous redirect", beta_expanding(alter));
		return (NULL);
	}
	return (tmp_alter[0]);
}
