/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 08:22:24 by abennar           #+#    #+#             */
/*   Updated: 2024/05/26 21:20:58 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig = 0;

int	handle_heredoc(t_node *root)
{
	t_redir	*alter;
	int		fd;

	if (!root)
		return (0);
	fd = dup(STDIN_FILENO);
	alter = root->redir;
	while (alter)
	{
		alter->file = beta_expanding(alter->file);
		if (!alter->file)
			alter->file = ft_strdup("\0", 0);
		if (alter->tok == HEREDOC)
			alter->fd = _heredoc_(alter);
		if (alter->fd == -1)
			return (dup2(fd, 0), close(fd), 1);
		alter = alter->next;
	}
	close(fd);
	if (root->left && handle_heredoc(root->left))
		return (1);
	if (root->right && handle_heredoc(root->right))
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
// $DSALKM""   					///////////
// << l | << l					///////////
//(<<"|)")               ////////////
// "(")					///////////	
//RESET THE FDS if CTRL+C on multiple heredoc `<< l | << k`		//////////////
//<< ""   					///////////
//cat > ''    					///////////
//ls .... (using recursion in the parse) 	/////////////
//< test.c cat >> out && << ok (cat || ls)   -> << and ()   (   ls (whoami)  )
//./minishell | ./minishell ??
// << s>  							/////
//echo h > ''      					///////////
// export a=' * ' && echo $a  ??
// create var a="*" and expand it inside the heredoc 	////////

// export l="      1"
// export p=$l

// unset with a var without value
// top with (sig quit) ruines the readline 

// fd leak : multi heredoc in pipe and ||
// heredoc file change its place to /tmp or any