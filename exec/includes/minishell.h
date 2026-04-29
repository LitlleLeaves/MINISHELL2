/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: side-lan <side-lan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 17:05:14 by jjhurry           #+#    #+#             */
/*   Updated: 2026/04/29 17:52:19 by side-lan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "minishell1.h"

/* readline tering zooi wat een functie*/
char	*get_line(t_data *data);
char	*safe_readline(void);

/* tokenization helpers */
t_token	*classify_and_make(t_data *d, char *line);
t_token	*tokenize_input(t_data *d, char *str);
t_token	*if_redirection(t_data *d, int start, char *line, t_token_type type);
t_token	*if_word(t_data *d, int start, char *line);
t_token	*make_new_token(char *value, t_token_type type);
t_token	*tokenize_loop(t_data *d, char *str, t_token *head, t_token *current);

/*quotes*/
t_token	*make_word_token_with_quotes(t_data *d, char *line, int start);
t_token	*if_quotes(t_data *d, char *line, int start);
int		check_closed_quotes(char *line);

bool	convert_expansions(t_data *d, int start);
bool	replace_key_in_line(t_data *d, char *value, int start, int key_len);

/* misc */
int		index_to_char(char *str, char c);

/* signals*/
void	setup_signals(t_sig_status	type);
int		heredoc_signal_hook(void);
int		interactive_signal_hook(void);

size_t	ft_strlen(const char *str);
char	*get_next_line(int fd);
char	*ft_strchr(const char *str, int c);
void	*ft_calloc(size_t nmemb, size_t size);
char	*free_left(char **left);
char	*free_left(char **left);

/*wait children.c*/
int		ft_wait_all_children(t_data *data, int nmb_of_pipes);

/*string helpers*/
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);

/*arguments*/
int		ft_build_arguments_array(t_exec_info *exec_info);

#endif