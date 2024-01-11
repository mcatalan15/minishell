# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/10 12:38:40 by mcatalan          #+#    #+#              #
#    Updated: 2024/01/11 11:5:04 by mcatalan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
CFLAGS = -Wall -Werror -Wextra #-fsanitize=address
RM = rm -rf

# Colors
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
RESET = \033[0m

SRC = $(wildcard src/*.c)

OBJ = $(SRC:.c=.o)

DEPS = $(SRC:.c=.d)

%.o : %.c Makefile
	@echo "$(GREEN)Compiling...$(RESET)"
	$(CC) $(CFLAGS) -c $< -o $@ $(FFLAGS) -MMD

all : $(NAME)

-include $(DEPS)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(FFLAGS)

clean :
	@echo "$(RED)Cleaning up objets...$(RESET)"
	$(RM) $(OBJ) $(DEPS)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY: clean fclean all re