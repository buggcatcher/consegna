/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_preprocessor.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mailinci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:08:32 by mailinci          #+#    #+#             */
/*   Updated: 2025/07/24 17:08:36 by mailinci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	preprocess_hdocs(t_node *node, t_shell_state *state)
{
	t_node	*current;
	t_redir	*redir;

	current = node;
	while (current)
	{
		redir = current->redirs;
		while (redir)
		{
			if (redir->type == TK_HEREDOC_5 && redir->fd == -1)
			{
				if (handle_hdoc_sequence(redir, state) != 0)
					return (1);
			}
			redir = redir->next;
		}
		current = current->next;
	}
	return (0);
}

int	fill_hdoc_buffer(t_redir *start, t_heredoc_buffer *buffer, \
						t_shell_state *state)
{
	t_redir	*current;

	current = start;
	while (current && current->type == TK_HEREDOC_5)
	{
		buffer->size = 0;
		if (buffer->capacity > 0 && buffer->content)
		{
			buffer->content[0] = '\0';
		}
		if (read_hdoc_input(current->filename, buffer, state) != 0)
			return (1);
		current = current->next;
	}
	return (0);
}

void	mark_as_skipped(t_redir *start)
{
	t_redir	*current;

	current = start;
	while (current && current->type == TK_HEREDOC_5)
	{
		current->fd = -2;
		current = current->next;
	}
}
