/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:49:15 by alex              #+#    #+#             */
/*   Updated: 2024/09/12 16:02:51 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//# include "../libft/src/libft.h"
# include <stdio.h>					// Printf
# include <stdlib.h> 				// Malloc, Free, exit
# include <fcntl.h> 				// Open
# include <unistd.h> 				// read, execve, fork, pipe, getcwd
# include <sys/wait.h> 				// waitpid
# include <signal.h> 				// signal
# include <sys/types.h>
# include <dirent.h>
# include <errno.h> 				// errno
# include <sys/stat.h> 				//S_ISDIR
# include <readline/readline.h> 	// Readline
# include <readline/history.h> 		// History

# include <string.h>
# include <ctype.h>

typedef struct s_checker
{
	struct s_checker	*prev;
	char				*data;
	int					data_type;
	int					pos;
	struct s_checker	*next;
}				t_checker;

typedef struct s_cmd
{
	char				*cmd;
	char				*path;
	char				**args;
	int					in_fd;
	int					out_fd;
	struct s_cmd		*next;
}				t_cmd;

// main fts

void			ft_heredoc(char **pre_input);
int				ft_count_q(char *input, int x);
char			*ft_append_input(char *pre_input, char *hd_input);
char			*ft_clean_input(char *pre_input);
char			*ft_create_input(char *old_input);
int				ft_var_len(char *input, int idx);
int				ft_var_newlen(char *input);
int				ft_cpy_value(char **input, char *new_input, int *idx, int idy);
void			ft_dollar_exp(char **input, int *dquotes);
void			ft_new_input(char **input, int new_len);
int				ft_builtin(char *input, char **envp);
void			ft_exit_check(char *input);
int				ft_exit_num(char *input);
t_checker		*ft_setup_checker(char **input);
t_checker		*ft_create_node(char *input, int idx);
void			ft_append_end(t_checker **checks, t_checker *new_node);
int				ft_datatype(char *input);
void			ft_init_minishell(char *input, char **envp);
int				ft_check_input(t_checker *checker);
int				ft_checks_00(t_checker *checker);
int				ft_checks_01(t_checker *checker);
int				ft_checks_02(int pipes_c, int cmd_c, int redir_c, int arch_c);
void			ft_print_checker(t_checker *checker);
void			ft_free_checker(t_checker *checker);
void			ft_free_node(t_checker *node);
void			ft_init_execution(char *input, char **envp);
void			ft_execute_cmds(t_cmd *cmd_list, char **envp);
pid_t			ft_fork_and_execute(t_cmd *cmd, char **envp, int pipefd[2]);
void			ft_parent_process(t_cmd *cmd, int pipefd[2]);
char			*ft_find_command_path(char *cmd_name);
void			ft_clean_input_ex(char **input);
t_cmd			*ft_create_cmd(char *cmd_str, int in_fd);
t_cmd			*ft_parse_cmds(char *input, int *flag);
void			ft_create_pipe(int pipefd[2]);
void			ft_redirect_io(int in_fd, int out_fd);
void			ft_handle_redirection(char *cmd, int *out_fd);
void			ft_free_cmd(t_cmd *cmd);
void			ft_free_cmd_list(t_cmd *cmd_list);
void			ft_signal_handler(void);
void			sigquit_handler(int sig);
void			sigint_handler(int sig);
int				ft_echo(char *input);
int				ft_cd(char *input);
int				ft_cd2(char *input, int len);
int				ft_export(char *input, char **envp);
void			ft_add_update_env(char *name, char *value, char **envp);
int				ft_find_env(char *name, char **envp);
char			*ft_create_env(char *name, char *value);
int				ft_unset(char *input, char **envp, int len);
int				ft_pwd(char *input, char **envp);
int				ft_env(char *input, char **envp);

// utils

void			ft_elevate_doll(int *new_len, int *idx);
void			ft_init_doll(int *new_len, int *idx);
int				ft_previous_checks(char *input, int dquotes);
int				ft_is_cmd(char *input);
int				ft_are_cmds(char *input);
int				ft_strlen(char *string);
int				ft_error(int x);
int				ft_strncmp(const char *str, const char *str2, size_t c);
int				ft_atoi(const char *str);
void			ft_free_spltinput(char **input);
char			*ft_strdup(const char *s1);
char			**ft_split(char *s, char c);
char			*ft_strtok(char *str, const char *delim);
char			*ft_strcat(char *dest, const char *src);

#endif