/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ourisan <ourisan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 17:37:22 by lde-plac          #+#    #+#             */
/*   Updated: 2026/03/12 17:32:46 by ajuvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "minishell_struct.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../LIBFT/SRC/libft.h"
# include <linux/limits.h>

/* Executor */
void	executor(t_cmd *cmds, t_env *env);

/* Redir */
void	redir_open(t_redir *redir);
void	redir_exec(t_redir *redir);

/* Utils*/
char	**env_to_array(t_env *env);
char	*exec_path(char	*cmd, t_env *env);
char	*shell_prompt(char *pwd);

/* Lexer */
t_token	*token_new(char *value, t_token_type type);
void	token_add_back(t_token **lst, t_token *new);
int		lexer(t_token **token, char *str);
void	token_clear(t_token **lst);

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
int		builtin_exit(char **args);

/* Built-ins utils */
int		is_valid_identifier(const char *s);
char	*var_expansion(char *var, t_env *env);

#endif
