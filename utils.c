/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 19:11:23 by root              #+#    #+#             */
/*   Updated: 2025/04/15 15:50:57 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char *ft_strduptext(char *str)
{
	int	i;
	char *dup;

	dup = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char *ft_strdup(char *str)
{
	int	i;
	char *dup;

	dup = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (str[i])
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

void	*ft_memset(void *b, int c, size_t len)
{
	char	*start;

	if (b == NULL)
		return (NULL);
	start = b;
	while (len)
	{
		*start = c;
		start++;
		len--;
	}
	return (b);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}
int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	return (0);
}

int	check_len(char *s1, char *s2)
{
	if (ft_strlen(s1) != ft_strlen(s2))
		return (1);
	return (0);
}

int	ft_strncmp(char *s1, char *s2, int n )
{
	int	i;

	i = 0;
	if (!s1 || !s2 || n <= 0)
		return (-1);
	if (!(*s1) || !(*s2))
		return (1);
	while (i < n && s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	return (0);
}

int	ft_strlcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	if (!(*s1) || !(*s2))
		return (1);
	if (check_len(s1, s2) != 0)
		return (1);
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	return (0);
}

void	show_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("%s", tab[i]);
		i++;
	}
}

int	get_height(char *map_name)
{
	int	fd;
	char *line;
	int	count;
	int	map_started;

	map_started = 0;
	fd = open(map_name, O_RDONLY);
	if (fd < 0)
		return (printf("Impossible to open the map!\n"), -1);
	count = 0;
	line = get_next_line(fd);
	while (line)
    {
        // Si on a trouvé une ligne commençant par '1', on a commencé la carte
        if (line[0] == '1')
            map_started = 1;
        
        // On ne compte que les lignes après avoir commencé la carte
        if (map_started)
            count++;
        
        free(line);  // Toujours libérer la ligne
        line = get_next_line(fd);
    }
	close(fd);
	return (count);
}