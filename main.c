/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manavarr <manavarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 13:20:38 by manavarr          #+#    #+#             */
/*   Updated: 2022/08/29 13:30:03 by manavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
void	ft_putstr(char *str)
{
	char	c;
	int		i;

	i = 0;
	c = str[i];
	while (c != '\0')
	{
		write(1, &c, 1);
		i++;
		c = str[i];
	}
}

int	ft_length(char *buf)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	res = 0;
	while (buf[i] != '\n')
	{
		i++;
	}
	i++;
	while (buf[i] != '\n')
	{
		i++;
		res++;
	}
	return (res);
}

int	ft_comp_lin(char *buf)
{
	int	i;
	int	res;
	int	x;

	i = 0;
	res = 0;
	while (buf[i] != '\n')
		i++;
	i++;
	while (buf[i] != '\0')
	{
		x = 0;
		while (buf[i] != '\n' && buf[i] != '\0')
		{
			i++;
			x++;
		}
		if (x != ft_length(buf))
			return (1);
		i++;
	}
	return (0);
}

int	ft_atoi(char *buf)
{
	int	x;
	int	num;

	x = 0;
	num = 0;
	while (buf[x] >= '0' && buf[x] <= '9')
	{
		num = num * 10 + buf[x] - 48;
		x++;
	}
	return (num);
}

void	print_matrix(char **mat, char *buf)
{
	int	i;

	i = 0;
	while (i < ft_atoi(buf))
	{
		ft_putstr(mat[i]);
		write(1, "\n", 1);
		i++;
	}
}

char	*info(char *buf)
{
	int		x;
	int		num;
	char	*info;

	info = ((char *)malloc(3 * sizeof(char)));
	x = 0;
	num = 0;
	while (buf[x] >= '0' && buf[x] <= '9')
	{
		x++;
	}
	while (num < 3)
	{
		info[num] = buf[x];
		x++;
		num++;
	}
	return (info);
}

int	ft_comp_salt(char *buf)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (buf[i] != '\0')
	{
		if (buf[i] == '\n')
		{
			x++;
		}
		i++;
	}
	if (x == ft_atoi(buf) + 1)
	{
		return (0);
	}
	return (1);
}

int	ft_comp_car(char *buf)
{
	if (info(buf)[0] == info(buf)[1] && info(buf)[0] == info(buf)[2] && info(buf)[2] == info(buf)[1])
	{
		return (1);
	}
	return (0);
}

int	ft_comp_val(char *buf)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (buf[i] != '\n')
		i++;
	i++;
	while (buf[i] != '\0')
	{
		if (buf[i] != info(buf)[0] && buf[i] != info(buf)[1] && buf[i] != info(buf)[2] && buf[i] != '\n' && buf[i] != '\0')
			return (1);
		i++;
	}
	return (0);
}

void	ft_matriz(char **m, char *buf, int lin)
{
	int	i;
	int	x;
	int	q;

	i = 0;
	q = 0;
	x = 0;
	while (buf[i] != '\n')
	{
		i++;
	}
	i++;
	while (x < lin)
	{
		q = 0;
		while (buf[i] != '\n')
		{
			m[x][q] = buf[i];
			i++;
			q++;
		}
		m[x][q] = '\0';
		i++;
		x++;
	}
}

void	escribir(char **m, int *esc, int num, char *buf)
{
	int		x;
	int		y;
	char	c;

	c = info(buf)[2];
	x = esc[0] - 1;
	while (x >= esc[0] - num)
	{
		y = esc[1] - 1;
		while (y >= esc[1] - num)
		{
			m[y][x] = c;
			y--;
		}
		x--;
	}
}

int	comprueba(char **m, char *val, char *buf)
{
	int		i;
	int		q;
	char	*c;

	c = info(buf);
	i = 0;
	while (i < val[0] - 48)
	{
		q = 0;
		while (q < val[0] - 48)
		{
			if (m[i + val[2] - 48][q + val[1] - 48] == c[1])
				return (1);
			q++;
		}
		i++;
	}
	return (0);
}

int	*comprueba2(char **m, char *val, char *buf)
{
	int		i;
	int		q;
	char	c;
	int		*esc;

	c = info(buf)[1];
	esc = ((int *)malloc(2 * sizeof(int)));
	i = 0;
	esc[0] = -1;
	esc[1] = -1;
	while (i < val[0] - 48)
	{
		q = 0;
		while (q < val[0] - 48)
		{
			if (m[i + val[2] - 48][q + val[1] - 48] == c)
				return (esc);
			q++;
		}
		i++;
	}
	esc[0] = i + val[1] - 48;
	esc[1] = i + val[2] - 48;
	return (esc);
}

int	mover_cuadrado(char **mat, char *buf, int num)
{
	int		x;
	int		y;
	char	val[3];

	y = 0;
	while (y <= ft_atoi(buf) - num)
	{
		x = 0;
		while (x <= ft_length(buf) - num)
		{
			if (num <= ft_length(buf))
				val[0] = num + 48;
			else if (num > ft_length(buf))
				val[0] = ft_length(buf) + 48;
			val[1] = x + 48;
			val[2] = y + 48;
			if (comprueba(mat, val, buf) == 0)
				return (num);
			x++;
		}
		y++;
	}
	return (0);
}

int	*mover_cuadrado2(char **mat, char *buf, int num)
{
	int		x;
	int		y;
	char	val[3];

	y = 0;
	while (y <= ft_atoi(buf) - num)
	{
		x = 0;
		while (x <= ft_length(buf) - num)
		{
			if (num <= ft_length(buf))
				val[0] = num + 48;
			else if (num > ft_length(buf))
				val[0] = ft_length(buf) + 48;
			val[1] = x + 48;
			val[2] = y + 48;
			if (comprueba2(mat, val, buf)[0] != -1 && comprueba2(mat, val,
					buf)[1] != -1)
				return (comprueba2(mat, val, buf));
			x++;
		}
		y++;
	}
	return (comprueba2(mat, val, buf));
}

void	ft_heart(char *buf)
{
	char	**mat;
	int		i;
	int		x;

	x = ft_atoi(buf);
	i = 0;
	mat = (char **)malloc(x * sizeof(char *));
	while (i < x)
	{
		mat[i] = (char *)malloc(ft_length(buf) * sizeof(char));
		i++;
	}
	if (x <= ft_length(buf))
		ft_matriz(mat, buf, x);
	else if (x > ft_length(buf))
		ft_matriz(mat, buf, ft_length(buf));
	while (x != 0 && mover_cuadrado(mat, buf, x) == 0)
		x--;
	escribir(mat, mover_cuadrado2(mat, buf, x), x, buf);
	if (ft_comp_car(buf) == 1 || ft_comp_lin(buf) == 1 || ft_comp_salt(buf) == 1 || ft_comp_val(buf) == 1 || ft_length(buf) < 1)
		write(1, "map error\n", 10);
	else
		print_matrix(mat, buf);
}

int	main(int argc, char **argv)
{
	int		fd;
	char	buf[100000];
	ssize_t	nr_bytes;

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		nr_bytes = read(fd, buf, 100000);
		close(fd);
		ft_heart
	(buf);
	}
}

//mucha ayuda recibida por pecampos - 42Málaga
//https://github.com/pejor76