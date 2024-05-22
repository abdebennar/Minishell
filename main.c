/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 08:22:24 by abennar           #+#    #+#             */
/*   Updated: 2024/05/22 18:05:32 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig = 0;

int	handle_heredoc(t_node *root)
{
	t_redir	*alter;
	int		c;

	c = 0;
	int	fd[2];
	fd[0] = dup(STDIN_FILENO);
	fd[1] = dup(STDOUT_FILENO);
	if (!root)
		return 0 ;
	alter = root->redir;
	while (alter)
	{
		alter->file = beta_expanding(alter->file);
		if (!alter->file)
		{
			alter->file = my_malloc(1, 1, 0);
			alter->file = "\0";	
		}
		if (alter->tok == HEREDOC)
			alter->fd = _heredoc_(alter);
			if (alter->fd == -1)
			{
				dup2(fd[0], 0);
				dup2(fd[1], 1);
				close(fd[0]);
				close(fd[1]);
				return (1);
			}
		alter = alter->next;
	}
	if (root->left && !c)
		if (handle_heredoc(root->left))
			return (1);
	if (root->right)
		if (handle_heredoc(root->right))
			return (1);
	return (0);
}

int	main(void)
{
	char	*line;
	t_node	*node;

	add_env();
	while (666)
	{
		sig_ign();
		my_malloc(0, 0, 0);
		line = readline(PROMPT);
		if (!line)
			break ;
		g_sig = 1;
		node = parsing(line);
		if (handle_heredoc(node))
			node = NULL;
		_exec_arch_(node);
		g_sig = 0;
	}
	printf("exit\n");
	my_malloc(0, 0, 1);
	my_malloc(0, 0, 0);
}

// export l="   p" && export p=$l && echo $p
// (a) > out
// $DSALKM""   					///////////
// << l | << l					///////////
//(<<"|)")               //CHECKTHIS
// "(")							
//RESET THE FDS if CTRL+C on multiple heredoc `<< l | << k`
//<<"|(")
//<< &"&"
//<< ""   					///////////
//cat > ''    					///////////
//ls .... (using recursion in the parse)
//< test.c cat >> out && << ok (cat || ls)   -> << and () 
//$_ | $_
// << s>  
//echo h > ''      					///////////
//ulimits -s 5 this set the limit of stack to 5kb
//  ~ ?
// echo 1 && echo
// export a=' * ' && echo $a
// create var a="*" and expand it inside the heredoc 	////////

// export l="      1"
// export p=$l