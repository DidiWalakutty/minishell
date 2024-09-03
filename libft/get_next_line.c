/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   get_next_line.c                                   :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/02/14 22:57:31 by sreerink      #+#    #+#                 */
/*   Updated: 2024/02/15 16:44:39 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	afternwl_to_line(char **line, char **after_nwl)
{
	*line = ft_strjoin_free(*line, *after_nwl);
	free(*after_nwl);
	*after_nwl = NULL;
}

static void	read_and_stack(char **line, int fd, ssize_t *chars_read)
{
	char	buffer[BUFFER_SIZE + 1];

	while (ft_index_chr(*line, '\n') == -1)
	{
		*chars_read = read(fd, buffer, BUFFER_SIZE);
		if ((*chars_read == -1) || (*chars_read == 0 && *line == NULL))
		{
			free(*line);
			*line = NULL;
			return ;
		}
		if (*chars_read == 0)
			return ;
		buffer[*chars_read] = '\0';
		*line = ft_strjoin_free(*line, buffer);
		if (!*line)
		{
			free(*line);
			return ;
		}
	}
}

static void	make_line_and_afternwl(char **line, char **after_nwl, ssize_t pos)
{
	char	*temp;

	*after_nwl = ft_strjoin_free(*after_nwl, *line + (pos + 1));
	if (!*after_nwl)
	{
		free(*line);
		*line = NULL;
		return ;
	}
	temp = malloc(sizeof(char) * (pos + 2));
	if (!temp)
	{
		free(*line);
		free(*after_nwl);
		*line = NULL;
		*after_nwl = NULL;
		return ;
	}
	ft_strlcpy(temp, *line, pos + 2);
	free(*line);
	*line = temp;
}

char	*get_next_line(int fd)
{
	ssize_t		chars_read;
	ssize_t		pos;
	char		*line;
	static char	*after_nwl;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	chars_read = 1;
	if (after_nwl)
	{
		afternwl_to_line(&line, &after_nwl);
		if (!line)
			return (NULL);
	}
	read_and_stack(&line, fd, &chars_read);
	if (!line)
		return (free(after_nwl), NULL);
	pos = ft_index_chr(line, '\n');
	if (chars_read == 0 || line[pos + 1] == '\0')
		return (line);
	make_line_and_afternwl(&line, &after_nwl, pos);
	return (line);
}
