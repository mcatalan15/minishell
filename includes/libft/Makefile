# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/04 19:10:12 by mcatalan@st       #+#    #+#              #
#    Updated: 2024/01/30 11:09:39 by mcatalan@st      ###   ########.fr        #
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

RM = rm -rf

$(OBJS_DIR)/%.o: %.c libft.h
#	@echo "$(YELLOW)Compiling libft...$(RESET)"
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -MMD $(INCLUDE) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
#	@echo "$(YELLOW)Building libft...$(RESET)"
	@ar -rcs $(NAME) $(OBJS)
	@echo "$(GREEN)Built libft!$(RESET)✅"

-include $(DEPS)

clean:
#	@echo "$(YELLOW)Cleaning libft...$(RESET)"
	@$(RM) -r $(OBJS_DIR)  $(DEPS)
	@echo "$(RED)Cleaned libft!$(RESET)✅"

fclean:
#	@echo "$(YELLOW)Fcleaning libft...$(RESET)"
	@$(RM) $(NAME)
	@$(RM) -r $(OBJS_DIR)  $(DEPS)
	@echo "$(RED)Fcleaned libft!$(RESET)✅"

re: fclean all
.PHONY: all clean fclean re
