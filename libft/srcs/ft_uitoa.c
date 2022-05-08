/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpou-ale <tpou-ale@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 17:26:36 by tpou-ale          #+#    #+#             */
/*   Updated: 2022/01/31 17:26:48 by tpou-ale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_uintlen(size_t n)
{
	size_t	len;

	len = !n;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_uitoa(unsigned int n)
{
	int		len;
	char	*str;

	len = ft_uintlen(n);
	str = (char *)malloc(len + 1);
	if (!str)
		return (str);
	str[0] = '0';
	str[len--] = 0;
	while (n)
	{
		str[len--] = (char)(48 + n % 10);
		n /= 10;
	}
	return (str);
}
