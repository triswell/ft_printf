/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fanalyze.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpou-ale <tpou-ale@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 17:07:21 by tpou-ale          #+#    #+#             */
/*   Updated: 2022/02/01 17:07:25 by tpou-ale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_init_flags(t_data *data)
{
	data->f_minus = 0;
	data->f_zero = 0;
	data->f_plus = 0;
	data->f_blank = 0;
	data->f_sharp = 0;
	data->period = 0;
	data->width = 0;
	data->prec = 0;
	data->str = ft_strdup("");
	data->pos = 0;
	data->zero = 0;
	data->null = 0;
}

static void	ft_set_flags(char flag, t_data *data)
{
	if (!data)
		return ;
	if (flag == '-')
		data->f_minus = 1;
	else if (flag == '0')
		data->f_zero = 1;
	else if (flag == '+')
		data->f_plus = 1;
	else if (flag == ' ')
		data->f_blank = 1;
	else if (flag == '#')
		data->f_sharp = 1;
}

ssize_t	ft_fanalyze(char *mod, t_data *data)
{
	ssize_t	i;

	i = -1;
	ft_init_flags(data);
	while (!ft_strchr("cspdiuxX123456789.", mod[++i]))
		if (ft_strchr("-0+ #", mod[i]))
			ft_set_flags(*ft_strchr("-0+ #", mod[i]), data);
	if (ft_isdigit(mod[i]))
	{
		data->width = (ssize_t)ft_atoi((char *)(mod + i));
		while (ft_isdigit(mod[i]))
			++i;
	}
	if (mod[i] == '.')
	{
		data->period = 1;
		if (ft_isdigit(mod[++i]))
			data->prec = (ssize_t)ft_atoi(mod + i);
		while (ft_isdigit(mod[i]))
			++i;
	}
	if (ft_strchr("cspdiuxX%", mod[i]))
		data->spec = (char)*(ft_strchr("cspdiuxX%", mod[i++]));
	return (i);
}
