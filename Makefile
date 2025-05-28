NAME		= philo

CC			= cc
CFLAGS		= -Wall -Wextra -Werror

# Directories
OBJ_DIR		= .obj

# Header files
HEADERS		= philo.h

# Source files
SRC			= main.c parsing.c threading.c utils.c \
			set_philos.c

# Object files
OBJ			= $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

# Colors for terminal output
GREEN		= \033[32m
YELLOW		= \033[33m
RESET		= \033[0m

# Rules
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "$(GREEN)Compilation complete. Executable '$(NAME)' created.$(RESET)"

# This pattern rule ensures source files are recompiled if headers or Makefile change
$(OBJ_DIR)/%.o: %.c $(HEADERS) Makefile
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(YELLOW)Object files removed.$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(YELLOW)Executable '$(NAME)' removed.$(RESET)"

re: fclean all

.PHONY: all clean fclean re