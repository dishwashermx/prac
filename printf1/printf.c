/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghwa <ghwa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:35:59 by ghwa              #+#    #+#             */
/*   Updated: 2024/02/28 17:23:04 by ghwa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0') {
		i++;
	}
	return (i);
}

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(char *s)
{
	write (1, s, ft_strlen(s));
	return (ft_strlen(s));
}

int	ft_putnbr(int i, int count)
{
	if (i == -2147483648) {
		write (1, "-2147483648", 11);
		return (11);
	}
	else if (i < 0) {
		write (1, "-", 1);
		i *= -1;
		count++;
	}
	if (i > 9)
		count = ft_putnbr(i/10, ++count);
	else
		count++;
	ft_putchar((i % 10) + '0');
	return (count);
}

int ft_putunbr(unsigned int i, int count)
{
	if (i > 9)
		count = ft_putunbr((i/10), ++count);
	else
		count++;
	ft_putchar((i % 10) + '0');
	return (count);
}

int	ft_putptr(unsigned int i, char code, int first, int count)
{
	char *hex;

	if (code == 'x' || code == 'p')
		hex = "0123456789abcdef";
	else if (code == 'X')
		hex = "0123456789ABCDEF";
	if (first == 1 && code == 'p')
		ft_putstr("0x");
	if (first == 1 && i == 0)
			return (ft_putchar('0'));
	if (i != 0) {
		count = ft_putptr((i / 16), code, 0, ++count);
		ft_putchar(hex[i % 16]);
	}
	return (count);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		count;

	count = 0;
	va_start(args, str);
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == '%') {
			if (str[i + 1] == 'c') {
				count += ft_putchar(va_arg(args, int));
			}
			else if (str[i + 1] == 's'){
				count += ft_putstr(va_arg(args, char *));
			}
			else if (str[i + 1] == 'd') {
				count += ft_putnbr(va_arg(args, int), 0);
			}
			else if (str[i + 1] == 'u') {
				count += ft_putunbr(va_arg(args, unsigned int), 0);
			}
			else if (str[i + 1] == 'p') {
				count += ft_putptr(va_arg(args, uintptr_t), 'p', 1, 0);
			}
			else if (str[i + 1] == 'x') {
				count += ft_putptr(va_arg(args, unsigned int), 'x', 1, 0);
			}
			else if (str[i + 1] == 'X') {
				count += ft_putptr(va_arg(args, unsigned int), 'X', 1, 0);
			}
			else if (str[i + 1] == '%') {
				count += ft_putchar('%');
			}
			i++;
		}
		else
			count += ft_putchar(str[i]);
		}
	va_end(args);
	return (count);
}

int	main(void)
{
	int	i;

	i = 1902;
	printf("%c char\n", 'c');
	printf("%d digit\n", i);
	printf("%s string\n", "string");
	printf("%u unsigned\n", i);
	printf("%p pointer\n", &i);
	printf("%x unsigned hex\n", i);
	printf("%X uppercase hex\n", i);
	printf("%% percent\n");
	ft_printf("%d\n", ft_printf("%p\n", &i));
	printf("\n\n");
	ft_printf("%c char\n", 'c');
	ft_printf("%d digit\n", i);
	ft_printf("%s string\n", "string");
	ft_printf("%u unsigned\n", i);
	ft_printf("%p pointer\n", &i);
	ft_printf("%x unsigned hex\n", i);
	ft_printf("%X uppercase hex\n", i);
	ft_printf("%% percent\n");
	ft_printf("%d\n", ft_printf("%p\n", &i));
	return (0);
}