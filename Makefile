SRC = utils/*.c Parsing/*.c Exec/*/*.c main.c

NAME = minishell

FLAGS = -Wall -Wextra -Werror -lreadline

INCLUDE = -I$(HOME)/goinfre/homebrew/opt/readline/include -I$(PWD)/Include
LIBRARY = -L/Users/abennar/goinfre/homebrew/opt/readline/lib

all:
	@rm minishell
	@if ! brew -v  >/dev/null 2>&1 ; then \
		echo "\n[x] installing home brew ...";\
		mkdir ~/goinfre/homebrew >/dev/null 2>&1 ; \
		curl --silent -L https://github.com/Homebrew/brew/tarball/master |\
		tar xz --strip 1 -C ~/goinfre/homebrew >/dev/null 2>&1; \
		brew update --force --quiet >/dev/null 2>&1; \
		echo "[+]done"; \
	fi
	@if ! brew list | grep "readline" >/dev/null 2>&1 ; then \
		echo "[x] installing readline ...";\
		brew install readline >/dev/null 2>&1; \
		echo "[+]done"; \
	fi
	$(MAKE) $(NAME)

$(NAME):
	cc -fsanitize=address $(FLAGS) $(LIBRARY) $(INCLUDE) $(SRC) -I$(PWD)/Include -o $@

re :
	rm -rf minishell
	$(MAKE) all