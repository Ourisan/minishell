/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-plac <lde-plac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 17:37:22 by lde-plac          #+#    #+#             */
/*   Updated: 2026/03/05 19:09:51 by lde-plac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../LIBFT/SRC/libft.h"
# include <linux/limits.h>

/* Utils*/
char	*shell_prompt(char *pwd);

/* Lexer */
typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_IN,
	TOKEN_HEREDOC,
	TOKEN_APPEND
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

/* Parser */
typedef struct s_redir
{
	t_token_type		type;
	char				*target;
	struct s_redir		*next;
}	t_redir;

typedef struct s_cmd
{
	char			**argv;
	t_redir			*redir;
	struct s_cmd	*next;
}	t_cmd;

t_token	*token_new(char *value, t_token_type type);
void	token_add_back(t_token **lst, t_token *new);
int		lexer(t_token **token, char *str);
void	token_clear(t_token **lst);
t_cmd	*cmd_new(void);
void	argv_add(char ***argv, char *value);
void	redir_add(t_redir **list, t_token_type type, char *target);
void	cmd_add_back(t_cmd **list, t_cmd *new);
int		check_cmd(t_token *tokens);
void	parser_init(t_cmd **cmds, t_token *tokens);
void	cmds_clear(t_cmd **cmds);

/* Env */
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

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
