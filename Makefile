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
RLFLAGS = -lreadline -ltermcap  -DREADLINE_LIBRARY#  -lreadline -L includes/readline/lib -lreadline -L includes/readline/lib -lhistory -L includes/readline/lib -ltermcap
RLURL = http://git.savannah.gnu.org/cgit/readline.git/snapshot/readline-bfe9c573a9e376323929c80b2b71c59727fab0cc.tar.gz

#Directories
SRC_DIR = src
OBJ_DIR = obj
DEP_DIR = dep
LIBFT_DIR = includes/libft/
RL_DIR = includes/readline/
RL_FILE = readline.tar
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
readline: | rl_decompress
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

rl_decompress:
	@echo "$(YELLOW)Decompressing readline...$(RESET)"
	@tar -xvf $(RL_FILE)
	@mv readline-* ./includes/readline
	@echo ✅

rl_download:
	@echo "$(YELLOW)Downloading readline...$(RESET)"
	@curl -k $(RLURL) > $(RL_FILE)
	@echo ✅

print_message:
	$(PRINT_MINISHELL)
	$(PRINT_AUTHORS)

-include $(DEPS)

$(NAME) : $(OBJ) $(READLINE)
	@echo "$(YELLOW)Linking...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ) $(READLINE) -o $@ $(RLFLAGS) -L $(LIBFT_DIR) -lft  ## -g -lreadline -L/usr/lib/x86_64-linux-gnu

clean :
	@echo "$(RED)Cleaning up objets and dependencies...$(RESET)"
	@$(RM) $(OBJ_DIR) $(DEP_DIR) $(RL_DIR)*.a
	@make -s -C $(LIBFT_DIR) clean
	@make -s -C $(RL_DIR) clean

fclean : clean
	@$(RM) $(NAME) $(READLINE)
	@make -s -C $(LIBFT_DIR) fclean

re : fclean all

rm_readline:
	@echo "$(RED)Removing readline...$(RESET)"
	@$(RM) $(RL_DIR)

$(OBJ_DIR) :
	@echo "$(YELLOW)Creating objects directory...$(RESET)"
	@mkdir -p $(OBJ_DIR)

$(DEP_DIR) :
	@echo "$(YELLOW)Creating dependencies directory...$(RESET)"
	@mkdir -p $(DEP_DIR)

.PHONY: clean fclean all re print_message rl_download rl_decompress readline rm_readline

# DEF_COLOR	:=	\033[1;97m
# PINK		:=	\033[1;95m
# GREEN		:=	\033[1;92m
# CIAN		:=	\033[1;96m

# NAME        = minishell

# HEADER      = ./includes/minishell.h ./includes/definitions.h ./include/structs.h

# SRC_PATH    = src/
# SRCS		= $(wildcard $(SRC_DIR)/*.c)

# LIBFT_PATH	= includes/libft/
# LIBFT		= $(LIBFT_PATH)/libft.a

# # PRINTF_PATH	= libs/ft_printf/
# # PRINTF		= $(PRINTF_PATH)/libftprintf.a

# RLINE_PATH	= includes/readline/
# RLINE		= $(RLINE_PATH)/libreadline.a
# RLINE_H		= $(RLINE_PATH)/libhistory.a

# LIB_PATH	= -L$(LIBFT_PATH) -L$(RLINE_PATH) 
# LIB_FLAGS	= $(LIBFT) $(PRINTF) -lreadline -ltermcap 

# OBJ_PATH	= ./OBJ/
# OBJ			= $(addprefix $(OBJ_PATH), $(SRC:.c=.o))
# DEP			= $(addprefix $(OBJ_PATH), $(OBJ:.o=.d))

# INC_PATH	= ./includes/ $(LIBFT_PATH) $(RLINE_PATH)
# INC			= $(addprefix -I, $(INC_PATH))

# CC			= gcc
# CFLAGS		= -Wall -Wextra -Werror -MMD 
# RM			= rm -f


# all: $(RLINE) $(OBJ_PATH) subsystems $(NAME)
	
# clean:
# 	@$(RM) $(OBJS) $(DEPS)
# 	@$(RM) -rf $(OBJ_PATH)
# 	@make -s -C $(LIBFT_PATH) clean
# 	@make -s -C $(PRINTF_PATH) clean
# 	@echo "$(PINK)Objects removed$(DEF_COLOR)"

# fclean: clean
# 	@$(RM) $(NAME)
# 	@make -s -C $(LIBFT_PATH) fclean
# 	@make -s -C $(PRINTF_PATH) fclean
# 	@echo "$(PINK)Minishell removed$(DEF_COLOR)"

# re: fclean all

# cleanrl:
# 	@make -s -C $(RLINE_PATH) mostlyclean
# 	@echo "$(PINK)READLINE removed$(DEF_COLOR)"

# $(NAME)::  $(OBJ) ./$(LIBFT) ./$(RLINE) ./$(RLINE_H)
# 	@$(CC) $(CFLAGS) $(^) -ltermcap -lreadline -o $(NAME)
# 	@echo "$(GREEN)MINISHELL compiled :D$(DEF_COLOR)"

# subsystems:
# 	@make -s -C $(LIBFT_PATH)

# $(OBJ_PATH):
# 	@mkdir -p $(OBJ_PATH)

# $(RLINE):
# 	@cd libs/readline && ./configure &>/dev/null
# 	@$(MAKE) -C $(RLINE_PATH) --no-print-directory
# 	@echo "$(CIAN)READLINE compiled$(DEF_COLOR)"

# $(OBJ_PATH)%.o: $(SRC_PATH)%.c Makefile $(HEADER)
# 	$(CC) $(CFLAGS) $(INC) -c $< -o $@

# -include ${DEP}

# # Phony
# .PHONY: all clean fclean re cleanrl