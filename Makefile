SRC = utils/*.c Parsing/*.c Exec/*/*.c main.c
SHELL := /bin/bash
NAME = minishell
BREW = $(HOME)/goinfre/homebrew/bin/brew
FLAGS = -Wall -Wextra -Werror -lreadline -fsanitize=address

INCLUDE = -I$(HOME)/goinfre/homebrew/opt/readline/include -I$(PWD)/Include
LIBRARY = -L$(HOME)/goinfre/homebrew/opt/readline/lib

all:
	@rm -rf minishell;
	@alias brew='$(HOME)/goinfre/homebrew/bin/brew';
	@if ! $(BREW) -v  >/dev/null 2>&1 ; then \
		echo "\n[x] installing home brew ...";\
		mkdir ~/goinfre/homebrew >/dev/null 2>&1 ; \
		curl --silent -L https://github.com/Homebrew/brew/tarball/master |\
		tar xz --strip 1 -C ~/goinfre/homebrew >/dev/null 2>&1; \
		$(BREW) update --force --quiet >/dev/null 2>&1; \
		echo "[+]done"; \
	fi
	@if ! $(BREW) list | grep "readline" >/dev/null 2>&1 ; then \
		echo "[x] installing readline ...";\
		$(BREW) install readline >/dev/null 2>&1; \
		echo "[+]done"; \
	fi
	$(MAKE) $(NAME)

$(NAME):
	cc  $(FLAGS) $(LIBRARY) $(INCLUDE) $(SRC) -I$(PWD)/Include -o $@

re :
	rm -rf minishell
	$(MAKE) all