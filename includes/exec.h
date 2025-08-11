#ifndef EXEC_H
# define EXEC_H

# include "../libft/libft.h"
# include "minishell.h"
// # include <dirent.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define FD_STDIN 0
# define FD_STDOUT 1
# define READ 0
# define WRITE 1

typedef struct s_cmd	t_cmd;

// built-in utils

long					ft_atol(char *str);
int						is_digit(char *str);

// built-in

int						child_process_built_in(t_cmd *cmd, char **envp);
int						parent_process_built_in(t_cmd *cmd, char **envp);
bool					is_built_in(t_cmd *cmd);
int						built_in_echo(t_cmd *cmd);
int						built_in_cd(t_cmd *cmd);
int						built_in_pwd(t_cmd *cmd);
int						built_in_export(t_cmd *cmd);
int						built_in_unset(t_cmd *cmd);
int						built_in_env(t_cmd *cmd, char **envp);
int						built_in_exit(t_cmd *cmd, int status);

// errors

void					free_array(char **split);
void					error(t_cmd *cmd, char *str, int code);
void					free_all_struct(t_cmd *cmd);
void					close_all_fd(int *fd);

// exec

void					unused_heredoc_fd(t_cmd *current, t_cmd *cmd_list);
int						wait_child(pid_t *pid, int size);
int						pipe_function(t_cmd *cmd, pid_t *pid, int exit_status,
							char **envp);

// get_path

char					**get_path(char **envp);
bool					exe_my_cmd(t_cmd *cmd, char **envp);

// manage_files

void					open_infile(t_cmd *cmd);
void					open_outfile(t_cmd *cmd);
void					manage_heredocs(t_cmd *cmd);

// utils

int						count_cmd(t_cmd *cmd);
int						count_args(t_cmd *cmd);
int						count_all_cmd_args(t_cmd *cmd);
void					print_array(char **array);

#endif