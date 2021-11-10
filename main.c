/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calecia <calecia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 16:09:29 by calecia           #+#    #+#             */
/*   Updated: 2021/11/10 19:33:35 by calecia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	char	*line;
	int		fd;
	int		fd2;

	fd2 = open("testOut.txt", O_WRONLY);
	fd = open("test.txt", O_RDONLY);
	line = get_next_line(fd);
	while (line && *line)
	{
		write(fd2, line, ft_strlen(line));
		line = get_next_line(fd);
	}
	close(fd);
	close(fd2);
}
