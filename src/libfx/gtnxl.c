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

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1024
#endif

// Legge dal file descriptor e restituisce il contenuto letto
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

// Estrae una linea completa dal buffer fino al primo \n
char	*extract_from_buffer(char **lbuffer)
{
	char	*line;
	char	*char_left;
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
		if ((*lbuffer)[x + 1] != '\0')
			char_left = ft_strdup((*lbuffer) + x + 1);
		else
			char_left = ft_strdup("");
		if (!char_left)
		{
			free(line);
			return (NULL);
		}
		free(*lbuffer);
		*lbuffer = char_left;
		return (line);
	}
	return (NULL);
}

// Legge e assembla il contenuto fino a trovare una linea completa
char	*read_and_assemble(char **lbuffer, int fd, int *flag)
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
		{
			if (*flag == 1)
				return (NULL);
			// EOF raggiunto - restituisci ciò che rimane nel buffer
			if (*lbuffer && **lbuffer)
			{
				line = ft_strdup(*lbuffer);
				free(*lbuffer);
				*lbuffer = NULL;
				return (line);
			}
			return (NULL);
		}
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

// Funzione principale di get_next_line
char	*gtnxl(int fd)
{
	static char	*buffer;
	int			flag;
	char		*result;

	flag = 0;
	if (fd == -1)
	{
		if (buffer)
		{
			free(buffer);
			buffer = NULL;
		}
		return (NULL);
	}
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer)
		buffer = ft_strdup("");
	if (!buffer)
		return (NULL);
	result = read_and_assemble(&buffer, fd, &flag);
	if (flag)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	// Se EOF e nessun risultato, pulisci il buffer
	if (!result && buffer)
	{
		free(buffer);
		buffer = NULL;
	}
	return (result);
}
