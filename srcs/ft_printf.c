/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpou-ale <tpou-ale@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 19:37:28 by tpou-ale          #+#    #+#             */
/*   Updated: 2022/01/30 20:42:46 by tpou-ale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void	ft_clean_flags(t_data *d)
{
	d->f_zero &= !(d->f_minus) * (ft_strchr("diuXx%", d->spec) != 0);
	d->period &= (ft_strchr("sdiuxX", d->spec) != 0);
	d->prec *= (size_t)d->period;
	d->f_plus &= (ft_strchr("di", d->spec) != 0);
	d->f_blank &= !(d->f_plus) * (ft_strchr("di", d->spec) != 0);
	d->f_sharp &= (ft_strchr("xX", d->spec) != 0);
}

ssize_t	ft_pfmod(char *format, t_data *d)
{
	ssize_t	i;
	char	c;

	i = ft_fanalyze(format, d);
	ft_clean_flags(d);
	ft_pformat(d, 1);
	ft_set_precision(d);
	if (!d->f_zero)
		ft_change_sign(d, 2);
	if (d->width && d->width > ft_strlen(d->str))
	{
		c = (char)((!d->period && d->f_zero) * '0'
				+ (!d->f_zero || d->period) * ' ');
		if (!d->zero && c == ' ')
			ft_set_sharp(d);
		ft_set_width(d, c);
	}
	ft_change_sign(d, 0);
	ft_set_sharp(d);
	ft_putstr_fd(d->str, 1);
	if (d->spec == 'c' && d->null && !d->f_minus)
		ft_putchar_fd(0, 1);
	free(d->str);
	return (i);
}

void	ft_pformat(t_data *data, char mod)
{
	if (!mod)
		ft_init_flags(data);
	if (data->spec == 'c')
		ft_pchar(data, va_arg(data->args, int), 1);
	else if (data->spec == 's')
		ft_pstring(data);
	else if (data->spec == 'p')
		ft_ppointer(data);
	else if (data->spec == 'd' || data->spec == 'i')
		ft_pnumber(data);
	else if (data->spec == 'u')
		ft_punsigned(data);
	else if (data->spec == 'x' || data->spec == 'X')
		ft_phex(data);
	else if (data->spec == '%')
		ft_pchar(data, '%', 1);
	data->len += ft_strlen(data->str);
	if (data->spec == 'c' && data->null && (!mod || data->f_minus))
		ft_putchar_fd(0, 1);
	if (mod)
		return ;
	ft_putstr_fd(data->str, 1);
	free(data->str);
}

int	ft_printf(const char *str, ...)
{
	t_data	*data;
	size_t	i;

	i = -1;
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (-1);
	data->len = 0;
	va_start(data->args, str);
	while (str[++i])
	{
		if (str[i] == '%' && ft_strchr("cspdiuxX%", str[i + 1]))
		{
			data->spec = str[i++ + 1];
			ft_pformat(data, 0);
		}
		else if (str[i] == '%')
			i += ft_pfmod((char *)(str + i + 1), data);
		else
			ft_pchar(data, str[i], 0);
	}
	va_end(data->args);
	i = data->len;
	free(data);
	return ((int)i);
}
