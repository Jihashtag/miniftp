/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbert <jbert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/25 14:17:05 by jbert             #+#    #+#             */
/*   Updated: 2015/06/05 13:23:50 by jbert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int		action(char *s, int fd)
{
	if (!ft_strncmp(s, "lls", 3))
		exec_cmd(s + 1);
	else if (!ft_strncmp(s, "lmkdir", 6))
		exec_cmd(s + 1);
	else if (!ft_strncmp(s, "lrmdir", 6))
		exec_cmd(s + 1);
	else if (!ft_strncmp(s, "lrm", 3))
		exec_cmd(s + 1);
	else if (!ft_strncmp(s, "lcd", 3))
		ft_cd(s + 4);
	else if (!ft_strncmp(s, "lpwd", 4))
		ft_pwd(s);
	else if (!ft_strncmp(s, "get", 3))
		ft_get(s, fd);
	else if (!ft_strncmp(s, "put", 3))
		ft_put(s, fd);
	else if (!ft_strncmp(s, "quit", 4))
		return (0);
	else if (s[0])
		ft_send(s, fd);
	return (1);
}

int		read_sock(int fd)
{
	int		ret;
	char	buff[1025];
	char	prompt[1025];

	ft_bzero(buff, 1025);
	ft_bzero(prompt, 1025);
	while (ft_printf("%ecyan%e%s%eblue%e $> %eyellow%e", \
		getcwd(prompt, 1025)) && \
			(ret = read(0, buff, 1024)) > 0)
	{
		buff[ret - 1] = '\0';
		if (!action(buff, fd))
			break ;
		ft_bzero(buff, ret);
		ft_bzero(prompt, 1025);
	}
	return (ret);
}

int		sock_error(int i)
{
	if (i == 0)
		return (ft_putstr_fd("Error : could not create socket\n", 2));
	if (i == -1)
		return (ft_putstr_fd("Error : could not get protocol by name\n", 2));
	if (i == -2)
		return (ft_putstr_fd("Error : could not connect\n", 2));
	if (i == -3)
		return (ft_putstr_fd("Error : could not listen\n", 2));
	return (-1);
}

int		main(int ac, char **av)
{
	int					p;
	int					s;

	if (ac < 3)
		return (ft_putstr_fd("Error : not enough arguments\n", 2));
	if (av[3] && chdir(av[3]) != -1)
		ft_printf("Client root is : [%s]\n", home_save(getcwd(NULL, 1025)));
	else
		home_save(getcwd(NULL, 1025));
	p = ft_atoi(av[2]);
	if (p <= 0)
		return (ft_putstr_fd("Error : port should be positive\n", 2));
	s = ret_sock(av[1], p);
	if (s <= 0)
		return (sock_error(s));
	if (read_sock(s) < 0)
		return (ft_putstr_fd("Error while reading socks\n", 2));
	close(s);
	return (0);
}
