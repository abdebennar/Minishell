       0       0       0

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