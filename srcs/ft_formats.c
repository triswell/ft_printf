/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_formats.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpou-ale <tpou-ale@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 03:42:21 by tpou-ale          #+#    #+#             */
/*   Updated: 2022/02/12 04:07:22 by tpou-ale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_punsigned(t_data *data)
{
	char			*str;
	char			*s;
	unsigned int	u;

	u = va_arg(data->args, unsigned int);
	if (!u)
		data->zero = 1;
	str = ft_uitoa(u);
	if (!str)
		return ;
	if (data->zero && data->period && !data->prec)
	{
		free(str);
		return ;
	}
	s = ft_strjoin(data->str, str);
	free(str);
	if (!s)
		return ;
	free(data->str);
	data->str = s;
}

void	ft_pnumber(t_data *data)
{
	char	*str;
	char	*s;
	int		i;

	i = va_arg(data->args, int);
	str = ft_itoa(i);
	if (!str)
		return ;
	if (i >= 0)
		data->pos = 1;
	if (!i)
		data->zero = 1;
	if (data->zero && data->period && !data->prec)
	{
		free(str);
		return ;
	}
	s = ft_strjoin(data->str, str);
	free(str);
	if (!s)
		return ;
	free(data->str);
	data->str = s;
}

void	ft_pstring(t_data *data)
{
	char	*str;
	char	*s;

	str = va_arg(data->args, char *);
	if (str != NULL)
		s = ft_strjoin(data->str, str);
	else
		s = ft_strjoin(data->str, "(null)");
	if (!s)
		return ;
	free(data->str);
	data->str = s;
}

void	ft_pchar(t_data *data, char c, int mode)
{
	char	*str;
	char	*s;

	if (!mode)
	{
		ft_putchar_fd(c, 1);
		++(data->len);
		return ;
	}
	if (!c && ++(data->len))
	{
		data->null = 1;
		return ;
	}
	str = (char *)ft_calloc(2, 1);
	if (!str)
		return ;
	str[0] = c;
	s = ft_strjoin(data->str, str);
	free(str);
	if (!s)
		return ;
	free(data->str);
	data->str = s;
}
