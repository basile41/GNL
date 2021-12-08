/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bregneau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 14:21:13 by bregneau          #+#    #+#             */
/*   Updated: 2021/12/08 15:26:48 by bregneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_add_to_str(char *s1, char *s2, size_t s2_size)
{
	size_t	s1_size;
	char	*str;
	size_t	i;

	s1_size = 0;
	if (s1)
		s1_size = ft_strlen(s1);
	if (s2_size && s2 && *s2)
	{
		str = malloc((s1_size + s2_size + 1) * sizeof(char));
		if (!str)
			return (NULL);
		i = 0;
		ft_strcpy(str, s1);
		ft_strcpy(str + s1_size, s2);
		str[s1_size + s2_size] = '\0';
		if (s1)
			free(s1);
		return (str);
	}
	return (s1);
}

char	*ft_read_file(int fd, char **memory)
{
	char	buffer[BUFFER_SIZE + 1];
	ssize_t	ret;
	char	*endline;

	endline = NULL;
	ret = 1;
	while (ret > 0)
	{
		if (*memory)
		{
			endline = ft_strchr(*memory, '\n');
			if (endline)
				break ;
		}
		ret = read(fd, buffer, BUFFER_SIZE);
		if (ret > 0)
		{
			buffer[ret] = 0;
			*memory = ft_add_to_str(*memory, buffer, ret);
		}
	}
	return (endline);
}

char	*ft_extract_line(char **memory, char *endline)
{
	char	*tmp;
	char	*line;

	line = ft_strndup(*memory, endline + 1 - *memory);
	if (!line)
		return (NULL);
	tmp = ft_strndup(endline + 1, BUFFER_SIZE);
	free(*memory);
	*memory = ft_strndup(tmp, BUFFER_SIZE);
	free(tmp);
	if (!(*memory))
		return (NULL);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*memory[1024];
	char		*line;
	char		*endline;

	if (fd < 0 || fd > 1024)
		return (NULL);
	endline = ft_read_file(fd, memory + fd);
	line = NULL;
	if (endline)
	{
		return (ft_extract_line(memory + fd, endline));
	}
	if (memory[fd])
	{
		if (*(memory[fd]))
			line = ft_strndup(memory[fd], ft_strlen(memory[fd]));
		free(memory[fd]);
		memory[fd] = NULL;
		return (line);
	}
	return (NULL);
}
