/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putint_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 14:51:27 by ohakola           #+#    #+#             */
/*   Updated: 2019/12/17 14:52:24 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmatrix.h"

static	void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

/*
** ft_putint_fd() writes a given integer into given file descriptor.
*/

void			ft_putint_fd(int nb, int fd)
{
	int	digits[10];
	int	index;
	int sign;

	index = 0;
	sign = nb >= 0 ? 1 : -1;
	if (nb == 0)
		ft_putchar_fd('0', fd);
	while (nb != 0)
	{
		digits[index] = nb % 10;
		nb = nb / 10;
		index++;
	}
	index++;
	if (sign < 0)
		ft_putchar_fd('-', fd);
	while (--index > 0)
		ft_putchar_fd(sign * digits[index - 1] + '0', fd);
}
