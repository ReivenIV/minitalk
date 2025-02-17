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

CLIENT_SRCS = client.c tools_bits.c tools_nbs.c tools_signals.c tools_strs.c
SERVER_SRCS = server.c tools_bits.c tools_nbs.c tools_signals.c tools_strs.c

CLIENT_OBJS = $(CLIENT_SRCS:.c=.o)
SERVER_OBJS = $(SERVER_SRCS:.c=.o)

# Rules 
all: $(NAME)
	$(MAKE) clean

$(NAME): server client

server: $(SERVER_OBJS)
	$(CC) -o server $(SERVER_OBJS)

client: $(CLIENT_OBJS)
	$(CC) -o client $(CLIENT_OBJS)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f $(CLIENT_OBJS) $(SERVER_OBJS)
	
fclean: clean
	rm -f server client

re: fclean all
	$(MAKE) clean

.PHONY: all bonus clean fclean re