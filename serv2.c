/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serv2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbert <jbert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/05 10:28:13 by jbert             #+#    #+#             */
/*   Updated: 2015/06/05 10:29:23 by jbert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serv.h"

int		ret_sock(int p)
{
	int					s;
	struct protoent		*prot;
	struct sockaddr_in	saddr;

	prot = getprotobyname("tcp");
	if (!prot)
		return (-1);
	s = socket(PF_INET, SOCK_STREAM, prot->p_proto);
	if (s == -1)
		return (0);
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(p);
	saddr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(s, (const struct sockaddr *)&saddr, sizeof(saddr)) != 0)
		return (-2);
	if (listen(s, 42) != 0)
		return (-3);
	return (s);
}

void	ft_get(char *s, int sock)
{
	int		fd;
	char	buff[1025];
	int		ret;

	fd = open(s, O_RDONLY);
	if (fd <= 0)
	{
		ft_putall(s, " : got an error while opening\n");
		return ;
	}
	send(sock, s, 1020, 0);
	ft_bzero(buff, 1025);
	while ((ret = read(fd, buff, 1024)) > 0)
	{
		send(sock, buff, ret, 0);
		ft_bzero(buff, ret);
	}
	close(fd);
}

void	ft_put(char *s, int fd)
{
	char	tmp[1025];
	int		ret;
	int		file;

	ft_bzero(tmp, 1025);
	file = open(s, O_RDWR | O_CREAT, S_IRWXU);
	if (file < 0)
	{
		ft_putstr_fd("We could not open your file ...\n", fd);
		return ;
	}
	else
		ft_putstr_fd("ok", fd);
	while ((ret = recv(fd, tmp, 1024, 0)) > 0)
	{
		ret = write(file, tmp, ret);
		if (ret < 1024)
			break ;
	}
	if (ret <= 0)
		ft_putstr_fd("\nAn error occured\n", 2);
}

void	error(char *s)
{
	ft_printf("Error : [%s] is an invalid command\n", s);
}

int		action(char *s, int fd)
{
	if (!ft_strncmp(s, "ls", 2))
		exec_cmd(s);
	else if (!ft_strncmp(s, "mkdir", 5))
		exec_cmd(s);
	else if (!ft_strncmp(s, "rmdir", 5))
		exec_cmd(s);
	else if (!ft_strncmp(s, "rm", 2))
		exec_cmd(s);
	else if (!ft_strncmp(s, "cd", 2))
		ft_cd(s + 3);
	else if (!ft_strncmp(s, "pwd", 3))
		ft_pwd(s);
	else if (!ft_strncmp(s, "get", 3))
		ft_get(s + 4, fd);
	else if (!ft_strncmp(s, "put", 3))
		ft_put(s + 4, fd);
	else if (!ft_strncmp(s, "quit", 4))
		return (0);
	else if (s[0])
		error(s);
	if (s[0] && ft_strncmp(s, "get", 3) && ft_strncmp(s, "put", 3))
		write(fd, "\n\0", 2);
	return (1);
}
