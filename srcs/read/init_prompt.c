/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 17:45:51 by aroulin           #+#    #+#             */
/*   Updated: 2017/09/14 17:45:52 by aroulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

void			my_pwd(void)
{
    static char	*command[] = {"/bin/pwd"};
    pid_t	    father;
    int         fdout;
    int         fderr;

    fdout = open("/tmp/.pwd_info", O_CREAT | O_TRUNC | O_WRONLY, 0644);
    fderr = open("/tmp/.pwd_info_err", O_CREAT | O_TRUNC | O_WRONLY, 0644);
    if ((father = fork()) == -1)
        return ;
    if (!father)
    {
        dup2(fdout, STDOUT_FILENO);
        dup2(fderr, STDERR_FILENO);
        execve(command[0], command, NULL);
        exit(EXIT_FAILURE);
    }
    else
        wait(&father);
    close(fderr);
    close(fdout);
}

static void			git_branch(void)
{
    static char	*command[] = {"/usr/bin/git", "branch"};
    pid_t	    father;
    int         fdout;
    int         fderr;

    fdout = open("/tmp/.git_info", O_CREAT | O_TRUNC | O_WRONLY, 0644);
    fderr = open("/tmp/.git_info_err", O_CREAT | O_TRUNC | O_WRONLY, 0644);
    if ((father = fork()) == -1)
        return ;
    if (!father)
    {
        dup2(fdout, STDOUT_FILENO);
        dup2(fderr, STDERR_FILENO);
        execve(command[0], command, NULL);
        exit(EXIT_FAILURE);
    }
    else
        wait(&father);
    remove("/tmp/.git_info_err");
    close(fderr);
    close(fdout);
}

static int            get_str_from_branch(char **prompt)
{
    char		*line;
    int			fd;

    line = NULL;
    git_branch();
    fd = open("/tmp/.git_info", O_RDONLY);
    while (get_next_line(fd, &line))
    {
        if (line[0] == '*')
            break ;
        else
            free(line);
    }
    if (ft_strlen(line))
    {
        ft_strcpy((*prompt) + ft_strlen((*prompt)), "\x1B[31m git[\x1B[32m");
        ft_strcpy((*prompt) + ft_strlen((*prompt)), line + 2);
        ft_strcpy((*prompt) + ft_strlen((*prompt)), "\x1B[31m]");
        free(line);
        return (6 + ft_strlen(line + 2));
    }
    free(line);
    close(fd);
    remove("/tmp/.git_info");
    return (0);
}

static int          get_str_from_pwd(char **prompt)
{
    char        *tmp;
    int         i;
    int         s;
    int         fd;

    tmp = NULL;
    my_pwd();
    fd = open("/tmp/.pwd_info", O_RDONLY);
    get_next_line(fd, &tmp);
    s = 0;
    i = -1;
    while (tmp[++i])
        if (tmp[i] == '/')
            s = i;
    ft_strcpy((*prompt) + ft_strlen(*prompt), (!s) ? tmp : tmp + s + 1);
    s = ft_strlen(tmp + s + 1);
    remove("/tmp/.pwd_info");
    free(tmp);
    close(fd);
    return (!s ? 1 : s);
}

void			init_prompt(void)
{
    static char		*prompt;
    int             i;
    int             len;

    i = -1;
    len = 3;
    if (!prompt)
        prompt = (char *)ft_memalloc(sizeof(char) * 127);
    ft_strcpy(prompt + ft_strlen(prompt), "\x1B[1m\x1B[34m");
    len += get_str_from_pwd(&prompt);
    len += get_str_from_branch(&prompt);
    ft_strcpy(prompt + ft_strlen(prompt), " √ \x1B[0m");
    my_prompt(prompt);
    get_len_prompt(len);
}
