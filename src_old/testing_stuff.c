/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_stuff.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwilsch <mwilsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:57:10 by mwilsch           #+#    #+#             */
/*   Updated: 2023/03/05 13:38:57 by mwilsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*cut_out(char *str, int start, t_data *data)
{
	int		len;
	int		i;
	int		earser;
	
	i = start + 1;
	len = 1;
	earser = 0;
	// checking if it's one or a a two redirect pair
	if (str[i] != ' ') // what about other white space?
	{
		len++;
		i++;
	} 
	// Skipping over whitespace between redirect and red argument
	while (incl_char(str[i], " \t"))
	{
		i++;
		earser++;
		if (incl_char(str[i], "<>")) // This has to depend on the right redirect tho
			return (err_msg("syntax error near unexpected token `>'\n"), NULL);
	}
	i -= earser;
		str = delete_substr(str, start + len, earser);
	while (str[i] && !incl_char(str[i], ">< "))
	{
		len++;
		i++;
	}
	return (ft_substr(str, start, len));
}







#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

// This is how I can capture output of a file and then redirect it into a fd
int main() {
    int fd = open("file.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    char *args[] = {"/bin/ls", "-l", NULL};
    char *envp[] = {NULL};

		
    
		dup2(fd, STDOUT_FILENO);



    
		execve("/bin/ls", args, envp);


    printf("Hello, world!\n");
		write(1, "YAHH", 4);
    close(fd);

    return 0;
}

/ #define BUFSIZE 1024

// int main() {
//     int pipefd[2];
//     pid_t pid;
//     char buf[BUFSIZE];
//     char output[10000] = "";
//     char *argv[] = {"ls", "-l", NULL};
//     char *envp[] = {NULL};

//     /* Create the pipe */
//     if (pipe(pipefd) == -1) {
//         perror("pipe");
//         exit(EXIT_FAILURE);
//     }

//     /* Create the child process */
//     pid = fork();
//     if (pid == -1) {
//         perror("fork");
//         exit(EXIT_FAILURE);
//     }

//     if (pid == 0) {
//         /* Child process */
//         /* Close the unused end of the pipe */
//         close(pipefd[0]);

//         /* Redirect stdout to the write end of the pipe */
//         dup2(pipefd[1], STDOUT_FILENO);

//         /* Execute the ls command */
//         if (execve("/bin/ls", argv, envp) == -1) {
//             perror("execve");
//             exit(EXIT_FAILURE);
//         }
//     } else {
//         /* Parent process */
//         /* Close the unused end of the pipe */
//         close(pipefd[1]);

//         /* Read the output from the read end of the pipe */
//         while (read(pipefd[0], buf, BUFSIZE) > 0) {
//             /* Concatenate to output string */
//             strcat(output, buf);
//         }

//         /* Close the pipe */
//         close(pipefd[0]);

//         /* Print the output */
//         // printf("%s", output);
//     }

//     return 0;