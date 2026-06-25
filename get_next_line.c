/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andmigue <andmigue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 18:47:49 by andmigue          #+#    #+#             */
/*   Updated: 2026/06/25 19:12:53 by andmigue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	ssize_t		readbytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	readbytes = 1;
	while (!if_new_line_exists(line))
	{
		if (*buffer == '\0')
		{
			readbytes = read(fd, buffer, BUFFER_SIZE);
			if (readbytes == -1)
				return (free(line), NULL);
			if (readbytes >= 0)
				buffer[readbytes] = '\0';
			if (readbytes == 0)
				return (line);
		}
		line = copy_to_line(line, buffer);
		get_the_rest(buffer);
	}
	return (line);
}

// int main(void)
// {
//     int     fd;
//     char    *line;

//     fd = open("teste1.txt", O_RDONLY);
//     if (fd == -1)
//         return (1);
//     while ((line = get_next_line(fd)) != NULL)
//     {
//         printf("%s", line);
//         free(line);
//     }
//     close(fd);
//     return (0);
// }