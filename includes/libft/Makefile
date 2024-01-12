# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/04 19:10:12 by mcatalan@st       #+#    #+#              #
#    Updated: 2023/08/22 11:16:37 by mcatalan@st      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CFLAGS = -Wall -Wextra -Werror

# Colors
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
VIOLET = \033[0;35m
RESET = \033[0m

SRCS = $(wildcard *.c)

OBJS_DIR = obj
DEPS_DIR = dep

OBJS = $(addprefix $(OBJS_DIR)/,$(SRCS:.c=.o))
DEPS = $(addprefix $(DEPS_DIR)/,$(SRCS:.c=.d))

INCLUDE = -I ./

RM = rm -f

$(OBJS_DIR)/%.o: %.c libft.h
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -MMD $(INCLUDE) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	ar -rcs $(NAME) $(OBJS)

-include $(DEPS)

clean:
	$(RM) -r $(OBJS_DIR)  $(DEPS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
.PHONY: all clean fclean re
