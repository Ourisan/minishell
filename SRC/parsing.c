#include "minishell.h"

void	free_argv(char **argv)
{
	int	i;

	if (!argv)
		return ;
	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

void	free_redir(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		tmp = redir->next;
		free(redir->target);
		free(redir);
		redir = tmp;
	}
}

void	cmds_clear(t_cmd **cmds)
{
	t_cmd	*tmp;

	if (!cmds || !*cmds)
		return ;
	while (*cmds)
	{
		tmp = (*cmds)->next;
		free_argv((*cmds)->argv);
		free_redir((*cmds)->redir);
		free(*cmds);
		*cmds = tmp;
	}
}

void	parser(t_token *tokens, t_cmd *current, t_cmd **cmds)
{
	t_token	*tmp;
	
	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == TOKEN_WORD)
			argv_add(&current->argv, tmp->value);
		else if(tmp->type == TOKEN_REDIR_IN || tmp->type == TOKEN_REDIR_OUT ||
				tmp->type == TOKEN_APPEND || tmp->type == TOKEN_HEREDOC)
		{
			redir_add(&current->redir, tmp->type, tmp->next->value);
			tmp = tmp->next;
		}
		else if (tmp->type == TOKEN_PIPE)
		{
			cmd_add_back(cmds, current);
			current = cmd_new();
			if (!current)
				return ;
		}
		tmp = tmp->next;
	}
	cmd_add_back(cmds, current);
}

void	parser_init(t_cmd **cmds, t_token *tokens)
{
	t_cmd	*current;

	if (check_cmd(tokens))
		return ;
	current = cmd_new();
	if (!current)
		return ;
	parser(tokens, current, cmds);
}
