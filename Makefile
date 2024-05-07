SRC = utils/*.c Parsing/*.c Exec/*/*.c main.c

NAME = minishell

FLAGS = -Wall -Wextra -Werror -lreadline

INCLUDE = -I$(HOME)/goinfre/homebrew/opt/readline/include -I$(PWD)/Include
LIBRARY = -L/Users/abennar/goinfre/homebrew/opt/readline/lib

all:
	@if ! brew -v ; then \
		curl --silent -L https://github.com/Homebrew/brew/tarball/master | tar xz --strip 1 -C ~/goinfre/homebrew > /dev/null 2>&1; \
	fi
	@if ! brew list | grep "readline"; then \
		brew install readline ; \
	fi
	$(MAKE) $(NAME)

$(NAME):
	cc -fsanitize=address $(FLAGS) $(LIBRARY) $(INCLUDE) $(SRC) -I$(PWD)/Include -o $@

re :
	rm -rf minishell
	$(MAKE) all