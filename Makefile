################################################################################
# Makefile for minishell
# - lists all .c files once in `SRC_FILES`
# - object files go to `obj/`
# - dependency files go to `dep/`
# - headers in `includes/`
################################################################################

CC := cc
CFLAGS := -Wall -Wextra -Werror -g -I exec/includes
NAME := minishell

SRC_DIR_E := exec/src
OBJ_DIR_E := exec/obj
DEP_DIR_E := exec/dep
BUILTINS_DIR:= exec/src/built-ins
SRC_DIR_P := parser/src
OBJ_DIR_P := parser/obj
DEP_DIR_P := parser/dep
INCLUDES := exec/includes
LDLIBS  = -lreadline -lhistory
HEADERS := $(INCLUDES)/exec.h

# List sources once by directory (basenames)
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
	expansion.c

BUILTINS_SRC_FILE_E := \
	built_in.c \
	built_in2.c \
	builtin_single.c \
	builtin_single2.c \
	export.c \
	cd.c \
	echo.c \
	single_builtin_execution.c \
	unset.c

SRC_FILES_P := \
	loop_shell.c \
	token_funcs.c \
	token_garbage.c \
	expansion.c \
	signal_funcs.c \
	read_line.c

# Object filenames: place in obj/ with same basenames
OBJS_E := $(addprefix $(OBJ_DIR_E)/, $(SRC_FILES_E:.c=.o) $(BUILTINS_SRC_FILES:.c=.o))
OBJS_P := $(addprefix $(OBJ_DIR_P)/, $(SRC_FILES_P:.c=.o))
# Dependency files (one per object) in dep/
DEPS_E := $(addprefix $(DEP_DIR_E)/, $(SRC_FILES_E:.c=.d) $(BUILTINS_SRC_FILES:.c=.d))
DEPS_P := $(addprefix $(DEP_DIR_P)/, $(SRC_FILES_P:.c=.d))

.PHONY: all clean fclean re obj dep

all: $(NAME)

$(NAME): $(OBJS_E) $(OBJS_P) | $(OBJ_DIR_E) $(DEP_DIR_E) $(OBJ_DIR_P) $(DEP_DIR_P)
	$(CC) $(CFLAGS) $(OBJS_E) $(OBJS_P) -o $(NAME) $(LDLIBS)

$(OBJ_DIR_E):
	@if [ ! -d $(OBJ_DIR_E) ]; then echo "creating $(OBJ_DIR_E)"; mkdir -p $(OBJ_DIR_E); fi

$(OBJ_DIR_P):
	@if [ ! -d $(OBJ_DIR_P) ]; then echo "creating $(OBJ_DIR_P)"; mkdir -p $(OBJ_DIR_P); fi

$(DEP_DIR_E):
	@if [ ! -d $(DEP_DIR_E) ]; then echo "creating $(DEP_DIR_E)"; mkdir -p $(DEP_DIR_E); fi

$(DEP_DIR_P):
	@if [ ! -d $(DEP_DIR_P) ]; then echo "creating $(DEP_DIR_P)"; mkdir -p $(DEP_DIR_P); fi

# Pattern rules: compile from src/ or src/built-ins/ to obj/
$(OBJ_DIR_E)/%.o: $(SRC_DIR_E)/%.c | $(OBJ_DIR_E) $(DEP_DIR_E)
	$(CC) $(CFLAGS) -c $< -o $@ -MMD -MP -MF $(DEP_DIR_E)/$*.d

$(OBJ_DIR_P)/%.o: $(SRC_DIR_P)/%.c | $(OBJ_DIR_P) $(DEP_DIR_P)
	$(CC) $(CFLAGS) -DBUILD_PARSER -c $< -o $@ -MMD -MP -MF $(DEP_DIR_P)/$*.d

$(OBJ_DIR_E)/%.o: $(BUILTINS_DIR)/%.c | $(OBJ_DIR_E) $(DEP_DIR_E)
	$(CC) $(CFLAGS) -c $< -o $@ -MMD -MP -MF $(DEP_DIR_E)/$*.d

clean:
	rm -f $(OBJS_E) $(OBJS_P)
	rm -rf $(DEP_DIR_E) $(DEP_DIR_P)

fclean: clean
	rm -f $(NAME)

re: fclean all

# Include dependency files if they exist (ignore missing files)
-include $(DEPS_E) $(DEPS_P)

