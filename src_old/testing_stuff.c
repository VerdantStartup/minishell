/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_stuff.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwilsch <mwilsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:57:10 by mwilsch           #+#    #+#             */
/*   Updated: 2023/03/04 14:36:41 by mwilsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>










// #define BUFSIZE 1024

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
// }

// int main() {
//     char *args[] = {"wc", "Makefile", "-l", NULL};
//     char *envp[] = {NULL};

//     int ret = execve("/usr/bin/wc", args, envp);
//     if (ret == -1) {
//         perror("execve");
//         return 1;
//     }

//     return 0;
// }


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