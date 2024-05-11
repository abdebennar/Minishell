SRC			= utils/*.c Parsing/*.c Exec/*/*.c main.c
SHELL		= /bin/bash
NAME		= minishell
CFLAGS		= -Wall -Wextra -Werror -lreadline #-fsanitize=address
CC			= cc
BREW		= $(HOME)/goinfre/homebrew/bin/brew
INCLUDE		= -I$(HOME)/goinfre/homebrew/opt/readline/include -I$(PWD)/Include
LIBRARY		= -L$(HOME)/goinfre/homebrew/opt/readline/lib

CHEKC_BREW	:= $(shell command -v brew)
RDL_CHEKC	:= $(shell brew list | grep "readline")



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
	@brew update --force >/dev/null 2>&1
	@echo "[+]done"
endif
ifndef RDL_CHEKC
	@echo "[x]installing readline lib"
	@echo "wait...."
	@brew install readline >/dev/null 2>&1
	@echo "[+] done"
endif


$(NAME)	: $(SRC)
	cc  $(CFLAGS) $(LIBRARY) $(INCLUDE) $(SRC) -I$(PWD)/Include -o $@

clean	:
	@echo "[x] nothing to clean"

fclean	:
	rm -rf $(NAME) >/dev/null 2>&1

re	:
	$(MAKE) fclean
	$(MAKE) all