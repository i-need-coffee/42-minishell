# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sjolliet <sjolliet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/06/28 18:50:42 by jturrel           #+#    #+#              #
#    Updated: 2026/08/21 22:04:13 by sjolliet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell

CC				= cc
CFLAGS			= -Wall -Wextra -Werror -g -Iinclude -Ilibft/include

LIBFT_DIR		= libft
LIBFT			= $(LIBFT_DIR)/libft.a

SRC_DIR			= src
OBJ_DIR			= obj

SRCS			= \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/utils/misc.c \
	$(SRC_DIR)/utils/cleanup.c \
	$(SRC_DIR)/utils/errors.c \
	$(SRC_DIR)/tokenization/tokenize_input.c \
	$(SRC_DIR)/tokenization/utils.c \
	$(SRC_DIR)/tokenization/add_word_token.c \
	$(SRC_DIR)/signals/signal_config.c \
	$(SRC_DIR)/env/environement.c \
	$(SRC_DIR)/env/utils_node.c \
	$(SRC_DIR)/parsing/parsing.c \
	$(SRC_DIR)/parsing/parsing_utils.c \
	$(SRC_DIR)/parsing/handle_literal.c \
	$(SRC_DIR)/parsing/parsing_word_token.c \
	$(SRC_DIR)/parsing/expension.c \
	$(SRC_DIR)/parsing/handle_quote.c \
	$(SRC_DIR)/parsing/parse_pipe_token.c \
	$(SRC_DIR)/parsing/parse_redirection_token.c \
	$(SRC_DIR)/parsing/wrapper.c \
	$(SRC_DIR)/parsing/expension_utils.c \
	$(SRC_DIR)/parsing/redirection_utils/common_redirection_utils.c \
	$(SRC_DIR)/execution/execute_input.c \
	$(SRC_DIR)/execution/heredoc.c \
	$(SRC_DIR)/execution/utils.c \
	$(SRC_DIR)/execution/children.c \
	$(SRC_DIR)/execution/files.c \
	$(SRC_DIR)/execution/exec.c \
	$(SRC_DIR)/execution/dup.c \
	$(SRC_DIR)/built-in/execute_built_in.c \
	$(SRC_DIR)/built-in/echo.c \
	$(SRC_DIR)/built-in/pwd.c \
	$(SRC_DIR)/built-in/cd.c \
	$(SRC_DIR)/built-in/utils.c \
	$(SRC_DIR)/built-in/env.c \
	$(SRC_DIR)/built-in/unset.c \
	$(SRC_DIR)/built-in/export.c \
	$(SRC_DIR)/built-in/export_one_arg.c \
	$(SRC_DIR)/built-in/exit_minishell.c

OBJS			= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# **************************************************************************** #

all: $(NAME)

$(LIBFT):
	@echo "📚 Building Libft..."
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory
	@echo "📚 Libft compiled successfully!"

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)
	@echo "🚀 $(NAME) compiled successfully!"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INC_FLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory
	@echo "🧹 Object files removed."

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@echo "🗑️  Library and executables removed."

re: fclean all

leaks: re
	valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes ./minishell

.PHONY: all clean fclean re leaks
