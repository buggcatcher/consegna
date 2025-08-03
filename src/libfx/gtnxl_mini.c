#include "minishell.h"


// Funzione ausiliaria per pulire il buffer
void	clean_buffer(char **buffer)
{
	if (*buffer)
	{
		free(*buffer);
		*buffer = NULL;
	}
}

// Funzione ausiliaria per gestire EOF o errore nella lettura
char	*handle_eof(char **lbuffer, int *flag)
{
	char	*line;

	if (*flag == 1)
		return (NULL);
	if (*lbuffer && **lbuffer)
	{
		line = ft_strdup(*lbuffer);
		free(*lbuffer);
		*lbuffer = NULL;
		return (line);
	}
	return (NULL);
}

