SRCS 		=	Exec/builtins/cd.c \
				Exec/builtins/echo.c \
				Exec/builtins/env.c \
				Exec/builtins/exit.c \
				Exec/builtins/export.c \
				Exec/builtins/pwd.c \
				Exec/builtins/unset.c \
				Exec/command/exec.c \
				Exec/command/exec_helper.c \
				Exec/command/expanding.c \
				Exec/command/expanding_helper.c \
				Exec/command/quotes.c \
				Exec/command/quotes_helper.c \
				Exec/command/wildcard.c \
				Exec/executor/and_or.c \
				Exec/executor/heredoc.c \
				Exec/executor/heredoc_helper.c \
				Exec/executor/pipe.c \
				Exec/executor/redirections.c \
				Exec/executor/redirections_helper.c \
				Parsing/algo.c \
				Parsing/algo_utils.c \
				Parsing/error.c \
				Parsing/init.c \
				Parsing/lexer.c \
				Parsing/mng_args.c \
				Parsing/mng_cmd.c \
				Parsing/parsing.c \
				Parsing/syntax.c \
				Parsing/tree.c \
				utils/ft_is.c \
				utils/ft_itoa.c \
				utils/ft_split.c \
				utils/ft_str.c \
				utils/ft_str2.c \
				utils/ft_strjoin.c \
				utils/ft_strtrim.c \
				utils/get_next_word.c \
				utils/link_lst.c \
				utils/link_lst2.c \
				utils/my_malloc.c \
				utils/setenv.c \
				utils/signal.c \
				main.c
OBJDIR		= $(CURDIR)/obj
SHELL		= /bin/bash
NAME		= minishell
CFLAGS		= -Wall -Wextra -Werror
XFLAGS		= -lreadline# -fsanitize=address
CC			= cc
HEADER		= $(CURDIR)/Include/minishell.h $(CURDIR)/Include/prottypes.h
BREW		= $(HOME)/goinfre/homebrew/bin/brew
INCLUDE		= -I$(HOME)/goinfre/homebrew/opt/readline/include -I$(CURDIR)/Include
LIBRARY		= -L$(HOME)/goinfre/homebrew/opt/readline/lib
BREW		= $(HOME)/goinfre/homebrew/bin/brew
CHEKC_BREW	:= $(shell command -v $(BREW))
RDL_CHEKC	:= $(shell $(BREW) list | grep "readline")
OBJS 		= $(SRCS:%.c=$(OBJDIR)/%.o)

all	: check_brew
	@$(MAKE) $(NAME)

check_brew	:
ifndef CHEKC_BREW
	@echo
	@echo "[x] Homebrew not found. Initiating installation..."
	@echo "Please wait..."
	@mkdir ~/goinfre/homebrew >/dev/null 2>&1
	@curl -s -L https://github.com/Homebrew/brew/tarball/master | \
	tar xz --strip 1 -C ~/goinfre/homebrew >/dev/null 2>&1 
	@$(BREW) update --force >/dev/null 2>&1
	@echo "[+] Homebrew installation complete."
endif
ifndef RDL_CHEKC
	@echo "[x] Installing readline library..."
	@echo "Please wait..."
	@$(BREW) install readline >/dev/null 2>&1
	@echo "[+] Readline library installation complete."
endif

$(NAME)	: $(HEADER) $(OBJS)
	$(CC) $(XFLAGS) $(LIBRARY) $(INCLUDE) $(OBJS) -o $@


$(OBJDIR)/%.o: %.c $(HEADER)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean	:
	rm -rf $(OBJDIR)

fclean	: clean
	rm -f $(NAME)

re	: fclean all