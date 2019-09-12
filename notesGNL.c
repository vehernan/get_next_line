
static int	nlcheck(char *old_stuff)
{
	char	*temp;

	temp = NULL;
	//nothing allocated, free to use pointer
	if (old_stuff == NULL)
		return (1);
	//looking for a newline char in the string
	temp = ft_strchr(old_stuff, NEWLINE);
	//if no new line, free to use
	if (temp == NULL)
		return (1);
	//found a new line char in string
	if (temp != NULL)
		return (0);
	return (0);
}

/*
**we are done reading the file and no new line char is found
*/

static int	foundread_nonl(char **original1, char **line)
{
	char *original;

	original = *original1;
	//my og is going to contain *og1;
	*line = ft_strdup(original);
	//dup my og contend
	free(original);
	*original1 = NULL;
	//set the og1 to null
	//to be able to return a 1.. as to something was read but
	return (1);
}

/*
**Handles the parsing of the string at the new line
*/

static char		last_check(char **original1, char **line)
{//keep track of the start
	char		*temp;
	char		*original;

	original = original1[0];
	//set og to my pointers og
	temp = NULL;
	if (ft_strchr(original, NEWLINE))
	{
		temp = original;
		original = ft_strchr(original, NEWLINE);
		//find my newline character
		original[0] = '\0';
		//sets pointer with a null(caps it)
		if (ft_strlen(&original[1]) > 0)
			//move to the next character after newline found
			*original1 = ft_strdup(&original[1]);
		//and then strdup it.to my original 
		else
			*original1 = NULL;
		*line = ft_strdup(temp);
		free(temp);
	}
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
		//while there no new line lets do this
	{
		bytes_read = read(fd, buffer, BUFF_SIZE); 
		//star reading my fd, read holds 3 params
		if (bytes_read > 0)
			//my nl func, has read my numb of bytes
		{
			buffer[bytes_read] = '\0';
			//set my null char after total of numb of bytes read
			if (original == NULL)
			original = ft_strdup(buffer);
			//dup buffer to original everytime it reads
		else
			original = ft_strnjoin(original, buffer, 1);
		//if my og isnt null, append og && buffer, freeing the s1 at sam etime
		}
		else if (original != NULL && ft_strlen(original) > 0 && bytes_read == 0)
			return (foundread_nonl(&original, line));
		//if my no new line @end found or if there just wasnt anything
		else
			return (0);
	}
	return (last_check(&original, line));
	//keep track of my start and free.
}
