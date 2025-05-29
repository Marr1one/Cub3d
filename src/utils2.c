/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/05/29 11:43:44 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../cub3d.h"

char	*skip_spaces(char *str)
{
	int		len;
	int		i;
	int		j;
	char	*res;

	len = 0;
	i = -1;
	while (str[++i] && str[i] != '\n')
	{
		if (str[i] != ' ' && str[i] != '\t')
			len++;
	}
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i] && str[i] != '\n')
	{
		if (str[i] != ' ' && str[i] != '\t')
			res[j++] = str[i];
		i++;
	}
	res[j] = '\0';
	return (res);
}

int	is_numeric(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	str_in_str(char *str, char *to_find)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i + j] == to_find[j])
			j++;
		if (j == ft_strlen(to_find))
			return (1);
		i++;
	}
	return (0);
}

int	space_before(char *line)
{
	if (line[0] == ' ')
		return (1);
	return (0);
}

int	ft_atoi(char *str)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (str[i])
	{
		n = n * 10 + (str[i] - '0');
		i++;
	}
	return (n);
}
