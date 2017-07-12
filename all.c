/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbert <jbert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/05 10:16:58 by jbert             #+#    #+#             */
/*   Updated: 2015/06/05 10:18:29 by jbert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

char	*home_save(char *s)
{
	static char	*save = NULL;

	if (s)
		save = s;
	return (save);
}

void	ft_putall(char *s1, char *s2)
{
	char	*tmp;

	tmp = ft_strjoin(s1, s2);
	ft_putstr(tmp);
	free(tmp);
}

char	*retcmd(char *s)
{
	if (!ft_strncmp(s, "ls", 2))
		return ("/bin/ls");
	if (!ft_strncmp(s, "mkdir", 5))
		return ("/bin/mkdir");
	if (!ft_strncmp(s, "rmdir", 5))
		return ("/bin/rmdir");
	if (!ft_strncmp(s, "rm", 2))
		return ("/bin/rm");
	return (NULL);
}

void	exec_cmd(char *s)
{
	char	*path;
	char	**av;
	int		i;
	pid_t	f;

	path = retcmd(s);
	av = ft_strsplit(s, ' ');
	f = fork();
	if (f < 0)
		ft_printf("Error while executing [%s] : could not fork\n", s);
	if (f == 0)
	{
		execv(path, av);
		ft_printf("Error while executing [%s] : \
this command did not exec\n", path);
	}
	wait4(f, NULL, WUNTRACED, NULL);
	i = 0;
	while (av[i])
	{
		free(av[i]);
		i++;
	}
	free(av);
}

void	ft_cd(char *s)
{
	char	pwd[1025];

	if (!s[0])
		chdir(home_save(NULL));
	else if (chdir(s) == -1)
		ft_printf("Error : [%s] could not be accessed\n", s);
	getcwd(pwd, 1025);
	if (ft_strncmp(home_save(NULL), pwd, ft_strlen(home_save(NULL))) != 0)
		chdir(home_save(NULL));
	getcwd(pwd, 1025);
	ft_putall(pwd, "\n");
}
