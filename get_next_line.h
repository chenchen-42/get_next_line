/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andmigue <andmigue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 18:47:40 by andmigue          #+#    #+#             */
/*   Updated: 2026/06/25 19:08:35 by andmigue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# include <stdint.h>
# include <fcntl.h>

char	*get_next_line(int fd);
size_t	get_size(const char *s);
int		if_new_line_exists(char *s);
void	get_the_rest(char *buffer);
char	*copy_to_line(char *line, char *buffer);

#endif