/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissat <maissat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 20:25:05 by root              #+#    #+#             */
/*   Updated: 2025/05/22 17:35:28 by maissat          ###   ########.fr       */
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
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		if (str[i] != ' ' && str[i] != '\t')
			len++;
		i++;
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

char	*ft_substr(char *str, int start, int end)
{
	char	*res;
	int		i;

	i = 0;
	res = malloc(sizeof(char) * (end - start + 1));
	if (!res)
		return (NULL);
	while (str[start] && start < end)
	{
		res[i] = str[start];
		i++;
		start++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	while (i > 0)
	{
		if (s[i] == (char)c)
			return ((char *)(&s[i]));
		i--;
	}
	if (s[i] == (char)c)
		return ((char *)(&s[i]));
	return (0);
}
