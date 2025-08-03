#include "minishell.h"

void	clean_buffer(char **buffer)
{
	if (*buffer)
	{
		free(*buffer);
		*buffer = NULL;
	}
}

void	handle_hdoc_cleanup(void)
{
	gtnxl(-1);
	setup_signals();
}

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

