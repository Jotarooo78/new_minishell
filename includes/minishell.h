/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:19:43 by messengu          #+#    #+#             */
/*   Updated: 2025/07/29 15:52:46 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../includes/exec.h"
# include "../includes/parsing.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>

// ---- STRUCTS ----

typedef enum input_type
{
	STDIN,
	PIPEIN,
	HERE_DOC,
}						t_input_type;

typedef enum output_type
{
	STDOUT,
	PIPEOUT,
}						t_output_type;

typedef struct s_heredoc
{
	char				*delimiter;
	char				*content;
	int					expand_vars;
	struct s_heredoc	*next;
}						t_heredoc;

typedef struct s_file
{
	char				*name;
	char				permission[3];
	int					append;
	int					fd; //variable temporaraire, ne pas stocker les fd car les files peuvent etre supprimes entre le parsing et l'exec
	struct s_file		*next;
}						t_file;

typedef struct s_cmd
{
	char				*name;
	char				**args;
	t_file				*infile; // ici, tableau de str.
	t_file				*outfile; //same
	t_input_type		input_type;
	t_output_type		output_type;
	t_heredoc			*heredocs;
	struct s_cmd		*next;
}						t_cmd;

typedef struct s_stack
{
	void				*value;
	struct s_stack		*next;
}						t_stack;

// ---- FUNCTIONS ----

// -- stacks
t_cmd					*parse(char *line);
void    				executable(t_cmd *cmd, char **envp);
t_stack					*init_stack(void);
void					push(t_stack **stack, void *value);
void					*pop(t_stack **stack);
void					*top(t_stack *stack);
void					clean(t_stack **stack);
int						is_empty(t_stack *stack);
void					print_cmd(t_cmd *cmd);
int						check_cmds(t_cmd *cmd);
t_cmd					*tokens_to_cmds(t_token *tokens);
void					expand_cmds(t_cmd *tokens);
void					remove_quotes(t_cmd *cmds);

#endif
