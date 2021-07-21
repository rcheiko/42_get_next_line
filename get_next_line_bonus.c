/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcheiko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 11:37:21 by rcheiko           #+#    #+#             */
/*   Updated: 2021/02/11 10:46:40 by rcheiko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int		is_newline(char *str, char c)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (c == str[i])
			return (i);
		i++;
	}
	return (i + 1);
}

char	*creat_line(char *str, char *buffer)
{
	char	*tmp;
	int		j;
	int		k;

	j = 0;
	k = 0;
	if (!(tmp = malloc(sizeof(char) * (BUFFER_SIZE + 1 + ft_strlen(str)))))
		return (NULL);
	if (str)
	{
		while (str[j])
		{
			tmp[j] = str[j];
			j++;
		}
		free(str);
		str = NULL;
	}
	while (buffer[k])
		tmp[j++] = buffer[k++];
	tmp[j] = '\0';
	return (tmp);
}

int		get_rest(char **line, char *str)
{
	char	*rest;
	int		i;

	i = is_newline(str, '\n');
	if ((rest = ft_strchr(str, '\n')))
	{
		*line = ft_substr(str, 0, i);
		ft_strcpy(str, rest + 1);
		return (1);
	}
	return (0);
}

int		get_next_line(int fd, char **line)
{
	static char	*str[4096];
	char		buffer[BUFFER_SIZE + 1];
	int			ret;

	if (fd < 0 || fd > 255 || BUFFER_SIZE <= 0 || !line)
		return (-1);
	if (str[fd] && get_rest(line, str[fd]))
		return (1);
	while ((ret = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[ret] = '\0';
		if (!(str[fd] = creat_line(str[fd], buffer)))
			return (-1);
		if (get_rest(line, str[fd]))
			return (1);
	}
	if (str[fd])
		*line = ft_strdup(str[fd]);
	else
		*line = ft_strdup("");
	free(str[fd]);
	str[fd] = NULL;
	return (ret);
}
