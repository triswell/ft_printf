/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpou-ale <tpou-ale@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 03:44:13 by tpou-ale          #+#    #+#             */
/*   Updated: 2022/02/12 04:17:32 by tpou-ale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_set_plus_space(t_data *data, int mode)
{
	char	*str;

	if (!mode || (!data->f_plus && !data->f_blank) || data->pos != 1)
		return ;
	if (data->f_plus)
		str = ft_strjoin("+", data->str);
	else
		str = ft_strjoin(" ", data->str);
	if (!str)
		return ;
	free(data->str);
	++(data->len);
	data->str = str;
	data->f_plus = 0;
	data->f_blank = 0;
}

void	ft_set_sharp(t_data *data)
{
	char	*str;
	char	*s;

	ft_set_plus_space(data, 1);
	if (data->f_sharp != 1 || data->zero)
		return ;
	str = (char *)ft_calloc(3, 1);
	if (!str)
		return ;
	str[0] = '0';
	str[1] = data->spec;
	s = ft_strjoin(str, data->str);
	free(str);
	if (!s)
		return ;
	data->len += 2;
	free(data->str);
	data->str = s;
	data->f_sharp = 2;
}

void	ft_change_sign(t_data *d, int mode)
{
	if (mode == 2 && ft_strchr("di", d->spec)
		&& (ft_strchr(d->str, ' ') > ft_strchr(d->str, '0')))
	{
		ft_swap(ft_strchr(d->str, ' '), ft_strchr(d->str, '0'));
		return ;
	}
	if ((d->prec && !mode)
		|| (!d->f_zero && !d->prec) || d->pos || !ft_strchr("di", d->spec))
		return ;
	if (ft_strchr(d->str, '0') < ft_strchr(d->str, '-'))
		ft_swap(ft_strchr(d->str, '0'), ft_strchr(d->str, '-'));
	d->pos = 2;
}
