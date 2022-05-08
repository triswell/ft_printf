/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_modifiers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpou-ale <tpou-ale@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 17:07:21 by tpou-ale          #+#    #+#             */
/*   Updated: 2022/02/09 17:07:25 by tpou-ale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_set_precision(t_data *d)
{
	char	*str;
	char	*s;
	int		diff;

	diff = (int)(d->prec - ft_strlen(d->str)) + !d->pos
		* (ft_strchr("di", d->spec) != 0);
	if (!d->period || (d->spec != 's' && diff <= 0))
		return ;
	if (d->spec == 's')
		s = ft_substr(d->str, 0, d->prec);
	else
	{
		str = (char *)ft_calloc(diff + 1, 1);
		if (!str)
			return ;
		s = ft_strjoin(ft_memset(str, '0', diff), d->str);
		free(str);
	}
	d->len += (d->spec == 's') * -1 * (ft_strlen(d->str) - ft_strlen(s))
		+ (d->spec != 's') * diff;
	if (!s)
		return ;
	free(d->str);
	d->str = s;
	ft_change_sign(d, 1);
}

void	ft_set_width(t_data *d, char c)
{
	char	*str;
	char	*s;
	int		i;

	ft_set_plus_space(d, c == ' ');
	i = (int)(d->width - ft_strlen(d->str) - d->null
			- ((d->f_blank || d->f_plus) && d->pos && c == '0'))
		- 2 * (d->f_sharp != 0) * (c == '0') * !d->zero;
	if (i <= 0)
		return ;
	str = (char *)ft_calloc(i + 1, 1);
	if (!str)
		return ;
	ft_memset(str, c, i);
	if (c == ' ' && d->f_minus)
		s = ft_strjoin(d->str, str);
	else
		s = ft_strjoin(str, d->str);
	free(str);
	if (!s)
		return ;
	d->len += i;
	free(d->str);
	d->str = s;
}
