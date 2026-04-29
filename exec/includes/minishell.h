#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>
#include <dirent.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <termcap.h>
#include <errno.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <limits.h>
#include <stdbool.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE  200
# endif

extern volatile sig_atomic_t g_signal_received;

typedef enum e_sig_status
{
	INTERACTIVE,  // terwijl je kan type
	NON_INTERACTIVE, //tijdes execute
	IGNORE, //als je parent word moet je sigint en sigquit negeren
	CHILD, //ergens in the child code moet dit gedefineerd worde
	HEREDOC_SIG //heredoc werkt bijna t zelfde als interactive maar geeft een bepaalde exit code (130)
}			t_sig_status;

typedef enum	e_token_type
{
    WORD,
    PIPE,
    REDIR_OUT_TRUNC,   /* >  canonical */
    REDIR_OUT_APP,     /* >> canonical */
    REDIR_IN,          /* < */
    HEREDOC, /* << eof */
    HEREDOC_NO_EXPANSION, /* << 'eof' || << "eof" */

    ENVIRONMENT,
}               t_token_type;

typedef enum	e_sig_kind
{
    HEREDOC_INT,
	INTERACTIVE_INT,
	INTERACTIVE_KILL,
	NOTHING,
}               t_sig_kind;



/* Backwards-compat aliases used across the codebase */
#define REDIR_OUT_TRUNCT REDIR_OUT_TRUNC
#define REDIR_OUT_APPEND REDIR_OUT_APP

typedef struct  s_token
{
    char            *value;
    t_token_type    type;
    struct s_token  *next;
    int             heredoc_fd; /* present in exec implementation */
    char            *filename;  /* optional filename for redirections */
}               t_token;

typedef struct s_exec_info
{
    char    *str;
    t_token *start;
    t_token *end;
    int     fd_in;
    int     fd_out;
    int     command_number;
    int     words;
    char    **arguments;
}               t_exec_info;

typedef struct s_single_fds
{
    int fd_in;
	int fd_out;
	int	std_out;
	int std_in;
}  				t_single_fds;

typedef struct s_data
{
	    /* exec-related */
    int			**pipes;
    pid_t		*pids;
    char		**envp;
    long		shutdown;
    int			exit_code;
    t_token		*head;
    int			nmb_of_pipes;
    char		*line;
    int			index;
	int			level;
	t_sig_kind	sig;
	    /* parser-related */
    int     		shell_level;
    t_token 		*current;
}   t_data;

//main.c
int	main(int argc, char *argv[], char *envp[]);
int		main_loop(t_data *data);
int	get_input(t_data *data);
int	execute_input(t_data *data);

int ft_start_exec(t_token *head, t_data *data);

/* free.c */
void    ft_free_arr(void **array);
void    ft_free_r(void **array, int i);
void    ft_free_tokens(t_token *head, t_data *data);
void    ft_cleanup(t_token *head, t_data *data, int nmb_of_pipes);
void    ft_child_builtin_cleanup(t_data *data, char **arguments);

/* pipes.c */
int ft_find_pipes(t_token *head);
int ft_create_pipes_and_pids(int number, t_data *data);
int ft_setup_pipes(t_data *data, int nmb_of_pipes, int i);
void ft_close_all_pipes(t_data *data, int nmb_of_pipes);

/* dummy.c */
t_token *ft_get_head();
t_token *create_token(char *value, t_token_type type);

/* helper.c */
int     ft_strncmp(const char *s1, const char *s2, size_t n);
size_t  ft_strlen(const char *str);
char    *ft_strchr(const char *str, int c);
char    *ft_strdup(const char *s);
int     ft_isdigit(int c);
int     ft_isalpha(int c);
char    *ft_substr(char const *str, int start, int length);
int     ft_isalnum(int c);
void    *ft_memcpy(void *to, const void*from, size_t bytes);

void    *ft_calloc(size_t nmemb, size_t size);
int     check_delimeters(char c);
char    *ft_strjoin(char const *s1, char const *s2);
int     ft_copy_envp(t_data *data, char **envp);

/* childs.c */
int ft_child_process(t_token *head, t_data *data, int i);
void ft_execution_failure(char *executable, char **arguments);

/* split.c */
char    **ft_split(const char *str, char);

/* ft_strjoin.c */

/* redirection.c */
int ft_handle_in(int *fd_in, t_token *curr);
int ft_handle_in_heredoc(int *fd_in, t_token *curr);
int ft_handle_out_app(int *fd_out, t_token *curr);
int ft_handle_out_trunc(int *fd_out, t_token *curr);
int ft_apply_redirection(int *fd_in, int *fd_out, t_token *curr);

