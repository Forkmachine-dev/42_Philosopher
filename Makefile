NAME    = philo

SRC     = check.c  ft_atoi.c ft_time.c init.c life.c main.c print.c utils.c

OBJ     = ${SRC:.c=.o}

CC      = cc

CFLAGS  = -Wall -Wextra -Werror

RED     = echo "\033[0;31m"

YELLOW  = echo "\033[0;33m"

GREEN   = echo "\033[0;32m"

END     = echo "\033[0m"


all : $(NAME)

$(NAME) : $(OBJ) philo.h
	@$(GREEN)
	$(CC) $(CFLAGS) $(SRC) -o $(NAME) #-g -fsanitize=thread
	@$(END)

clean : 
	@$(YELLOW)
	rm -f $(OBJ)
	@$(END)

fclean : clean
	@$(RED)
	rm -rf $(NAME)
	@$(END)


re : fclean all
