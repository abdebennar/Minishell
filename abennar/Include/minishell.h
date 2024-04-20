/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 08:28:29 by abennar           #+#    #+#             */
/*   Updated: 2024/04/20 21:34:45 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL
# define MINI_SHELL

#include <stdio.h>
# include <stdbool.h>
#include "../libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>

# define ALLOC	1
# define CLEAN	0
# define SEP	" \t\n\v\r\f"

typedef	enum e_token
{
	AND,		// &&
	OR,			// ||
	PIPE,		// | 
	HEREDOC,	// <<
	APPEND,		// >>
	OUT,		// >
	IN,			// < 
	LPR,		// (
	RPR,		// )
	NOT
}			t_token;

typedef struct s_redir
{
	char			*file;
	t_token			tok;
	struct s_redir	*next;
	struct s_redir	*prev;
}	t_redir;

typedef	struct s_node
{
	char			*cmd;
	char			**args;

	char			*full_cmd;
	int				pre;
	t_token			tok;
	t_redir			*redir;
	struct s_node	*left;
	struct s_node	*right;
}	t_node;


// typedef struct s_data
// {
// 	void			*data;
// 	struct s_data	*next;
// }	t_data;


void	print_tok(t_token tok);

void	*my_malloc(size_t size, int mode);

t_node	*new_node(char *cmd, t_redir *redir, t_token tok, int pre);
void	add_redir_back(t_redir *node, t_redir **list);
t_redir	*new_redir(char *file, t_token tok);
void	add_node_back(t_node *node, t_node **list);
char *get_next_word(char *str, int *i, t_token tok);
t_token	get_token(char c1, char c2);
int	get_cmd_area(char *s, int start);
void	add_node_back(t_node *node, t_node **list);
void	Parsing(char *cmd);
t_node	*lexer(char *cmd);
bool	low_pre(t_token tok);

int	skip_quaout(char *s, char c);
void	lst_iter(t_node	*lst, void (*f)(t_node *));
void	get_args(t_node *node);

t_node	*infix_to_postfix(t_node **lst);
t_node	*postfix_to_prefex(t_node *node);
t_node	*tree(t_node	*node);

void	top_push(t_node **src, t_node **dest);
void	back_push(t_node **src, t_node **dest);

#endif