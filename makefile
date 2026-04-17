################################################################################
# Makefile for minishell
# - exec sources in exec/src
# - parser sources in parser/src
# - object files in exec/obj and parser/obj
# - dependency files in exec/dep and parser/dep
# - headers in exec/includes and parser/includes
################################################################################

CC := cc
CFLAGS := -Wall -Wextra -Werror -g -I exec/includes -I parser/includes

NAME := minishell

SRC_DIR_E := exec/src
OBJ_DIR_E := exec/obj
DEP_DIR_E := exec/dep
BUILTINS_DIR_E := exec/src/built-ins

SRC_DIR_P := parser/src
OBJ_DIR_P := parser/obj
DEP_DIR_P := parser/dep

LDLIBS := -lreadline -lhistory

# exec sources
SRC_FILES_E := \
	child.c \
	dummy.c \
	env_list.c \
	executable.c \
	ft_atol.c \
	ft_split.c \
	ft_strjoin.c \
	helper.c \
	main.c \
	pipes.c \
	redirection.c \
	test.c \
	free.c \
	ft_itoa.c \
	heredoc.c \


# builtins sources
BUILTINS_SRC_FILES_E := \
	built_in.c \
	built_in2.c \
	builtin_single.c \
	builtin_single2.c \
	export.c \
	cd.c \
	echo.c \
	single_builtin_execution.c \
	unset.c

# parser sources
SRC_FILES_P := \
	loop_shell.c \
	token_funcs.c \
	token_garbage.c \
	expansion.c

# object files
OBJS_E := $(addprefix $(OBJ_DIR_E)/, $(SRC_FILES_E:.c=.o) $(BUILTINS_SRC_FILES_E:.c=.o))
OBJS_P := $(addprefix $(OBJ_DIR_P)/, $(SRC_FILES_P:.c=.o))

# dependency files
DEPS_E := $(addprefix $(DEP_DIR_E)/, $(SRC_FILES_E:.c=.d) $(BUILTINS_SRC_FILES_E:.c=.d))
DEPS_P := $(addprefix $(DEP_DIR_P)/, $(SRC_FILES_P:.c=.d))

OBJS := $(OBJS_E) $(OBJS_P)
DEPS := $(DEPS_E) $(DEPS_P)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS) | $(OBJ_DIR_E) $(DEP_DIR_E) $(OBJ_DIR_P) $(DEP_DIR_P)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDLIBS)

$(OBJ_DIR_E):
	@mkdir -p $(OBJ_DIR_E)

$(DEP_DIR_E):
	@mkdir -p $(DEP_DIR_E)

$(OBJ_DIR_P):
	@mkdir -p $(OBJ_DIR_P)

$(DEP_DIR_P):
	@mkdir -p $(DEP_DIR_P)

$(OBJ_DIR_E)/%.o: $(SRC_DIR_E)/%.c | $(OBJ_DIR_E) $(DEP_DIR_E)
	$(CC) $(CFLAGS) -c $< -o $@ -MMD -MP -MF $(DEP_DIR_E)/$*.d

$(OBJ_DIR_E)/%.o: $(BUILTINS_DIR_E)/%.c | $(OBJ_DIR_E) $(DEP_DIR_E)
	$(CC) $(CFLAGS) -c $< -o $@ -MMD -MP -MF $(DEP_DIR_E)/$*.d

$(OBJ_DIR_P)/%.o: $(SRC_DIR_P)/%.c | $(OBJ_DIR_P) $(DEP_DIR_P)
	$(CC) $(CFLAGS) -c $< -o $@ -MMD -MP -MF $(DEP_DIR_P)/$*.d

clean:
	rm -f $(OBJS)
	rm -rf $(DEP_DIR_E) $(DEP_DIR_P)

fclean: clean
	rm -f $(NAME)
	rm -rf $(OBJ_DIR_E) $(OBJ_DIR_P)

re: fclean all

-include $(DEPS)