/* executable.c */
char *ft_relative_executable(char *command);
char *ft_make_executable(char *executable, t_data *data);
void ft_check_builtins(t_exec_info *exec_info, t_data *data, char **arguments);
char *ft_decide_executable(char *command, t_data *data);

/*executable_relative.c*/
char *ft_relative_executable(char *command);
void ft_relative_executable_help(char *command);

/* builtins */
void ft_builtin_cd(t_exec_info *exec_info, t_data *data, char **arguments);
void ft_builtin_export(t_data *data, char **arguments);
void ft_builtin_unset(t_data *data, char **arguments);
void ft_builtin_echo(t_data *data, char **arguments);
void ft_builtin_exit(t_exec_info *exec_info, t_data *data, char **arguments);
void ft_builtin_env(t_data *data, char **arguments);
void ft_builtin_pwd(t_data *data, char **arguments);

/* single builtins */
int ft_check_single_builtin(char **arguments);
int ft_check_builtins_before_fork(t_token *head, t_data *data);
void ft_single_builtin(t_token *head, t_data *data);
int ft_count_single_words(t_token *head);
int ft_execute_single_builtin(int words, char **arguments, t_data *data);

/* builtin_single.* */
void ft_builtin_single_exit(int words, char **arguments, t_data *data);
void ft_builtin_single_echo(char **arguments, t_data *data);
void ft_builtin_single_unset(char **arguments, t_data *data);
void ft_builtin_single_export(char **arguments, t_data *data);
void ft_builtin_single_cd(int words, char **arguments, t_data *data);
int ft_builtin_single_pwd(t_data *data);
void ft_builtin_single_env(char **arguments, t_data *data);

/*single_builtin_fds.c*/
int ft_single_redirection(t_token *curr, int *fd_in, int *fd_out, t_data *data);
void	ft_builtin_fds(t_single_fds fds, int words, char **arguments, t_data *data);

/* cd.c */
int ft_cd_no_arguments(t_data *data);
int ft_cd_one_argument(char **arguments, t_data *data);

/* env_list */
char *ft_getenv(t_data *data, char *var);
int ft_extend_env(t_data *data, char *entry);
int ft_change_env_key_value(char *key, char *value, t_data *data);
int ft_change_env_key(char *entry, t_data *data);

/* ft_strl* helpers */
size_t  ft_strlcat(char *dst, const char *src, size_t size);
size_t  ft_strlcpy(char *dst, const char *src, size_t size);

/* export/unset/echo */
int ft_add_to_export_list(char **arguments, t_data *data);
int ft_export_print_list(t_data *data);
void ft_unset(char **args, t_data *data);
int ft_echo_newline(char **arguments, int i);
int ft_echo_no_arguments();
int ft_echo_no_newline(char **arguments, int i);
int ft_check_echo_option(char **arguments);
int ft_export_print_list(t_data *data);

/* ft_atol / ft_itoa */
int	ft_exit_code_atol(const char *ptr);
char *ft_itoa(int n);
int	ft_atoi(const char *ptr);

/* heredoc */
int handle_heredoc(t_token *head, t_data *data);
void ft_close_heredoc_fds(t_token *head);

/* expansions (parser + exec) */
void	check_expansions(t_data *d);
bool    convert_expansions(t_data *d, int start);
char    *get_key(char *line, int start);
bool    replace_key_in_line(t_data *d, char *value, int start, int key_len);
bool	remove_quotes_from_empty_key(t_data *d, int start);

/* readline tering zooi wat enn kk functie*/
char    *get_line(t_data *data);
char	*safe_readline(void);

/* tokenization helpers */
t_token *classify_and_make(t_data *d, char *line);
t_token *tokenize_input(t_data *d, char *str);
t_token *if_redirection(t_data *d, int start, char *line, t_token_type type);
t_token *if_word(t_data *d, int start, char *line);
t_token *make_new_token(char *value, t_token_type type);
t_token *if_quotes(t_data *d, char *line, int start);
int		check_closed_quotes(char *line);

/*quotes*/
t_token	*make_word_token_with_quotes(t_data *d, char *line, int start);

/* misc */
int index_to_char(char *str, char c);

/* signals*/
void	setup_signals(t_sig_status	type);
int		heredoc_signal_hook(void);
int		interactive_signal_hook(void);

size_t		ft_strlen(const char *str);
char		*get_next_line(int fd);
char		*ft_strchr(const char *str, int c);
void		*ft_calloc(size_t nmemb, size_t size);
char		*free_left(char **left);
char		*free_left(char **left);

/*wait children.c*/
int	ft_wait_all_children(t_data *data, int nmb_of_pipes);


#endif
