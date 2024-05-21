/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 08:22:24 by abennar           #+#    #+#             */
/*   Updated: 2024/05/21 05:44:08 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig = 0;

void	handle_heredoc(t_node *root)
{
	t_redir	*alter;
	
	if (!root)
		return ;
	alter = root->redir;
	while (alter)
	{
		alter->file = beta_expanding(alter->file);
		if (!alter->file)
		{
			alter->file = my_malloc(1, 1, 1);
			alter->file = "\0";	
		}
		if (alter->tok == HEREDOC)
			alter->fd = _heredoc_(alter);
		alter = alter->next;
	}
	if (root->left)
		handle_heredoc(root->left);
	if (root->right)
		handle_heredoc(root->right);
}

int	main(void)
{
	char	*line;
	t_node	*node;

	if (!isatty(0))
		return (put_err("khrj t9wd\n"), 0);
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
		handle_heredoc(node);
		_exec_arch_(node);
		g_sig = 0;
	}
	printf("exit\n");
	my_malloc(0, 0, 1);
	my_malloc(0, 0, 0);
}

// export l="   p"
// export p=$l
// (a) > out
// $DSALKM""   					///////////
// << l | << l
//(<<"|)")
// "(")
//<<"|(")
//<< &"&"
//<< ""   					///////////
//cat > ''    					///////////
//ls .... (using recursion in the parse)
//< test.c cat >> out && << ok (cat || ls)   -> << and () 
//$_ | $_
// << s>  
//echo h > ''      					///////////
//<< ''			   					///////////
//ulimits -s 5 this set the limit of stack to 5kb
//  ~ ?
// echo 1 && echo
// export a=' * ' && echo $a
//strdup_len - I changed the last arg on while do the test