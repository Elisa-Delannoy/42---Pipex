/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelanno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:53:19 by edelanno          #+#    #+#             */
/*   Updated: 2024/11/18 16:53:20 by edelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# define BASE16 "0123456789abcdef"

# include <stdarg.h>
# include <unistd.h>

int	ft_putchar(char c);
int	ft_putstr(char *s);
int	ft_convert10to16(size_t nb, char c, int j);
int	ft_putnbr(long int n, int i);
int	ft_conversions(char c, va_list argp);
int	ft_printf(const char *format, ...);
int	ft_testneghexa(size_t nb);

#endif
