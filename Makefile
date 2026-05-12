NAME			= minishell

CC				= cc
CFLAGS			= -Wall -Wextra -Werror -g -Iinclude -Ilibft/include

LIBFT_DIR		= libft
LIBFT			= $(LIBFT_DIR)/libft.a

SRC_DIR			= src
OBJ_DIR			= obj

SRCS			= \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/utils.c \
	$(SRC_DIR)/tokenization/tokenize_input.c \
	$(SRC_DIR)/tokenization/utils.c \
	$(SRC_DIR)/tokenization/add_word_token.c\
	$(SRC_DIR)/signals/signal_config.c

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
	@$(CC) $(CFLAGS) -c $< -o $@

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
	valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all --track-origins=yes --trace-children=yes --track-fds=yes ./minishell

.PHONY: all clean fclean re leaks