/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_stuff.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwilsch <mwilsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:57:10 by mwilsch           #+#    #+#             */
/*   Updated: 2023/03/01 17:16:55 by mwilsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// The goal here is to trying to find ls in path
	// 1. Get PATH
	// 2. Split it with : as a delimiter
	// 3. Loop through all directories and run access with F_OK
		// F_OK check if the files exsits

// int main(void)
// {
// 	// 1. Get the PATH Environment Variable
// 	char *path_var = getenv("PATH");

// 	//	2. Split it every directory using : as delimiter
// 	char **path_modfiable = ft_split(path_var, ':'); 
// 	int i = 0;
// 	while (path_modfiable[i] != NULL)
// 	{
// 		// Add the command we are looking for to the subdirectory
// 		path_modfiable[i] = ft_strjoin(path_modfiable[i], "/ls");
// 		// Check if executable exsits with access
// 		if (access(path_modfiable[i], X_OK) == 0)
// 		{
// 			// printf("%s", path_modfiable[i]);
// 			break;
// 		}
// 		i++;
// 	}
// 	// argv contains the command and the flag, and the EOF
// 	char *argv[] = {"echo", "$HOME", NULL};
// 	// Execute takes in the absolute path, command with flags, and NULL
// 	execve(path_modfiable[i], argv, NULL);
// }

int main() {
    char *argv[] = {"ls", "-llibft", NULL};
    char *envp[] = {NULL};

    int ret = execve("/bin/ls", argv, envp);
    if (ret == -1) {
        perror("execve");
        return 1;
    }

    return 0;
}










// Prototype & libary
#include <stdlib.h>

char *getenv(const char *name);

// Example
#include <stdio.h>
#include <stdlib.h>

int main() {
    char *value = getenv("HOME");
    if (value == NULL) {
        perror("getenv");
        return 1;
    }

    printf("HOME=%s", value);
    return 0;
}



