#include "exec.h"

t_token	*create_token(char *value, t_token_type type)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	if (value)
		token->value = strdup(value);
	else
		token->value = NULL;
	token->filename = NULL;
	token->type = type;
	token->next = NULL;
	return (token);
}

//dummy function to generate differnt lists to test before parsig is done
t_token	*ft_get_head()
{
	// Token array for easier initialization
    struct {
        char *value;
        t_token_type type;
    } token_data[] = {
        {"eof", HEREDOC_EXPANSION},
		// {"infile", REDIR_IN},
        {"grep", WORD},
		{"j", WORD},
		// {"jjhurry", WORD},
		// {"outfile", REDIR_OUT_TRUNCT},
        {NULL, PIPE},
		// // // {"infile", REDIR_IN},
        {"grep", WORD},
		{"j", WORD},
        // // {NULL, PIPE},
        // {"wc", WORD},
		// // {"-l", WORD},
        {"outfile2", REDIR_OUT_APPEND},
		
    };
	// printf("dummy function called\n"); // debug
    
    int count = sizeof(token_data) / sizeof(token_data[0]);
    t_token *head = NULL;
    t_token *current = NULL;
    
    for (int i = 0; i < count; i++) {
        t_token *new = create_token(token_data[i].value, 
                                     token_data[i].type);
        if (!head) {
            head = new;
            current = head;
        } else {
            current->next = new;
            current = new;
        }
    }
	return (head);
}