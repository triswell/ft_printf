/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_phex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpou-ale <tpou-ale@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 02:45:28 by tpou-ale          #+#    #+#             */
/*   Updated: 2022/01/31 02:49:46 by tpou-ale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int	ft_hexlen(unsigned int num)
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

static void	ft_puthex(unsigned int num, char *str, t_data *data)
{
	char	*s;

	if (num > 15)
	{
		ft_puthex(num / 16, str, data);
		ft_puthex(num % 16, str, data);
	}
	else
	{
		s = (char *)malloc(2);
		if (num < 10)
			s[0] = (char)(num + '0');
		else
		{
			if (data->spec == 'X')
				s[0] = (char)(num - 10 + 'A');
			else if (data->spec == 'x')
				s[0] = (char)(num - 10 + 'a');
		}
		ft_strlcat(str, s, ft_strlen(str) + 2);
		free(s);
	}
}

void	ft_phex(t_data *data)
{
	char			*str;
	char			*s;
	unsigned int	hex;

	hex = va_arg(data->args, unsigned int);
	str = NULL;
	if (!hex)
		data->zero = 1;
	if (hex)
		str = (char *)ft_calloc(ft_hexlen(hex) + 1, 1);
	else if (!(data->period) || data->prec)
		str = (char *)ft_calloc(2, 1);
	if (!str)
		return ;
	ft_puthex(hex, str, data);
	s = ft_strjoin(data->str, str);
	free(str);
	if (!s)
		return ;
	if (data->str)
		free(data->str);
	data->str = s;
}
