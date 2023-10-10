all: 
	cc -Wall -Wextra -Werror *.c -o Philo 
clean:
	rm -f Philo
fclean:
	rm -f Philo