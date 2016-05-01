/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_fct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfolly <tfolly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/10 16:14:09 by tfolly            #+#    #+#             */
/*   Updated: 2016/04/27 16:16:18 by tfolly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		two_oct(int c)
{
	char *mask;
	int count;

	//	ft_putendl("2oct");
	mask = ft_strdup("110xxxxx10xxxxxx");
	mask = fill_mask(mask, c);
	count = print_mask(mask, 2);
	return (count);
}

int		three_oct(int c)
{
	char *mask;
	int count;

	mask = ft_strdup("1110xxxx10xxxxxx10xxxxxx");
	mask = fill_mask(mask, c);
	count = print_mask(mask, 3);

	return (count);
}

int		four_oct(int c)
{
	char *mask;
	int count;

	mask = ft_strdup("11110xxx10xxxxxx10xxxxxx10xxxxxx");
	mask = fill_mask(mask, c);
	count = print_mask(mask, 4);

	return (count);
}


int		ft_printf_putlstr(t_data *data, va_list ap)
{
	int		count;
	int		*str;

	data->mwidth = 1;
	str = va_arg(ap, int*);
	if (!str)
	{
		ft_putstr("(null)");
		return (6);
	}
	count = 0;
	while (*str)
	{
		if (*str < 128)
		{
			ft_putchar(*str);
			count++;
		}
		else if (*str < 2048)
			count +=  (two_oct(*str));
		else if (*str < ft_pow(2, 15) * 2 - 1)
			count += three_oct(*str);
		else
			count += four_oct(*str);
		str++;
	}
	return (count);
}

//coder un char jusqua 4 octets, la limite utf8
int		ft_printf_putlchar(t_data *data, va_list ap)
{
	int		c;

	data->mwidth = 1;
	c = va_arg(ap, int);
	if (c < 128)
	{
		ft_putchar(c);
		return (1);
	}
	else if (c < 2048)
		return (two_oct(c));
	else if (c < ft_pow(2, 15) * 2 - 1)
		return (three_oct(c));
	else
		return (four_oct(c));
	//	return (0);//a retirer
}

int		ft_printf_putloct(t_data *data, va_list ap)
{
	unsigned long long	pow;
	unsigned long	res;
	int				count;
	unsigned long			nb;

	nb = va_arg(ap, unsigned long);
	data->mwidth = 1; //a retirer, c juste pour utiliser data
	count = 0;
	if (nb == 0)
	{
		ft_putchar('0');
		return (1);
	}
	else
		res = nb;
	pow = 1;
	while (pow <= res)
		pow *= 8;
	pow /= 8;
	while (pow)
	{
		ft_putchar('0' + res / pow);
		res = res - (res / pow) * pow;
		pow /= 8;
		count++;
	}
	return (count);
}

int		ft_printf_putoct(t_data *data, va_list ap)
{
	unsigned long long	pow;
	unsigned int	res;
	int				count;
	int				nb;

	nb = va_arg(ap, int);
	data->mwidth = 1; //a retirer, c juste pour utiliser data
	count = 0;
	if (nb == 0)
	{
		ft_putchar('0');
		return (1);
	}
	else
		res = nb;
	pow = 1;
	while (pow <= res)
		pow *= 8;
	pow /= 8;
	while (pow)
	{
		ft_putchar('0' + res / pow);
		res = res - (res / pow) * pow;
		pow /= 8;
		count++;
	}
	return (count);
}

int		ft_printf_putptr(t_data *data, va_list ap)
{
	unsigned long	pow;
	unsigned long	res;
	int				count;
	unsigned long	nb;

	data->mwidth = 1; //a retirer, c juste pour utiliser data
	count = 2;

	nb = va_arg(ap, unsigned long);
	if (nb == 0)
	{
		ft_putstr("0x0");
		return (3);
	}
	ft_putstr("0x");
	res = nb;
	pow = 1;
	while (res / pow >= 16)
		pow *= 16;
	while (pow)
	{
		if (res / pow < 10)
			ft_putchar('0' + res / pow);
		else
			ft_putchar('a' + res / pow - 10);
		res = res - (res / pow) * pow;
		pow /= 16;
		count++;
	}
	return (count);
}

int		ft_printf_puthexa(t_data *data, va_list ap)
{
	unsigned int	pow;
	unsigned int	res;
	int				count;
	int				nb;

	nb = va_arg(ap, int);
	data->mwidth = 1; //a retirer, c juste pour utiliser data
	count = 0;
	if (nb == 0)
	{
		ft_putchar('0');
		return (1);
	}
	res = nb;
	pow = 1;
	while (res / pow >= 16)
		pow *= 16;
	while (pow)
	{
		if (res / pow < 10)
			ft_putchar('0' + res / pow);
		else if (*(data->fmt) == 'x')
			ft_putchar('a' + res / pow - 10);
		else
			ft_putchar('A' + res / pow - 10);
		res = res - (res / pow) * pow;
		pow /= 16;
		count++;
	}
	return (count);
}

int		ft_printf_putstr(t_data *data, va_list ap)
{
	int		count;
	char	*str;

	//data->mwidth = 1; //a retirer, c juste pour utiliser data
	str = va_arg(ap, char*);
	if (!str)
	{
		ft_putstr("(null)");
		return (6);
	}
	count = 0;
	t_lst *lst = 0;
	while (*str)
	{
		lst = pushback_lst(lst, *str);
		str++;
	}
	lst = format_lst(lst, data);
	count = lst_len(lst);
	print_lst(lst);
	free_lst(lst);
	return (count);
	// {
	// 	ft_putchar(*str);
	// 	str++;
	// 	count++;
	// }
	return (count);
}

int		ft_printf_putlunbr(t_data *data, va_list ap)
{
	unsigned  long long	pow;
	unsigned  long	res;
	int		    	count;
	unsigned  long	nb;

	nb = va_arg(ap, unsigned long);
	data->mwidth = 1; //a retirer, c juste pour utiliser data
	count = 0;
	if (nb == 0)
	{
		ft_putchar('0');
		return (1);
	}
	res = nb;
	pow = 1;
	while (pow <= res / 10)
		pow *= 10;
	while (pow)
	{
		ft_putchar('0' + res / pow);
		res = res - (res / pow) * pow;
		pow /= 10;
		count++;
	}
	return (count);
}

int		ft_printf_putunbr(t_data *data, va_list ap)
{
	unsigned long long	pow;
	unsigned int	res;
	int				count;
	unsigned int			nb;

	nb = va_arg(ap, unsigned int);
	data->mwidth = 1; //a retirer, c juste pour utiliser data
	count = 0;
	if (nb == 0)
	{
		ft_putchar('0');
		return (1);
	}
	res = nb;
	pow = 1;
	while (pow <= res)
		pow *= 10;
	pow /= 10;
	while (pow)
	{
		ft_putchar('0' + res / pow);
		res = res - (res / pow) * pow;
		pow /= 10;
		count++;
	}
	return (count);
}

int		ft_printf_putlnbr(t_data *data, va_list ap)
{
	unsigned long long	pow;
	unsigned long	res;
	int				count;
	long long				nb;

	nb = va_arg(ap, long);
	data->mwidth = 1; //a retirer, c juste pour utiliser data
	count = 0;
	if (nb == 0)
	{
		ft_putchar('0');
		return (1);
	}
	if (nb < 0)
	{
		res = -nb;
		ft_putchar('-');
		count++;
	}
	else
		res = nb;
	pow = 1;
	while (pow <= res)
		pow *= 10;
	pow /= 10;
	while (pow)
	{
		ft_putchar('0' + res / pow);
		res = res - (res / pow) * pow;
		pow /= 10;
		count++;
	}
	return (count);
}


int		ft_printf_putnbr(t_data *data, va_list ap)
{
	unsigned long long	pow;
	unsigned int	res;
	int				count;
	int				nb;

	nb = va_arg(ap, int);
	data->mwidth = 1; //a retirer, c juste pour utiliser data
	count = 0;
	if (nb == 0)
	{
		ft_putchar('0');
		return (1);
	}
	if (nb < 0)
	{
		res = -nb;
		ft_putchar('-');
		count++;
	}
	else
		res = nb;
	pow = 1;
	while (pow <= res)
		pow *= 10;
	pow /= 10;
	while (pow)
	{
		ft_putchar('0' + res / pow);
		res = res - (res / pow) * pow;
		pow /= 10;
		count++;
	}
	return (count);
}

int		ft_printf_putchar(t_data *data, va_list ap)
{
	int		count;
	char	c;

	count = 0;
	while (count < data->mwidth - 1)
	{
		ft_putchar(' ');
		count++;
	}
	c = (char)va_arg(ap, int);
	ft_putchar(c);
	return (count + 1);
}
