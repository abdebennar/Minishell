SRC			= utils/*.c Parsing/*.c Exec/*/*.c main.c
SHELL		= /bin/bash
NAME		= minishell
CFLAGS		= -Wall -Wextra -Werror -lreadline  #fsanitize=address
CC			= cc
HEADER		= Include/minishell.h Include/prottypes.h
BREW		= $(HOME)/goinfre/homebrew/bin/brew
INCLUDE		= -I$(HOME)/goinfre/homebrew/opt/readline/include -I$(PWD)/Include
LIBRARY		= -L$(HOME)/goinfre/homebrew/opt/readline/lib
BREW		=$(HOME)/goinfre/homebrew/bin/brew
CHEKC_BREW	:= $(shell command -v $(BREW))
RDL_CHEKC	:= $(shell $(BREW) list | grep "readline")


all	: check_brew
	@$(MAKE) $(NAME)

check_brew	:
ifndef CHEKC_BREW
	@echo
	@echo "[x] brew not found,installing now"
	@echo "wait...."
	@mkdir ~/goinfre/homebrew >/dev/null 2>&1
	@curl -s -L https://github.com/Homebrew/brew/tarball/master | \
	tar xz --strip 1 -C ~/goinfre/homebrew >/dev/null 2>&1 
	@$(BREW) update --force >/dev/null 2>&1
	@echo "[+]done"
endif
ifndef RDL_CHEKC
	@echo "[x]installing readline lib"
	@echo "wait...."
	@$(BREW) install readline >/dev/null 2>&1
	@echo "[+] done"
endif


$(NAME)	: $(SRC) $(HEADER)
	cc  $(CFLAGS) $(LIBRARY) $(INCLUDE) $(SRC) -I$(PWD)/Include -o $@

clean	:
	@echo "[x] nothing to clean"

fclean	:
	rm -rf $(NAME) >/dev/null 2>&1

re	:
	$(MAKE) fclean
	$(MAKE) all