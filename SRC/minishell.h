/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ourisan <ourisan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 17:37:22 by lde-plac          #+#    #+#             */
/*   Updated: 2026/03/22 05:16:36 by ourisan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "minishell_struct.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../LIBFT/SRC/libft.h"
# include <linux/limits.h>

/* Exec */
void	exec(t_cmd *cmds, t_shell *shell);

/* Exec Utils*/
int		builtin_cmd(char *cmd, char **argv, t_shell *shell);
int		is_builtin_cmd(char *cmd);

/* Redir */
void	redir_open(t_redir *r);
void	redir_open_heredoc(t_redir *r);
void	redir_exec(t_redir *r);

/* Utils*/
char	*var_expansion(char *var, t_shell *shell);
char	**env_to_array(t_env *env);
char	*exec_path(char	*cmd, t_env *env);
char	*shell_prompt(char *pwd);

/* Lexer */
t_token	*token_new(char *value, t_token_type type);
void	token_add_back(t_token **lst, t_token *new);
void	token_clear(t_token **lst);
int 	handle_word(t_token **token, char *str, t_shell *shell);
int		lexer(t_token **token, char *str, t_shell *shell);

/* Parser */
t_cmd	*cmd_new(void);
void	argv_add(char ***argv, char *value);
void	redir_add(t_redir **list, t_token_type type, char *target);
void	cmd_add_back(t_cmd **list, t_cmd *new);
int		check_cmd(t_token *tokens);
void	parser_init(t_cmd **cmds, t_token *tokens);
void	cmds_clear(t_cmd **cmds);

/* Env */
t_env	*env_find(t_env *env, char *key);
void	env_set(t_env **env, char *key, char *value, int append);
t_env	*env_init(char **envp);

/* Built-ins */
int		builtin_echo(char **args);
int		builtin_cd(char **args, t_env *env);
int		builtin_pwd(void);
int		builtin_export(char **args, t_env *env);
int		builtin_unset(char	**args, t_env **env);
int		builtin_env(t_env *env);
int		builtin_exit(char **args, t_shell *shell);

/* Built-ins utils */
void	export_env(char *arg, t_env *env, int *status);
void	env_remove(char **args, t_env **env, int i);
int		change_path(t_env *env, char *path);
int		is_valid_identifier(const char *s);

#endif
