/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 00:33:06 by maissat           #+#    #+#             */
/*   Updated: 2025/04/13 19:48:10 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*takeleft(char	*str)
{
	int		i;
	char	*res;

	i = 0;
	res = malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!res)
		return (NULL);
	while (str[i])
	{
		res[i] = str[i];
		if (str[i] == '\n')
			break ;
		i++;
	}
	if (str[i] == '\n')
		res[++i] = '\0';
	else
		res[i] = '\0';
	return (res);
}

char	*takeright(char	*str)
{
	int		i;
	char	*res;
	int		j;

	i = 0;
	j = 0;
	res = malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!res)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] != '\0')
		i++;
	while (str[i])
	{
		res[j] = str[i];
		i++;
		j++;
	}
	res[j] = 0;
	return (res);
}

int	ft_search(char	*str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (-1);
}

char	*ft_strjoin(char *src, char *add)
{
	char	*join;
	int		i;
	int		j;

	join = malloc(sizeof(char) * (ft_strlen(src) + ft_strlen(add) + 1));
	if (!join)
		return (NULL);
	i = 0;
	j = 0;
	while (src[i])
	{
		join[i] = src[i];
		i++;
	}
	while (add[j])
	{
		join[i] = add[j];
		i++;
		j++;
	}
	join[i] = 0;
	return (join);
}
