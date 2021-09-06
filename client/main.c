#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#define FAILURE -1
#define SUCCESS 1 

void	set_tab(int *tab, size_t size)
{
	size_t	i;

	i = 0;
	while (i < (size * 8 + 1))
	{
		tab[i] = -1;
		i++;
	}
}

int	get_bin_from_char(char c, int *tab)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (c & (1 << (7 - i)))
			tab[i] = 1;
		else
			tab[i] = 0;
		i++;
	}
	return (1);
}

int	*format_msg(char *str, int *tab)
{
	size_t	size;
	size_t	i;

	size = strlen(str);
	tab = malloc(sizeof(char) * size * 8 + 1);
	if (tab < 0)
		return (NULL);
	set_tab(tab, size);
	i = 0;
	while (i < size)
	{
		get_bin_from_char(str[i], &tab[8 * i]);
		i++;
	}
	return (tab);
}

int	send_msg(int pid, int *tab)
{
	size_t	i;

	i = 0;
	while (tab[i] != -1)
	{
		if (tab[i] == 1)
			kill(pid, SIGUSR2);
		else if (tab[i] == 0)
			kill(pid, SIGUSR1);
		i++;
		usleep(10);
	}
	free(tab);
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	int	pid;
	int	*tab;

	if (argc != 3)
		return (FAILURE);
	pid = atoi(argv[1]);
	tab = format_msg(argv[2], tab);
	if (tab == NULL)
		return (FAILURE);
	send_msg(pid, tab);
	return (SUCCESS);
}
