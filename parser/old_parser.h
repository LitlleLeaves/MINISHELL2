// #ifndef	MINISHELL_H
// # define MINISHELL_H

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
// #include <readline/readline.h>
// #include <readline/history.h>
// #include <limits.h>
// #include <stdbool.h>

// typedef enum	e_token_type
// {
//     WORD,
//     PIPE,
//     REDIR_OUT_TRUNC, 	// >
//     REDIR_OUT_APP,		// >>
//     REDIR_IN,			// <
//     HEREDOC_EXPANSION,		// << eof
// 	HEREDOC_NO_EXPANSION,	// << 'eof' || << "eof"

// 	ENVIRONMENT,
// }				t_token_type;

// typedef struct	s_token
// {
//     char            *value;
//     t_token_type    type;
//     struct s_token  *next;
// }				t_token;

// typedef struct	s_data
// {
// 	int		shell_level;
// 	int		exit_val;
// 	int		index;
// 	t_token	*head;
// 	char	**envp;
// 	t_token	*current;
// 	char	*line;
// }				t_data;

// //main
// int		main_loop(char	*envp[]);

// //read input
// char	*get_line(void);
// int		ft_copy_envp(t_data *data, char **envp);

// //tokens
// t_token	*classify_and_make(t_data *d, char *line);
// t_token	*tokenize_input(t_data *d, char *str);
// int		check_delimeters(char c);
// t_token *if_redirection(t_data *d, int start, char *line, t_token_type type);
// t_token	*if_word(t_data *d, int start, char *line);
// t_token	*make_new_token(char *value, t_token_type type);
// t_token	*if_quotes(t_data *d, char *line, int start);
// //t_token	*if_pipe(char *line);

// //token_indexer
// //int		index_to_next_delimeter(char *line, int index);
// //int		move_over_quotes(char *line, int index);

// //ft_helpers
// char	*ft_strdup(char const *str);
// int		ft_strlen(char const *str);
// char	*ft_strjoin(char const *s1, char const *s2);
// char	*ft_substr(char const *str, int start, int length);
// int		ft_strncmp(const char *s1, const char *s2, size_t n);
// void	*ft_calloc(size_t nmemb, size_t size);

// //expansions
// char	*check_expansions(t_data *data, char *line);
// bool	convert_expansions(t_data *d, int start);
// char 	*ft_getenv(t_data *data, char *var);
// char	*get_key(char *line, int start);
// bool	replace_key_in_line(t_data *d, char *value, int start, int val_len, int key_len);



// //hoppa
// int		index_to_char(char	*str, char c);

// //errorhandler

// #endif