#ifndef PARSER_H
# define PARSER_H

#include "minishell.h"
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
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>

// < infile< infile2.txt < infile3 wc <infile4 -l |  wc -l  | wc -l > outfile

#endif

// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <fcntl.h>
// #include <signal.h>
// #include <string.h>
// #include <dirent.h>
// #include <sys/wait.h>
// #include <sys/stat.h>
// #include <sys/ioctl.h>
// #include <termios.h>
// #include <termcap.h>
// #include <errno.h>
// #include <readline/readline.h>
// #include <readline/history.h>
// #include <stdbool.h>
// // < infile <infile2 < infile3 wc <infile4 -l |  wc -l  | wc -l > outfile

// typedef enum	e_token_type
// {
//     WORD,
//     PIPE,
//     REDIR_OUT_TRUNCT, 		// >
//     REDIR_OUT_APPEND,		// >>
//     REDIR_IN,				// <
//     HEREDOC_EXPANSION,		// << eof
// 	HEREDOC_NO_EXPANSION,	// << 'eof' || << "eof"
// 	ENVIRONMENT,
// }				t_token_type;

// typedef struct	s_token
// {
//     char            *value;
//     t_token_type    type;
//     struct s_token  *next;
// 	int				heredoc_fd;
// 	char			*filename;
// }				t_token;

// typedef struct	s_exec_info
// {
// 	char	*str;
// 	t_token	*start;
// 	t_token	*end;
// 	int		fd_in;
// 	int		fd_out;
// 	int		command_number;
// 	int		words;
// 	char	**arguments;
// }				t_exec_info;

// typedef struct s_data
// {
// 	int		**pipes;
// 	pid_t	*pids;
// 	char	**envp;
// 	long	shutdown;
// 	int		exit_code;
// 	t_token *head;
// 	int		nmb_of_pipes;
// 	char	*line;
// 	int		index;
// }	t_data;

// //free.c
// void	ft_free_arr(void **array);
// void	ft_free_r(void **array, int i);
// void ft_free_tokens(t_token *head);
// void ft_cleanup(t_token *head, t_data *data, int nmb_of_pipes);
// void ft_child_builtin_cleanup(t_data *data, char **arguments);

// //pipes.c
// int	ft_find_pipes(t_token *head);
// int ft_create_pipes_and_pids(int number, t_data *data);
// int ft_setup_pipes(t_data *data, int nmb_of_pipes, int i);
// void ft_close_all_pipes(t_data *data, int nmb_of_pipes);

// //dummy.c
// t_token	*ft_get_head();
// t_token	*create_token(char *value, t_token_type type);

// //helper.c
// void	*ft_calloc(size_t nmemb, size_t size);
// int		ft_strncmp(const char *s1, const char *s2, size_t n);
// size_t	ft_strlen(const char *str);
// char	*ft_strchr(const char *str, int c);
// char	*ft_strdup(const char *s);
// int	ft_isdigit(int c);
// int	ft_isalpha(int c);
// char	*ft_substr(char const *str, int start, int length);
// int	ft_isalnum(int c);
// void	*ft_memcpy(void	*to, const void*from, size_t bytes);
// int		check_delimeters(char c);

// //childs.c
// int	ft_child_process(t_token *head, t_data *data, int i);
// void ft_execution_failure(char *executable, char **arguments);

// //split.c
// char	**ft_split(const char *str, char);

// //ft_strjoin.c
// char	*ft_strjoin(char const *s1, char const *s2);

// //redirection.c
// int ft_handle_in(int *fd_in, t_token *curr);
// int ft_handle_in_heredoc(int *fd_in, t_token *curr);
// int ft_handle_out_app(int *fd_out, t_token *curr);
// int ft_handle_out_trunc(int *fd_out, t_token *curr);
// int ft_apply_redirection(int *fd_in, int *fd_out, t_token *curr);

// //executable.c
// char *ft_relative_executable(char *command);
// char *ft_make_executable(char *executable, t_data *data);
// void ft_check_builtins(t_exec_info *exec_info, t_data *data, char **arguments);
// char *ft_decide_executable(char *command, t_data *data);

// //built_in.c
// void ft_builtin_cd(t_exec_info *exec_info, t_data *data, char **arguments);
// void ft_builtin_export(t_data *data, char **arguments);
// void ft_builtin_unset(t_data *data, char **arguments);
// void ft_builtin_echo(t_data *data, char **arguments);
// void ft_builtin_exit(t_exec_info *exec_info, t_data *data, char **arguments);

// //built_in2.c
// void ft_builtin_env(t_data *data, char **arguments);
// void ft_builtin_pwd(t_data *data, char **arguments);

// //single_builtin_execution.c
// int ft_check_single_builtin(char **arguments);
// int ft_check_builtins_before_fork(t_token *head, t_data *data);
// void ft_single_builtin(t_token *head, t_data *data);
// int ft_count_single_words(t_token *head);

// //builtin_single.c
// void ft_builtin_single_exit(int words, char **arguments, t_data *data);
// void ft_builtin_single_echo(char **arguments, t_data *data);
// void ft_builtin_single_unset(char **arguments, t_data *data);
// void ft_builtin_single_export(char **arguments, t_data *data);
// void ft_builtin_single_cd(int words, char **arguments, t_data *data);

// //builtin_single2.c
// int ft_builtin_single_pwd(t_data *data);
// void ft_builtin_single_env(char **arguments, t_data *data);

// //cd.c
// int ft_cd_no_arguments(t_data *data);
// int ft_cd_one_argument(char **arguments, t_data *data);

// //env_list
// char *ft_getenv(t_data *data, char *var);
// int ft_extend_env(t_data *data, char *entry);
// int ft_change_env_key_value(char *key, char *value, t_data *data);
// int ft_change_env_key(char *entry, t_data *data);

// //ft_strjoin.c
// size_t	ft_strlcat(char *dst, const char *src, size_t size);
// size_t	ft_strlcpy(char *dst, const char *src, size_t size);

// //export.c
// int ft_add_to_export_list(char **arguments, t_data *data);
// int ft_export_print_list(t_data *data);

// //unset.c
// void ft_unset(char **args, t_data *data);

// //echo.c
// int ft_echo_newline(char **arguments, int i);
// int ft_echo_no_arguments();
// int ft_echo_no_newline(char **arguments, int i);
// int ft_check_echo_option(char **arguments);

// //ft_atol.c
// int	ft_atol(const char *ptr);

// //ft_itoa.c
// char	*ft_itoa(int n);

// //heredoc.c
// int handle_heredoc(t_token *head, t_data *data);
// void ft_close_heredoc_fds(t_token *head);

// //expansion.c
// char	*get_key(char *line, int start);

// //expansions
// char	*check_expansions(t_data *data);
// bool	convert_expansions(t_data *d, int start);
// char 	*ft_getenv(t_data *data, char *var);
// char	*get_key(char *line, int start);
// bool	replace_key_in_line(t_data *d, char *value, int start, int val_len, int key_len);



// #endif