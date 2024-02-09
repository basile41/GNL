/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bregneau <bregneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 20:32:23 by bregneau          #+#    #+#             */
/*   Updated: 2024/02/09 14:02:05 by bregneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_add_to_str(char *s1, char *s2, size_t s2_size)
{
	size_t	s1_size;
	char	*str;

	s1_size = 0;
	if (s1)
		s1_size = ft_strlen(s1);
	if (s2_size && s2 && *s2)
	{
		str = malloc((s1_size + s2_size + 1) * sizeof(char));
		if (!str)
			return (NULL);
		ft_strncpy(str, s1, s1_size);
		ft_strncpy(str + s1_size, s2, s2_size);
		str[s1_size + s2_size] = '\0';
		if (s1)
			free(s1);
		return (str);
	}
	return (s1);
}

int	ft_is_endline(char buf[], char **line)
{
	char	*ptr;

	ptr = ft_strchr(buf, '\n');
	if (ptr)
	{
		*line = ft_add_to_str(*line, buf, ptr - buf + 1);
		ft_strncpy(buf, ptr + 1, BUFFER_SIZE);
		return (1);
	}
	*line = ft_add_to_str(*line, buf, ft_strlen(buf));
	buf[0] = '\0';
	return (0);
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*line;
	int			ret;

	line = NULL;
	while (ft_is_endline(buf, &line) == 0)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret < 0)
		{
			buf[0] = '\0';
			free(line);
			return (NULL);
		}
		if (ret == 0)
			return (line);
		buf[ret] = '\0';
	}
	return (line);
}
