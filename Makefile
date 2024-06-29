# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ariling <ariling@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/29 18:46:21 by ariling           #+#    #+#              #
#    Updated: 2024/06/29 19:02:45 by ariling          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Directories
LIBFT_DIR = ./libft
LIBFT_INC = $(LIBFT_DIR)/includes
LIBFT = $(LIBFT_DIR)/libft.a
INCLUDES = -I$(LIBFT_INC) -I.

# Source files
CLIENT_SRC = client.c
SERVER_SRC = server.c

# Object files
CLIENT_OBJ = $(CLIENT_SRC:.c=.o)
SERVER_OBJ = $(SERVER_SRC:.c=.o)

# Executable names
CLIENT = client
SERVER = server

# All rule
all: $(LIBFT) $(CLIENT) $(SERVER)

# Compile libft
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# Compile client
$(CLIENT): $(CLIENT_OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(CLIENT_OBJ) -o $(CLIENT) $(LIBFT) $(INCLUDES)

# Compile server
$(SERVER): $(SERVER_OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(SERVER_OBJ) -o $(SERVER) $(LIBFT) $(INCLUDES)

# Generic rule for object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

# Clean rule
clean:
	rm -f $(CLIENT_OBJ) $(SERVER_OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean

# Full clean rule
fclean: clean
	rm -f $(CLIENT) $(SERVER)
	$(MAKE) -C $(LIBFT_DIR) fclean

# Rebuild rule
re: fclean all
