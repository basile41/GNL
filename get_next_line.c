/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bregneau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 20:32:23 by bregneau          #+#    #+#             */
/*   Updated: 2021/12/06 12:08:09 by bregneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_add_to_str(char *s1, char *s2, size_t s2_size)
{
	size_t	s1_size;
	char	*str;
	size_t	i;

	s1_size = 0;
	if (s1)
		s1_size = ft_strlen(s1);
	if (s2)
	{
		str = malloc((s1_size + s2_size + 1) * sizeof(char));
		if (!str)
			return (NULL);
		i = 0;
		ft_strcpy(str, s1);
		ft_strcpy(str + s1_size, s2);
		str[s1_size + s2_size] = '\0';
		free(s1);
		return (str);
	}
	return (s1);
}

char	*ft_read_file(int fd, char **memory)
{
	char	*buffer;
	ssize_t	ret;
	char	*endline;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	ret = BUFFER_SIZE;
	while (ret == BUFFER_SIZE)
	{
		if (*memory)
		{
			endline = ft_strchr(*memory, '\n');
			if (endline)
				break ;
		}
		ret = read(fd, buffer, BUFFER_SIZE);
		*memory = ft_add_to_str(*memory, buffer, ret);
	}
	free(buffer);
	if (ret < BUFFER_SIZE && *memory == NULL)
		return (NULL);
	return (endline);
	/*
	line = ft_strndup(*memory, endline + 1 - *memory);
	buffer = *memory;
	*memory = ft_strndup(endline + 1, BUFFER_SIZE);
	free(buffer);
	return (line);
	*/
}

char	*get_next_line(int fd)
{
	static char	*memory;
	char		*line;
	char		*endline;
	char		*tmp;

	endline = ft_read_file(fd, &memory);
	
	line = ft_strndup(memory, endline + 1 - memory);
	tmp = memory;
	memory = ft_strndup(endline + 1, BUFFER_SIZE);
	free(tmp);
	if (!(*line))
	{
		free(memory);
		return (NULL);
	}

	return (line);
}
