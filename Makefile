NAME = minishell
CC = cc
CFLAGS = -Wall -Werror -Wextra -g
LDFLAGS = -lreadline

SRCDIR = src
OBJDIR = obj
INCDIR = inc

LIBFT_DIR = lib
LIBFT_OBJ = $(LIBFT_DIR)/$(OBJDIR)
LIBFT_A = $(LIBFT_DIR)/libft.a
LIBFT_INC = -I$(LIBFT_DIR)
INCLUDES = -I$(INCDIR) $(LIBFT_INC)

SRC = \
	src/cmd/bin_cd.c \
	src/cmd/bin_cd_helpers.c \
	src/cmd/bin_echo.c \
	src/cmd/bin_env.c \
	src/cmd/bin_exit.c \
	src/cmd/bin_export.c \
	src/cmd/bin_export_helpers.c \
	src/cmd/bin_pwd.c \
	src/cmd/bin_unset.c \
	src/env/env_array.c \
	src/env/env_list.c \
	src/env/env_modifier.c \
	src/env/env_utils.c \
	src/exec/exec_builtin.c \
	src/exec/exec_cmd.c \
	src/exec/exec_flow.c \
	src/exec/exec_utils.c \
	src/exec/handle_assignments.c \
	src/exec/handle_fds.c \
	src/exec/handle_heredocs.c \
	src/exec/handle_paths.c \
	src/exec/handle_pipes.c \
	src/exec/handle_redirections.c \
	src/help/free_helpers.c \
	src/help/init_shell.c \
	src/help/utils.c \
	src/main/main.c \
	src/pars/expand_env.c \
	src/pars/expand_env_helpers.c \
	src/pars/lexer.c \
	src/pars/lexer_helpers.c \
	src/pars/parse_checks.c \
	src/pars/parse_cmd_list.c \
	src/pars/parse_helpers.c \
	src/pars/parse_syntax.c \
	src/pars/parse_tokens.c \
	src/pars/signals.c

OBJ = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_A)
	@echo "\033[1;34m 🚀🚀🚀 Building $(NAME)...\033[0m"
	@echo ""
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) $(LIBFT_A) -o $(NAME) $(LDFLAGS)
	@echo "\t \033[1;32m✅ Build complete!\033[0m"
	@echo "\033[1;36m▶️  $(NAME)\033[0m is now ready !"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT_A):
	@mkdir -p $(LIBFT_OBJ)
	@$(MAKE) -s -C $(LIBFT_DIR) OBJDIR=$(OBJDIR)

clean:
	@rm -rf $(OBJDIR)
	@$(MAKE) -s clean -C $(LIBFT_DIR) OBJDIR=$(OBJDIR)

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -s fclean -C $(LIBFT_DIR) OBJDIR=$(OBJDIR)

rebuild:
	@rm -rf $(OBJDIR)
	@rm -f $(NAME)
	@$(MAKE)

re: fclean all

.PHONY: all clean fclean re
