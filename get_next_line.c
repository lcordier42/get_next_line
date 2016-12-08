#include "get_next_line.h"
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

static int ft_reallocreste(char **reste)
{
    char *tmp;

    if (!(tmp = ft_strnew(ft_strlen(*reste))))
        return (0);
    ft_strcpy(tmp, *reste);
    *reste = NULL;
    if (!(*reste = ft_strnew(ft_strlen(tmp) + BUFF_SIZE)))
        return (0);
    ft_strcpy(*reste, tmp);
    return (1);
}

static int ft_putreste(char **reste, char **line)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (*reste[i] != '\n')
    {
        *line[i] = *reste[i];
        i++;
    }
    *line[i] = '\0';
    if (*reste[i] == '\n')
    {
        while (*reste[i])
        {
            *reste[j] = *reste[i];
            i++;
            j++;
        }
        *reste[j] = '\0';
        return (1);
    }
    return (0);
}

static int ft_checkndl(char **line)
{
    int i;

    i = 0;
    while (i < BUFF_SIZE)
    {
        if (*line[i] == '\n')
            return (1);
        i++;
    }
    return (0);
}

int get_next_line(const int fd, char **line)
{
    static char *reste;
    int ret;

    if (fd < 0 || !(*line))
        return (-1);
    while ((ret = read(fd, *line, BUFF_SIZE) > 0)
    {
        if (!(ft_reallocreste(&reste)))
            return (-1);
        ft_strncat(save, *line, BUFF_SIZE)
        if (ft_checkndl(line) == 1)
            break ;
    }
    if (ft_putreste(&reste, line) == 0)
        return (1);
    return (0);
}







int	main(int argc, char ** argv)
{
	int		fd;
	int		fd2;
	char	*line;
	pid_t	child;
	char	n = '\n';

	if (argc < 2)
	{
		printf("Usage %s <filename>\n", argv[0]);
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	fd2 = open("me.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == -1 || fd2 == -1)
	{
		perror("open");
		close(fd);
		close(fd2);
		return (-1);
	}
	while (get_next_line(fd, &line) == 1)
	{
		write(fd2, line, strlen(line));
		write(fd2, &n, 1);					// attention si le fichier test n a pas de \n et que ca affiche une erreur c'est normal
		free(line);							// vous inquietez pas
	}
	close(fd);
	close(fd2);
	child = fork();
	if (child == 0)
	{
		char	*arg[] = {"/usr/bin/diff", NULL, "me.txt", NULL};

		arg[1] = argv[1];
		execve(arg[0], arg, NULL);
		exit(0);
	}
	else
		wait(NULL); // bad code I know ... but it's not the project
	(void)argc;
	(void)argv;
	return (0);
}
