/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_processor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mailinci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 00:00:00 by mailinci          #+#    #+#             */
/*   Updated: 2025/08/03 00:00:00 by mailinci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_hdoc_line(char *line, t_shell_state *state)
{
	char	*input_ptr;
	char	*result;

	if (!line || !state)
		return (NULL);
	if (*line == '\0')
		return (ft_strdup(""));
		
	input_ptr = line;
	result = NULL;
	while (*input_ptr)	
	{
		result = ft_create_var(result, &input_ptr, state);
		if (!result)
			return (NULL);
	}
	return (result);
}

int	is_hdoc_delimiter(char *line, char *delimiter, size_t delimiter_len)
{
	return (ft_strlen(line) == delimiter_len && \
			ft_strncmp(line, delimiter, delimiter_len) == 0);
}

int	expand_and_append(char *line, t_heredoc_buffer *buffer, \
					t_shell_state *state)
{
	char	*expanded_line;

	expanded_line = expand_hdoc_line(line, state);
	if (!expanded_line)
		return (1);
	if (append_to_buffer(buffer, expanded_line) != 0)
	{
		free(expanded_line);
		return (1);
	}
	free(expanded_line);
	return (0);
}

int	process_hdoc_line(char *line, char *delimiter, size_t delimiter_len)
{
	size_t	line_len;

	line_len = ft_strlen(line);
	if (line_len > 0 && line[line_len - 1] == '\n')
		line[line_len - 1] = '\0';
	
	if (is_hdoc_delimiter(line, delimiter, delimiter_len))
		return (1);
	
	return (0);
}
