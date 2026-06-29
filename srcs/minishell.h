/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                   #+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 00:00:00 by alex              #+#    #+#             */
/*   Updated: 2026/06/29 00:00:00 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/src/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>

# define PROMPT "minishell$ "

extern volatile sig_atomic_t	g_signal;

typedef enum e_tok
{
	T_WORD,
	T_PIPE,
	T_IN,
	T_OUT,
	T_APPEND,
	T_HEREDOC
}	t_tok;

typedef struct s_token
{
	char			*value;
	t_tok			type;
	int				quoted;
	struct s_token	*next;
}	t_token;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef enum e_redir
{
	R_IN,
	R_OUT,
	R_APPEND,
	R_HEREDOC
}	t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;
	char			*target;
	int				expand;
	int				fd;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**argv;
	t_redir			*redirs;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_shell
{
	t_env	*env;
	t_cmd	*cmds;
	char	*line;
	int		exit_status;
}	t_shell;

/* main / loop */
void		shell_loop(t_shell *sh);
void		process_line(t_shell *sh, char *line);
int			has_content(char *line);
void		cleanup_after(t_shell *sh);

/* env */
t_env		*env_init(char **envp);
t_env		*env_new(char *key, char *value);
void		env_add_back(t_env **lst, t_env *node);
t_env		*env_find(t_env *env, char *key);
char		*env_get(t_env *env, char *key);
void		env_set(t_env **env, char *key, char *value);
void		env_declare(t_env **env, char *key);
void		env_unset(t_env **env, char *key);
char		**env_to_array(t_env *env);
void		env_clear(t_env **env);

/* signals */
void		setup_signals_interactive(void);
void		setup_signals_exec(void);
void		setup_signals_default(void);
void		sigint_handler(int sig);

/* lexer */
t_token		*lex(char *line);
int			add_word(char *line, int *i, t_token **toks);
int			add_operator(char *line, int *i, t_token **toks);
t_token		*token_new(char *value, t_tok type);
void		token_add_back(t_token **lst, t_token *node);
void		token_clear(t_token **lst);

/* expand */
void		expand_tokens(t_shell *sh, t_token *toks);
char		*expand_str(t_shell *sh, char *raw);
char		*expand_vars(t_shell *sh, char *line);
char		*app_char(char *s, char c);
char		*str_append_n(char *s, char *add, int n);
char		*gc_strjoin(char *s, char *add);
char		*app_single(char *res, char *raw, int *i);
char		*app_double(t_shell *sh, char *res, char *raw, int *i);
char		*app_dollar(t_shell *sh, char *res, char *raw, int *i);
char		*strip_quotes(char *raw);
void		replace_val(char **dst, char *new);

/* parser */
t_cmd		*parse(t_token *toks);
int			syntax_check(t_token *toks);
t_cmd		*cmd_new(void);
char		**argv_add(char **argv, char *str);
t_token		*add_arg(t_cmd *cmd, t_token *tok);
void		cmd_clear(t_cmd *cmd);
void		cmd_list_clear(t_cmd *cmds);
t_token		*add_redir(t_cmd *cmd, t_token *tok);
void		redir_clear(t_redir *r);

/* exec */
void		execute(t_shell *sh, t_cmd *cmds);
void		exec_single(t_shell *sh, t_cmd *cmd);
void		exec_pipeline(t_shell *sh, t_cmd *cmds);
void		child_process(t_shell *sh, t_cmd *cmd, int prev_fd, int *pipefd);
void		run_external(t_shell *sh, t_cmd *cmd);
int			resolve_path(t_shell *sh, char *cmd, char **out);
int			apply_redirs(t_cmd *cmd);
int			heredocs_setup(t_shell *sh, t_cmd *cmds);

/* builtins */
int			is_builtin(char *cmd);
int			run_builtin(t_shell *sh, char **argv);
int			bi_echo(char **argv);
int			bi_cd(t_shell *sh, char **argv);
int			bi_pwd(void);
int			bi_env(t_shell *sh);
int			bi_export(t_shell *sh, char **argv);
int			export_print(t_env *env);
int			bi_unset(t_shell *sh, char **argv);
int			bi_exit(t_shell *sh, char **argv);

/* utils */
void		cmd_error(char *cmd, char *msg);
void		cmd_error2(char *cmd, char *arg, char *msg);
int			synerr(char *tok);
void		free_shell(t_shell *sh);
void		shell_exit(t_shell *sh, int code);

#endif
