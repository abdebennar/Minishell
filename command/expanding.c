/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 00:29:18 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/04/18 01:25:36 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	_b_expanding_(t_node **node)
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
		index = 0;
		clean = NULL;
		m_cmd = cmd[v_index];
		while (m_cmd[index])
		{
			if (m_cmd[index] == '\'')
				clean = ft_strjoin(clean, s_q(m_cmd, &index));
			else if (m_cmd[index] == '"')
				clean = ft_strjoin(clean, d_q(m_cmd, &index));
			else
				clean = add_c(clean, m_cmd[index++]);
		}
		m_cmd = clean;
		printf("%s\n", clean);
	}
}

int main()
{
	t_node *node;

	node = malloc(sizeof(t_node));
	node->cmd = malloc(sizeof(char *) * 3);
	node->cmd[0] = ft_strdup("ls");
	node->cmd[1] = ft_strdup("123'fds'456\"$SHfELL\"7890");
	node->cmd[2] = NULL;
	// printf("SEG %s\n", (node)->cmd[2]);

	_b_expanding_(&node);
}


// void	_expanding_(t_node **node, t_env *env)
// {
// 	t_env	*tmp_env;
// 	int		index;
	
// 	tmp_env = env;
// 	while((*node)->cmd)
// 	{
// 		index = -1;
// 		while((*node)->cmd[++index])
// 		{
// 			if ((*node)->cmd[index][0] == '$')
// 			{
// 				if (!ft_strcmp((*node)->cmd[index], "$?"))
// 					exit_stat();
// 				env = tmp_env;
// 				while (ft_strcmp(&((*node)->cmd[index][1]), env->var))
// 					env = env->next;
// 				if (env)
// 					(*node)->cmd[index] = ft_strdup(env->value);
// 				else
// 					(*node)->cmd[index] = ft_strdup("");
// 			}
// 		}
// 		*node = (*node)->rchild;
// 	}
// }
