/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andmigue <andmigue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 19:32:19 by andmigue          #+#    #+#             */
/*   Updated: 2026/06/25 19:36:10 by andmigue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	get_size(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i++] == '\n')
			break ;
	}
	return (i);
}

int	if_new_line_exists(char *s)
{
	if (!s)
		return (0);
	while (*s)
	{
		if (*s == '\n')
			return (1);
		s++;
	}
	return (0);
}

void	get_the_rest(char *buffer)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	while (buffer[i])
		buffer[j++] = buffer[i++];
	buffer[j] = '\0';
}

char	*copy_to_line(char *line, char *buffer)
{
	char	*new_line;
	char	*temp;
	char	*to_free;

	new_line = malloc(get_size(buffer) + get_size(line) + 1);
	if (!new_line)
	{
		free(line);
		return (NULL);
	}
	temp = new_line;
	to_free = line;
	while (line && *line)
		*temp++ = *line++;
	while (*buffer)
	{
		*temp++ = *buffer;
		if (*buffer++ == '\n')
			break ;
	}
	free(to_free);
	*temp = '\0';
	return (new_line);
}
