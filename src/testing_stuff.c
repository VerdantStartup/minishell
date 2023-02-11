/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_stuff.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwilsch <mwilsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:57:10 by mwilsch           #+#    #+#             */
/*   Updated: 2023/02/08 21:29:47 by mwilsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "testing.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// The goal here is to trying to find ls in path
	// 1. Get PATH
	// 2. Split it with : as a delimiter
	// 3. Loop through all directories and run access with F_OK
		// F_OK check if the files exsits

int main(void)
{
	// 1. Get the PATH Environment Variable
	char *path_var = getenv("PATH");

	//	2. Split it every directory using : as delimiter
	char **path_modfiable = ft_split(path_var, ':'); 
	int i = 0;
	while (path_modfiable[i] != NULL)
	{
		// Add the command we are looking for to the subdirectory
		path_modfiable[i] = ft_strjoin(path_modfiable[i], "/ls");
		// Check if executable exsits with access
		if (access(path_modfiable[i], X_OK) == 0)
		{
			// printf("%s", path_modfiable[i]);
			break;
		}
		i++;
	}
	// argv contains the command and the flag, and the EOF
	char *argv[] = {"ls", "-l", NULL};
	// Execute takes in the absolute path, command with flags, and NULL
	execve(path_modfiable[i], argv, NULL);
}

// int main() {
//     char *argv[] = {"/bin/ls", "-l", NULL};
//     char *envp[] = {NULL};

//     int ret = execve("/Users/mwilsch/.brew/bin:/usr/local/bin", argv, envp);
//     if (ret == -1) {
//         perror("execve");
//         return 1;
//     }

//     return 0;
// }














