/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 00:29:18 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/05/05 16:18:55 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_expanding_(t_node **node)
{
	char	**cmd;
	char	*m_cmd;
	char	*clean;
	int		index;
	int		v_index;

	v_index = -1;
	cmd = (*node)->cmd;
	while (cmd[++v_index])
	{
		(1) && (index = 0, clean = NULL, m_cmd = cmd[v_index]);
		while (m_cmd[index])
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
		cmd[v_index] = _wildcard_(clean);
	}
}
