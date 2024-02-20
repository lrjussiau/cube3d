/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map__utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:01:21 by ljussiau          #+#    #+#             */
/*   Updated: 2024/02/20 11:24:09 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

char	*str_append(const char *str1, const char *str2)
{
	char	*result;
	size_t	len1;
	size_t	len2;

	if (str1 == NULL)
		len1 = 0;
	else
		len1 = ft_strlen(str1);
	if (str2 == NULL)
		len2 = 0;
	else
		len2 = ft_strlen(str2);
	result = safe_malloc(len1 + len2 + 1);
	*result = '\0';
	if (str1)
		ft_strlcat(result, str1, len1 + 1);
	if (str2[0] != '\0')
		ft_strlcat(result, str2, len1 + len2 + 1);
	return (result);
}

char	*clear_path(char *str)
{
	int	i;

	i = 3;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	return (&str[i]);
}

char	*clear_color(char *str)
{
	int	i;

	i = 2;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	return (&str[i]);
}
