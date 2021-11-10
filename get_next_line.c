/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calecia <calecia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 17:55:45 by calecia           #+#    #+#             */
/*   Updated: 2021/11/10 19:32:40 by calecia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_line(int fd, char *line)
{
	char	*buf;
	int		check;

	buf = malloc (BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	buf[BUFFER_SIZE] = '\0';
	check = 1;
	while (!have_end_line(line) && check)
	{
		check = read(fd, buf, BUFFER_SIZE);
		if (check == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[check] = '\0';
		line = ft_strjoin(line, buf);
	}
	free (buf);
	return (line);
}

char	*cut_tail(char *line)
{
	char	*tail;
	int		i;
	int		j;

	i = 0;
	if (!line)
		return (NULL);
	while (line[i] != '\n' && line[i])
		i++;
	if (!line[i])
	{
		free(line);
		return (NULL);
	}
	tail = malloc(ft_strlen(&line[i]) + 1);
	if (!tail)
		return (NULL);
	i++;
	j = 0;
	while (line[i])
		tail[j++] = line[i++];
	tail[j] = '\0';
	free(line);
	return (tail);
}

char	*before_tail(char *ret)
{
	int		i;
	char	*r;

	i = 0;
	if (!ret)
		return (NULL);
	while (ret[i] != '\n' && ret[i])
		i++;
	if (ret[i] == '\n')
		i++;
	r = malloc(i + 1);
	if (!r)
		return (NULL);
	i = 0;
	while (ret[i] != '\0' && ret[i] != '\n')
	{
		r[i] = ret[i];
		i++;
	}
	if (ret[i] == '\n')
		r[i++] = '\n';
	r[i] = '\0';
	return (r);
}

char	*get_next_line(int fd)
{
	char		*ret;
	static char	*rem_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	rem_line = read_line(fd, rem_line);
	if (!rem_line)
		return (NULL);
	ret = before_tail(rem_line);
	if (!ret || !*ret)
	{
		free(ret);
		if (rem_line)
		{
			free(rem_line);
			rem_line = NULL;
		}
		return (NULL);
	}
	rem_line = cut_tail(rem_line);
	return (ret);
}
