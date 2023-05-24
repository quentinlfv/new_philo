NAME = philo

CC		= gcc

CFLAGS	= -Wall -Werror -Wextra -pthread -g3 -O3 



SRCS		= main.c \
				thread.c \
				simulation.c	\
				init.c \
				check.c \
				free.c \
				utils.c \
				new.c \

OBJS		= $(SRCS:.c=.o)

RM 			:= rm -rf
MAKEFLAGS	+= --no-print-directory
all: $(NAME) 

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:

	$(RM) $(OBJS)	

fclean: clean
		$(RM) $(NAME)

re: 
		$(MAKE) fclean
		$(MAKE) all

.PHONY: all clean fclean re 
