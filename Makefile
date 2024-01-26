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

# Print MINISHELL and authors' names
MINISHELL_MSG = MINISHELL
AUTHORS_MSG = by jpaul-k & mcatalan
MESSAGE_LEN = $$(($(shell echo $(MINISHELL_MSG) | wc -c) - 1))

PRINT_MINISHELL = @printf "$(VIOLET)%*s$(RESET)\n" $(MESSAGE_LEN) $(MINISHELL_MSG)
PRINT_AUTHORS = @echo "$(BLUE)$(AUTHORS_MSG)$(RESET)"

# Name of the executable && compiler && flags
NAME = minishell
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g -fsanitize=address
RM = rm -rf
RLFLAGS = -lreadline -ltermcap ##  -lreadline -L includes/readline/lib -lreadline -L includes/readline/lib -lhistory -L includes/readline/lib -ltermcap
RLURL = http://git.savannah.gnu.org/cgit/readline.git/snapshot/readline-bfe9c573a9e376323929c80b2b71c59727fab0cc.tar.gz

#Directories
SRC_DIR = src
OBJ_DIR = obj
DEP_DIR = dep
LIBFT_DIR = includes/libft/
RL_DIR = includes/readline/
RL_FILE = readline.tar.gz
READLINE = $(RL_DIR)libreadline.a $(RL_DIR)libhistory.a

# Colors
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
VIOLET = \033[0;35m
RESET = \033[0m

SRC = $(wildcard $(SRC_DIR)/*.c)

OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))

DEPS = $(addprefix $(DEP_DIR)/, $(notdir $(SRC:.c=.d)))

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c Makefile | $(OBJ_DIR) $(DEP_DIR)
	@echo "$(YELLOW)Compiling...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@ -MMD

all : print_message readline subsystem $(NAME)
	@echo "$(GREEN)Build finished successfully!$(RESET)✅"

subsystem:
	@echo "$(YELLOW)Building libft...$(RESET)"
	@make -s -C $(LIBFT_DIR)
	@echo ✅

ifeq ($(wildcard $(RL_DIR)),)
readline: | rl_download
	@cd ./$(RL_DIR) && ./configure &> /dev/null && make
else
ifeq ($(wildcard $(RL_DIR)/config.status),)
readline:
	@echo "$(YELLOW)Configuring readline...$(RESET)"
	cd $(RL_DIR) && ./configure && make
else ifeq ($(wildcard $(RL_DIR)/libreadline.a),)
readline:
	@echo "$(GREEN)Readline is already configured!$(RESET)✅"
	cd $(RL_DIR) && make
else
readline:
	@echo "$(GREEN)Readline is already built!$(RESET)✅"
	@echo "$(GREEN)Skipping...$(RESET)"
	@echo ✅
endif
endif

rl_download:
	@echo "$(YELLOW)Downloading readline...$(RESET)"
	@cd includes
	@curl -k $(RLURL) > $(RL_FILE)
	@tar -xvf $(RL_FILE)
	@mv readline-* ./includes/readline
	@rm $(RL_FILE)
	@echo ✅

print_message:
	$(PRINT_MINISHELL)
	$(PRINT_AUTHORS)

-include $(DEPS)

$(NAME) : $(OBJ) $(READLINE)
	@echo "$(YELLOW)Linking...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ) $(READLINE) -o $@ $(RLFLAGS) -L $(LIBFT_DIR) -lft

clean :
	@echo "$(RED)Cleaning up objets and dependencies...$(RESET)"
	@$(RM) $(OBJ_DIR) $(DEP_DIR) $(RL_DIR)*.a
	@make -s -C $(LIBFT_DIR) clean

fclean : clean
	@$(RM) $(NAME) $(READLINE)
	@make -s -C $(LIBFT_DIR) fclean

re : fclean all

rm_download:
	@echo "$(RED)Removing readline...$(RESET)"
	@$(RM) $(RL_DIR)

$(OBJ_DIR) :
	@echo "$(YELLOW)Creating objects directory...$(RESET)"
	@mkdir -p $(OBJ_DIR)

$(DEP_DIR) :
	@echo "$(YELLOW)Creating dependencies directory...$(RESET)"
	@mkdir -p $(DEP_DIR)

.PHONY: clean fclean all re print_message rl_download readline rm_download