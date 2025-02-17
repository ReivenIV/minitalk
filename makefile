# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rita <rita>                                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/17 12:17:07 by rita              #+#    #+#              #
#    Updated: 2025/02/17 12:17:07 by rita             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minitalk
CFLAGS = -Wall -Werror -Wextra
CC = gcc
SRCS = client.c server.c tools_bits.c tools_nbs.c tools_signals.c \
tools_strs.c \

OBJS = $(SRCS:.c=.o)

# Rules 
all: $(NAME)

$(NAME): server client

server: $(OBJS)
	$(CC) -o server $(OBJS)

client: $(OBJS)
	$(CC) -o client $(OBJS)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJS)
	
fclean: clean
	rm -f server client

re: fclean all

.PHONY: all bonus clean fclean re