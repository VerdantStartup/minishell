/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_stuff.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwilsch <mwilsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:57:10 by mwilsch           #+#    #+#             */
/*   Updated: 2023/03/06 16:57:20 by mwilsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// This is how I can capture output of a file and then redirect it into a fd
// int main() {
//     int fd = open("file.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
//     char *args[] = {"/bin/ls", "-l", NULL};
//     char *envp[] = {NULL};

		
    
// 		dup2(fd, STDOUT_FILENO);



    
// 		execve("/bin/ls", args, envp);


//     printf("Hello, world!\n");
// 		write(1, "YAHH", 4);
//     close(fd);

//     return 0;
// }

#include <stdbool.h>
#include <fcntl.h>

typedef struct s_data {
	int fd;
} t_data;

bool test(t_data *data)
{
	// char *str = ">"
	char c = '>';
	char *filename = "output";
	int cnt = 1;
	int	fd;
	
	if (c == '>' && cnt == 1)
		return (data->fd = open(filename, O_CREAT), true);
	return (true);
}

int main(void)
{
	t_data data;
	test(&data);
}