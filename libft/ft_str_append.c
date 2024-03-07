/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_append.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 08:52:19 by ljussiau          #+#    #+#             */
/*   Updated: 2024/03/07 08:54:11 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*str_append(char *str1, char *str2)
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
	result = malloc(len1 + len2 + 1);
	*result = '\0';
	if (str1)
		ft_strlcat(result, str1, len1 + 1);
	if (str2[0] != '\0')
		ft_strlcat(result, str2, len1 + len2 + 1);
	free(str1);
	return (result);
}
