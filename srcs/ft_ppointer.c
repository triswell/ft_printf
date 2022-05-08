/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ppointer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpou-ale <tpou-ale@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 02:37:28 by tpou-ale          #+#    #+#             */
/*   Updated: 2022/01/31 02:42:46 by tpou-ale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int	ft_ptrlen(uintptr_t num)
{
	int	len;

	len = 0;
	while (num != 0)
	{
		num /= 16;
		++len;
	}
	return (len);
}

static void	ft_putptr(uintptr_t num, char *str)
{
	char	*s;

	if (num > 15)
	{
		ft_putptr(num / 16, str);
		ft_putptr(num % 16, str);
	}
	else
	{
		s = (char *)malloc(2);
		if (num < 10)
			s[0] = (char)(num + '0');
		else
			s[0] = (char)(num - 10 + 'a');
		ft_strlcat(str, s, ft_strlen(str) + 2);
		free(s);
	}
}

void	ft_ppointer(t_data *data)
{
	char				*str;
	char				*s;
	unsigned long long	p;

	p = (unsigned long long)va_arg(data->args, void *);
	s = ft_strjoin(data->str, "0x");
	if (!s)
		return ;
	free(data->str);
	data->str = s;
	str = NULL;
	if (p)
		str = (char *)ft_calloc(ft_ptrlen(p) + 1, 1);
	else if (!(data->period) || data->prec)
		str = (char *)ft_calloc(2, 1);
	if (!str)
		return ;
	ft_putptr(p, str);
	s = ft_strjoin(data->str, str);
	free(str);
	if (!s)
		return ;
	free(data->str);
	data->str = s;
}
