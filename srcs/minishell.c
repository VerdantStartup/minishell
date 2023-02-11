/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwilsch <mwilsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 09:15:25 by tklouwer          #+#    #+#             */
/*   Updated: 2023/02/07 19:45:43 by mwilsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_builtins.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/07 14:05:40 by tklouwer      #+#    #+#                 */
/*   Updated: 2023/02/07 15:16:17 by tklouwer      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

enum {
    CD,
    PWD,
    ECHO,
    EXPORT,
    UNSET,
    ENV,
    EXIT
};

int echo(int argc, char **argv)
{
    int i;

    i = 1;
    rl_on_new_line();
        while (i < argc)
        {
            printf("%s", argv[i]);
            if (i != argc - 1)
                printf(" ");
            i++;
        }
    printf("\n");
    return (i);
}

int cd(int argc, char **argv)
{
    if (!argc || !argv)
        return (perror("chdir"), 1);
    if (chdir(argv[1]) != 0) 
        perror("chdir");
  return (EXIT_SUCCESS);
}

int pwd(char *input)
{
    char *cwd;

    cwd = getcwd(input, 1024);
    if (!cwd)
        return (perror("getcwd"), 1);
    printf("%s", cwd);
    return (EXIT_SUCCESS);
}

int sh_exit(status)
{
    exit(status);
}

int env()
{    
    extern char **environ;
    char **envp;

    envp = environ;
    while (*envp != NULL) 
    {
        printf("%s\n", *envp);
        envp++;
    }
  return 0;
}

void unset(const char* name) 
{
    extern char **environ;
    int len;
    int i;
    int j;

    len = ft_strlen(name);
    i = 0;
    while (environ[i])
    {
        j = 0;
        if (ft_strncmp(environ[i], name, len) == 0 && environ[i][len] == '=') 
        {
            while(environ[j])
            {
                environ[j] = environ[j + 1];
                j++;
            }
            break;
        }
        i++;
    }
}

 



