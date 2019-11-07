
#include "get_next_line.h"

int     check_original(char *old_stuff)
{
    char *temp;

    temp = NULL;
    //nothing allocated, free to use pointer
    if (old_stuff == NULL)
        return (1);
    //looking for a newline char in string
    temp = ft_strchr(old_stuff, NEWLINE);
    //if no new line, free to use
    if (temp == NULL)
        return (1);
    //found a new line char in string
    if (temp != NULL)
        return (0);
    return (0);
}

int					get_next_line(int fd, char **line)
{
	static char		*original; 
    
    char            buffer[BUFF_SIZE + 1];
    int             bytes_read;
    char            *temp;

    bytes_read = 0;
	if (!line || fd < 0 || (read(fd, buffer, 0) < 0))
			return (-1);

	while (check_original(original))
	{
        //reading from FD 
        bytes_read = read(fd, buffer, BUFF_SIZE);
        if (bytes_read > 0)
        {
            //setting null char after total number of bytes read
            buffer[bytes_read] = '\0';
            if (original == NULL)
                original = ft_strdup(buffer);
            //string magic
            else
                //https://github.com/peachesforfree/libft/blob/master/ft_strnjoin.c     for the shit below
                original = ft_strnjoin(original, buffer, bytes_read);
        }
        else
            return (0) ;
	}
    if (ft_strchr(original, NEWLINE))
    {
        //keeping track of the start
        temp = original;
        original = ft_strchr(original, NEWLINE);
        original[0] = '\0';
        original = &original[1];
        original = ft_strdup(original);
        *line = ft_strdup(temp);
        free(temp);
    }
	return (1);
}


