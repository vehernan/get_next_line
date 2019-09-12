/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vehernan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 11:24:44 by vehernan          #+#    #+#             */
/*   Updated: 2019/09/10 16:27:14 by vehernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		nlcheck(char *old_stuff)
{
	char		*temp;

	temp = NULL;
	if (old_stuff == NULL)
		return (1);
	temp = ft_strchr(old_stuff, NEWLINE);
	if (temp == NULL)
		return (1);
	if (temp != NULL)
		return (0);
	return (0);
}

static int		last_check(char **original1, char **line)
{
	char		*temp;
	char		*original;

	original = original1[0];
	temp = NULL;
	if (ft_strchr(original, NEWLINE))
	{
		temp = original;
		original = ft_strchr(original, NEWLINE);
		original[0] = '\0';
		if (ft_strlen(&original[1]) > 0)
			*original1 = ft_strdup(&original[1]);
		else
			*original1 = NULL;
		*line = ft_strdup(temp);
		free(temp);
	}
	return (1);
}

static int		foundread_nonl(char **original1, char **line)
{
	char	*original;

	original = *original1;
	*line = ft_strdup(original);
	free(original);
	*original1 = NULL;
	return (1);
}

int				get_next_line(int fd, char **line)
{
	static char	*original;
	char		buffer[BUFF_SIZE + 1];
	int			bytes_read;

	bytes_read = 0;
	if (!line || fd < 0 || (read(fd, buffer, 0) < 0))
		return (-1);
	while (nlcheck(original))
	{
		bytes_read = read(fd, buffer, BUFF_SIZE);
		if (bytes_read > 0)
		{
			buffer[bytes_read] = '\0';
			if (original == NULL)
				original = ft_strdup(buffer);
			else
				original = ft_strnjoin(original, buffer, 1);
		}
		else if (original != NULL && ft_strlen(original) > 0 && bytes_read == 0)
			return (foundread_nonl(&original, line));
		else
			return (0);
	}
	return (last_check(&original, line));
}
