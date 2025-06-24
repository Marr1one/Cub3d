/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braugust <braugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:03:34 by maissat           #+#    #+#             */
/*   Updated: 2025/06/24 16:29:01 by braugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*update_stash(char *stash, char *buffer)
{
	char	*new_stash;

	new_stash = ft_strjoin(stash, buffer);
	free(stash);
	return (new_stash);
}

char	*read_to_stash(int fd, char *stash)
{
	char	*buffer;
	int		byte_read;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	while (1)
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read == -1)
		{
			free(buffer);
			free(stash);
			return (NULL);
		}
		if (byte_read == 0)
			break ;
		buffer[byte_read] = '\0';
		stash = update_stash(stash, buffer);
		if (ft_search(stash, '\n') != 0)
			break ;
	}
	free(buffer);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stash)
	{
		stash = malloc(1);
		if (!stash)
			return (NULL);
		stash[0] = '\0';
	}
	stash = read_to_stash(fd, stash);
	if (!stash || stash[0] == '\0')
	{
		if (stash)
			free(stash);
		stash = NULL;
		return (NULL);
	}
	line = takeleft(stash);
	temp = stash;
	stash = takeright(stash);
	return (free(temp), line);
}

/*int main(void)
{
	int	count;
	int	fd;

	count = 0;
	fd = open("slt.txt", O_RDONLY);
	while (count < 4)
	{

		printf("------- >GNL : %s",get_next_line(fd));
		count ++;
	}
	close(fd);
	return (0);
}*/
