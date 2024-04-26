/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:50:12 by abennar           #+#    #+#             */
/*   Updated: 2024/04/26 00:04:04 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_syntax(t_token tok, char *cmd, int i)
{
	i++;
	if (tok == AND || tok == OR || tok == APPEND || tok == HEREDOC)
		i++;
	while (ft_strchr(SEP, cmd[i]))
		i++;
	if (get_token(cmd[i], cmd[i + 1]) != NOT)
	{
		printf("shell: syntax error\n");
	}
}
