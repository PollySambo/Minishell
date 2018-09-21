

NAME = minishell
FILES = main.c builtins.c enviroment.c indirect.c
HEADER = minishell.h
OBJECTS = $(FILES:.c=.o)
HLOC = .
FLAGS = -Wall -Werror -Wextra -I$(HLOC) -c -g -g3 -static

LIB = libft/libft.a

all: $(NAME)

$(NAME):
	@gcc $(FLAGS) $(FILES) $(HEADER)
	@gcc -o $(NAME) $(OBJECTS) $(LIB)
	@echo "minishell compiled"

lib:
	@make -C libft/ all

clean:
	@rm -f $(OBJECTS)
	@echo "minishell cleaned"

fcleanlib:
	@make -C libft/ fclean

fclean: clean 
	@rm -f minishell
	@echo "minishell fcleaned"

mclean:
	@find . -name '._*' -type f -delete
	@echo "Removed hidden ._ files."

re: fcleanlib fclean clean lib all

test: fclean all

norm:
	@clear
	@echo "Norme Minishell"
	@norminette -R CheckForbiddenSourceHeader $(FILES) $(HEADER)
	@echo ""
	@make -C libft/ norm
	@echo "Norme Check Completed"
