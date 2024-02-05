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

# MACOS
# Print MINISHELL and authors' names
MINISHELL_MSG = MINISHELL
AUTHORS_MSG = by jpaul-kr & mcatalan
MESSAGE_LEN = $$(($(shell echo $(MINISHELL_MSG) | wc -c) - 1))

PRINT_MINISHELL = @printf "$(VIOLET)%*s$(RESET)\n" $(MESSAGE_LEN) $(MINISHELL_MSG)
PRINT_AUTHORS = @echo "$(BLUE)$(AUTHORS_MSG)$(RESET)"

# Colors
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
VIOLET = \033[0;35m
RESET = \033[0m

LIBFT_D = includes/libft/
LIBFT = libft.a

READLINE_D = readline/
READLINE = libreadline.a
READLINE_H = libhistory.a
READLINE_FLAGS = -lreadline -ltermcap
READLINE_CONFIGURE = $(wildcard $(READLINE_D)config.status)
READLINE_FILES = $(wildcard $(READLINE_D)$(READLINE) $(READLINE_D)$(READLINE_H))

NAME = minishell

SRCS =	$(wildcard src/*.c)

OBJS = $(SRCS:.c=.o)

DEPS = $(SRCS:.c=.d)

INCLUDE = -I./
RM = rm -f
CFLAGS = -Wall -Wextra -Werror
OFLAGS = -g -fsanitize=address

all: print_message libft readline $(NAME)
	@echo "$(GREEN)Build finished successfully!$(RESET)✅"

libft:
	@echo "$(YELLOW)Building libft...$(RESET)"
	@make --no-print-directory -C $(LIBFT_D)

readline:
ifeq ($(READLINE_CONFIGURE),)
	@echo "$(YELLOW)Building readline...$(RESET)"
	@cd $(READLINE_D) && ./configure &> /dev/null && make
	@make --no-print-directory -C $(READLINE_D)
	@echo "$(GREEN)Built readline!$(RESET)✅"
else
ifeq ($(wildcard $(READLINE_D)/config.status),)
	@echo "$(YELLOW)Configuring readline$(RESET)"
	@cd $(READLINE_D) && ./configure
else
ifeq ($(READLINE_FILES),)
	@echo "$(GREEN)Readline Configured$(RESET)✅"
	@echo "$(YELLOW)Compiling readline...$(RESET)"
	@echo "$(GREEN)Skipping...$(RESET)✅"
	@cd $(READLINE_D)
	@make --no-print-directory -C $(READLINE_D)
	@echo "$(GREEN)Readline ready$(RESET)✅"
else
	@echo "$(GREEN)Readline already built!$(RESET)✅"
	@echo "$(GREEN)Skipping...$(RESET)✅"
endif
endif
endif

print_message:
	$(PRINT_MINISHELL)
	$(PRINT_AUTHORS)

%.o: %.c
	@echo "$(YELLOW)Compiling...$(RESET)"
	@${CC} ${CFLAGS} -MMD $(INCLUDE) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT_D)$(LIBFT) $(READLINE_D)$(READLINE) $(READLINE_D)$(READLINE_H)
	@echo "$(YELLOW)Linking...$(RESET)"
	@$(CC) $(CFLAGS) $(READLINE_FLAGS) $(OBJS) -o $@ $(LIBFT_D)$(LIBFT) $(READLINE_D)$(READLINE) $(READLINE_D)$(READLINE_H) $(OFLAGS)
	@echo "$(GREEN)Linked!$(RESET)✅"
-include $(DEPS)

clean:
	@make clean --no-print-directory -C $(LIBFT_D)
	@make clean --no-print-directory -C $(READLINE_D)
	@echo "$(RED)Cleaned readline!$(RESET)✅"
	@$(RM) $(OBJS) $(DEPS)
	@echo "$(RED)Cleaned minishell!$(RESET)✅"

fclean: clean
	@make fclean --no-print-directory -C $(LIBFT_D)
	@$(RM) $(NAME) $(DEPS)
	@echo "$(RED)Fcleaned minishell!$(RESET)✅"

	
jesusg:
	@echo "$(VIOLET)Jesus is watching you...$(RESET)👀"
	@$(RM) -r $(OBJS_DIR) $(OBJS) $(DEPS)
	@echo "$(RED)Jesus has cleaned your soul!$(RESET)✅"

re: fclean all

.PHONY: all clean fclean re libft readline jesusg

# UBUNTU
# Print MINISHELL and authors' names
# MINISHELL_MSG = MINISHELL
# AUTHORS_MSG = by jpaul-kr & mcatalan
# MESSAGE_LEN = $$(($(shell echo $(MINISHELL_MSG) | wc -c) - 1))

# PRINT_MINISHELL = @printf "$(VIOLET)%*s$(RESET)\n" $(MESSAGE_LEN) $(MINISHELL_MSG)
# PRINT_AUTHORS = @echo "$(BLUE)$(AUTHORS_MSG)$(RESET)"

# # Colors
# RED = \033[0;31m
# GREEN = \033[0;32m
# YELLOW = \033[0;33m
# BLUE = \033[0;34m
# VIOLET = \033[0;35m
# RESET = \033[0m

# LIBFT_D = includes/libft/
# LIBFT = libft.a

# READLINE_FLAGS = 

# NAME = minishell

# SRCS =	$(wildcard src/*.c)

# OBJS = $(SRCS:.c=.o)

# DEPS = $(SRCS:.c=.d)

# INCLUDE = -I./
# RM = rm -f
# CFLAGS = -Wall -Wextra -Werror
# OFLAGS = -g -lreadline -L/usr/x86_64-linux-gnu 
# FFLAGS = -fsanitize=address

# all: print_message libft readline $(NAME)
# 	@echo "$(GREEN)Build finished successfully!$(RESET)✅"

# libft:
# 	@echo "$(YELLOW)Building libft...$(RESET)"
# 	@make --no-print-directory -C $(LIBFT_D)

# print_message:
# 	$(PRINT_MINISHELL)
# 	$(PRINT_AUTHORS)

# %.o: %.c
# 	@echo "$(YELLOW)Compiling...$(RESET)"
# 	@${CC} ${CFLAGS} -MMD $(INCLUDE) -c $< -o $@

# $(NAME): $(OBJS) $(LIBFT_D)$(LIBFT)
# 	@echo "$(YELLOW)Linking...$(RESET)"
# 	@$(CC) $(CFLAGS) $(OBJS) -o $@ $(LIBFT_D)$(LIBFT) $(OFLAGS) $(FFLAGS)
# 	@echo "$(GREEN)Linked!$(RESET)✅"
# -include $(DEPS)

# clean:
# 	@make clean --no-print-directory -C $(LIBFT_D)
# 	@echo "$(RED)Cleaned readline!$(RESET)✅"
# 	@$(RM) $(OBJS) $(DEPS)
# 	@echo "$(RED)Cleaned minishell!$(RESET)✅"

# fclean: clean
# 	@make fclean --no-print-directory -C $(LIBFT_D)
# 	@$(RM) $(NAME) $(DEPS)
# 	@echo "$(RED)Fcleaned minishell!$(RESET)✅"

# re: fclean all

# .PHONY: all clean fclean re libft readline 