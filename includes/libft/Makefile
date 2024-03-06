# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/04 19:10:12 by mcatalan@st       #+#    #+#              #
#    Updated: 2024/03/06 13:27:40 by mcatalan         ###   ########.fr        #
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

SRCS =	ft_add_str.c	\
		ft_atoi.c	\
		ft_atol.c	\
		ft_bzero.c	\
		ft_calloc.c	\
		ft_is_enter.c	\
		ft_is_space.c	\
		ft_isalnum.c	\
		ft_isalpha.c	\
		ft_isascii.c	\
		ft_isdigit.c	\
		ft_isprint.c	\
		ft_itoa.c		\
		ft_lstadd_back.c	\
		ft_lstadd_front.c	\
		ft_lstclear.c		\
		ft_lstdelone.c		\
		ft_lstiter.c		\
		ft_lstlast.c		\
		ft_lstmap.c			\
		ft_lstnew.c			\
		ft_lstsize.c		\
		ft_memchr.c			\
		ft_memcmp.c			\
		ft_memcpy.c			\
		ft_memmove.c		\
		ft_memset.c			\
		ft_num_size.c		\
		ft_putchar_fd.c		\
		ft_putchar.c		\
		ft_putendl_fd.c		\
		ft_putnbr_fd.c		\
		ft_putstr_fd.c		\
		ft_split.c			\
		ft_strcat.c			\
		ft_strchr.c			\
		ft_strcmp.c			\
		ft_strcmpc.c		\
		ft_strcmpnks.c		\
		ft_strcpy.c			\
		ft_strncpy.c		\
		ft_strdup.c		\
		ft_striteri.c		\
		ft_strjoin.c		\
		ft_strlcat.c		\
		ft_strlcpy.c		\
		ft_strlen.c			\
		ft_strmapi.c		\
		ft_strncmp.c		\
		ft_strncpy.c		\
		ft_strnstr.c		\
		ft_strrchr.c		\
		ft_strswap.c		\
		ft_strtrim.c		\
		ft_substr.c			\
		ft_tolower.c		\
		ft_toupper.c		\
		get_next_line_bonus.c	\
		get_next_line_utils_bonus.c

OBJS_DIR = obj
DEPS_DIR = dep

OBJS = $(addprefix $(OBJS_DIR)/,$(SRCS:.c=.o))
DEPS = $(addprefix $(DEPS_DIR)/,$(SRCS:.c=.d))

INCLUDE = -I ./

RM = rm -rf

$(OBJS_DIR)/%.o: %.c libft.h
#	@echo "$(YELLOW)Compiling libft...$(RESET)"
	@mkdir -p $(OBJS_DIR) $(DEPS_DIR)
	@$(CC) $(CFLAGS) -MMD $(INCLUDE) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
#	@echo "$(YELLOW)Building libft...$(RESET)"
	@ar -rcs $(NAME) $(OBJS)
	@echo "$(GREEN)Built libft!$(RESET)✅"

-include $(DEPS)

clean:
#	@echo "$(YELLOW)Cleaning libft...$(RESET)"
	@$(RM) $(OBJS_DIR) $(DEPS_DIR)
	@echo "$(RED)Cleaned libft!$(RESET)✅"

fclean:
#	@echo "$(YELLOW)Fcleaning libft...$(RESET)"
	@$(RM) $(NAME)
	@$(RM) $(OBJS_DIR)  $(DEPS_DIR)
	@echo "$(RED)Fcleaned libft!$(RESET)✅"

re: fclean all
.PHONY: all clean fclean re
