/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtnxl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mailinci <mailinci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:35:38 by mailinci          #+#    #+#             */
/*   Updated: 2025/08/02 00:00:00 by mailinci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*fd_reader(int fd, int *flag)
{
	int		char_read;
	char	*buffer;

	buffer = safe_alloc(BUFFER_SIZE + 1, sizeof(char), "fd_reader buffer");
	if (!buffer)
		return (NULL);
	char_read = read(fd, buffer, BUFFER_SIZE);
	if (char_read == 0)
	{
		free(buffer);
		return (NULL);
	}
	else if (char_read == -1)
	{
		free(buffer);
		*flag = 1;
		return (NULL);
	}
	buffer[char_read] = '\0';
	return (buffer);
}

static char	*update_buffer_after_extraction(char **lbuffer, int newline_pos)
{
	char	*char_left;

	if ((*lbuffer)[newline_pos + 1] != '\0')
		char_left = ft_strdup((*lbuffer) + newline_pos + 1);
	else
		char_left = ft_strdup("");
	if (!char_left)
		return (NULL);
	free(*lbuffer);
	*lbuffer = char_left;
	return (char_left);
}

static char	*extract_from_buffer(char **lbuffer)
{
	char	*line;
	int		x;

	x = 0;
	if (!lbuffer || !*lbuffer)
		return (NULL);
	while ((*lbuffer)[x] != '\n' && (*lbuffer)[x] != '\0')
		x++;
	if ((*lbuffer)[x] == '\n')
	{
		line = ft_strndup(*lbuffer, x + 1);
		if (!line)
			return (NULL);
		if (!update_buffer_after_extraction(lbuffer, x))
		{
			free(line);
			return (NULL);
		}
		return (line);
	}
	return (NULL);
}

static char	*read_and_assemble(char **lbuffer, int fd, int *flag)
{
	char	*read_line;
	char	*tmp;
	char	*line;

	while (1)
	{
		line = extract_from_buffer(lbuffer);
		if (line)
			return (line);
		read_line = fd_reader(fd, flag);
		if (!read_line)
			return (handle_eof(lbuffer, flag));
		tmp = ft_strjoin(*lbuffer, read_line);
		free(*lbuffer);
		free(read_line);
		if (!tmp)
		{
			*flag = 1;
			return (NULL);
		}
		*lbuffer = tmp;
	}
}

char	*gtnxl(int fd)
{
	static char	*buffer;
	int			flag;
	char		*result;

	flag = 0;
	if (fd == -1)
		return (clean_buffer(&buffer), NULL);
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer)
		buffer = ft_strdup("");
	if (!buffer)
		return (NULL);
	result = read_and_assemble(&buffer, fd, &flag);
	if (flag || (!result && buffer))
		return (clean_buffer(&buffer), NULL);
	return (result);
}
