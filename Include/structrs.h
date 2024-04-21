/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structrs.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 17:42:30 by abennar           #+#    #+#             */
/*   Updated: 2024/04/21 19:44:01 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	char			*cmd;
	char			**args;
	t_redir			*redir;
	t_env			*env;  // TODO 
	struct s_node	*left;
	struct s_node	*right;
}	t_node;