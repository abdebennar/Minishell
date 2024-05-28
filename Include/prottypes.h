/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prottypes.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 17:42:30 by abennar           #+#    #+#             */
/*   Updated: 2024/05/28 17:09:55 by bel-oirg         ###   ########.fr       */
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
# define PROMPT			 "$ "
# define SYNTAX_ERR		"shell: syntax error near unexpected token "
# define NOCMD_ERR		" command not found"
# define EXIT_MANY_ARGS "exit\nshell: exit: too many arguments\n"

extern int				g_sig;
typedef unsigned int	t_uint;
typedef long long		t_llong;
extern char				**environ;

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
	NOT,
	END
}	t_token;

typedef struct s_redir
{
	char			*file;
	t_token			tok;
	int				fd;
	struct s_redir	*next;
	struct s_redir	*prev;
}	t_redir;

typedef struct s_node
{
	/* my bs*/
	char			*full_cmd;
	int				pre;
	t_token			tok;
	/* your's */
	int				fd[2];
	int				io_bk[2];
	// int				pid[2];
	char			**cmd;
	t_redir			*redir;
	t_env			*env;
	struct s_node	*left;
	struct s_node	*right;
}	t_node;

#endif