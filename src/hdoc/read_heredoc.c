/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mailinci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:08:43 by mailinci          #+#    #+#             */
/*   Updated: 2025/07/24 17:08:45 by mailinci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_hdoc_cleanup(void)
{
	gtnxl(-1);
	setup_signals();
}

static void	handle_hdoc_eof(char *delimiter)
{
	ft_putstr_stderr("\nminishell: warning: here-document delimited by end-of-file (wanted `");
	ft_putstr_stderr(delimiter);
	ft_putstr_stderr("')\n");
	handle_hdoc_cleanup();
}

static int	check_signals_and_cleanup(char *line)
{
	if (g_sigint)
	{
		if (line)
			free(line);
		handle_hdoc_cleanup();
		return (130);
	}
	return (0);
}

static int	handle_read_line(char *line, char *delimiter, size_t delimiter_len,
								t_heredoc_buffer *buffer, t_shell_state *state)
{
	int	process_result;

	if (!line)
	{
		handle_hdoc_eof(delimiter);
		return (1);
	}
	process_result = process_hdoc_line(line, delimiter, delimiter_len);
	if (process_result == 1)
	{
		free(line);
		handle_hdoc_cleanup();
		return (1);
	}
	if (expand_and_append(line, buffer, state) != 0)
	{
		free(line);
		handle_hdoc_cleanup();
		return (-1);
	}
	return (free(line), 0);
}

int read_hdoc_input(char *delimiter, t_heredoc_buffer *buffer, 
                      t_shell_state *state)
{
    char *line;
    size_t delimiter_len;
    int signal_result;
    int line_result;

    delimiter_len = ft_strlen(delimiter);
    setup_hdoc_signals();
    while (1)
    {
        signal_result = check_signals_and_cleanup(NULL);
        if (signal_result != 0)
            return (signal_result);
        write(1, "> ", 2);
        line = gtnxl(STDIN_FILENO);
        signal_result = check_signals_and_cleanup(line);
        if (signal_result != 0)
            return (signal_result);
        line_result = handle_read_line(line, delimiter, delimiter_len, buffer, state);
        if (line_result == 1)
            break;
        if (line_result == -1)
            return (1);
    }
    handle_hdoc_cleanup();
    return (0);
}
