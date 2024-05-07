/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prottypes.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 17:42:30 by abennar           #+#    #+#             */
/*   Updated: 2024/05/07 17:09:37 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTTYPES_H
# define PROTTYPES_H

# define GB_GROUPS		2
# define ALLOC			1 
# define CLEAN			0
# define SEP			" \t\n\v\r\f"
# define CMD_N_FOUND	127
# define NOT_EXEC		126
# define PROMPT			"\033[1;34m┌──(mini㉿shell)\n\033[1;34m└─$\033[0m "

extern int	g_sig;
typedef unsigned int uint;

typedef struct s_data
{
	void			*data;
	struct s_data	*next;
}	t_data;

typedef struct s_env
{
	char			*env;
	char			*var;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef enum e_token
{
	PIPE,
	HEREDOC,
	LPR,
	RPR,
	AND,
	OR,
	APPEND,
	OUT,
	IN,
	NOT
}	t_token;

typedef struct s_redir
{
	char			*file;
	t_token			tok;
	int				fd;
	struct s_redir	*next;
	struct s_redir	*prev;
}	t_redir;

typedef	struct s_node
{
	/* my bs*/
	char			*full_cmd;
	int				pre;
	t_token			tok;
	/* your's */
	int				fd[2];
	char			**cmd;
	t_redir			*redir;
	t_env			*env;
	struct s_node	*left;
	struct s_node	*right;
}	t_node;

#endif