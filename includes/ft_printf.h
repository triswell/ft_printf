/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpou-ale <tpou-ale@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 19:37:28 by tpou-ale          #+#    #+#             */
/*   Updated: 2022/01/30 20:42:46 by tpou-ale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdio.h>
# include "libft.h"

typedef struct s_data
{
	va_list			args;
	unsigned char	f_minus;
	unsigned char	f_zero;
	unsigned char	f_plus;
	unsigned char	f_blank;
	unsigned char	f_sharp;
	unsigned char	pos;
	unsigned char	zero;
	unsigned char	null;
	size_t			width;
	unsigned char	period;
	size_t			prec;
	char			spec;
	void			*str;
	size_t			len;
}					t_data;

int		ft_printf(const char *format, ...);

void	ft_pformat(t_data *data, char mod);

void	ft_pchar(t_data *data, char c, int mode);

void	ft_pstring(t_data *data);

void	ft_pnumber(t_data *data);

void	ft_punsigned(t_data *data);

// Pointers

void	ft_ppointer(t_data *data);

// Hexa

void	ft_phex(t_data *data);

// ANALYSE

ssize_t	ft_pfmod(char *format, t_data *data);

ssize_t	ft_fanalyze(char *mod, t_data *data);

void	ft_init_flags(t_data *data);

// FLAGS && MODIFIERS

void	ft_set_precision(t_data *data);

void	ft_set_plus_space(t_data *data, int mode);

void	ft_set_sharp(t_data *data);

void	ft_set_width(t_data *data, char c);

void	ft_change_sign(t_data *d, int mode);

// UTILS

void	ft_swap(char *i, char *j);

#endif //FT_PRINTF_H
