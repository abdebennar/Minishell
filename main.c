/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 08:22:24 by abennar           #+#    #+#             */
/*   Updated: 2024/05/30 03:43:31 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig = 0;

void	term_attr(struct termios *att)
{
	if (isatty(0) && tcgetattr(0, att))
		perror("termios");
}

int	main(void)
{
	char			*line;
	t_node			*node;
	struct termios	att;

	add_env();
	while (666)
	{
		sig_ign();
		my_malloc(0, 0, 0);
		line = readline(PROMPT);
		if (!line)
			break ;
		node = parsing(line);
		if (handle_heredoc(node))
			node = NULL;
		term_attr(&att);
		_exec_arch_(node);
		g_sig = 0;
		if (isatty(0) && tcsetattr(0, TCSANOW, &att))
			perror("termios");
	}
	put_err("exit\n");
	clear_history();
	my_malloc(0, 0, 1);
	my_malloc(0, 0, 0);
}

// FIX // TODO //

/*
** ls " > file "
** cat "" ls "" ...  non stable behaviour 
*/

// export l="   p" && export p=$l && echo $p
// $DSALKM""   					///////////
// << l | << l					///////////
//(<<"|)")               ////////////
// "(")					///////////	
//RESET THE FDS if CTRL+C on multiple heredoc `<< l | << k`		//////////////
//<< ""   					///////////
//cat > ''    					///////////
//ls .... (using recursion in the parse) 	/////////////`
//< test.c cat >> out && << ok (cat || ls)   -> << and ()   (   ls (whoami)  )
//./minishell | ./minishell ??
// << s>  							/////
//echo h > ''      					///////////
// export a=' * ' && echo $a  ??

// export l="      1"
// export p=$l

// unset with a var without value /////////////
// top with (sig quit) ruines the readline ///////////

// fd leak : multi heredoc in pipe and || ///////////
// heredoc file change its place to /tmp or any  ///////////
//(3232) ls
//env -i bash --> echo $PATH
//exit stat of SYNXT ERR is 258 not 2
