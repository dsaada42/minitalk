#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <math.h>

char	bin_to_dec(int nb)
{
	int	dec;
	int	i;
	int	rem;
	int	base;

	dec = 0;
	base = 1;
	while (nb != 0)
	{
		rem = nb % 10;
		nb = nb / 10;
		dec = dec + rem * base;
		base = base * 2;
		i++;
	}
	return (dec);
}

void	handler(int signo)
{	
	static int	i = 0;
	static int	res = 0;
	char		c;

	if (signo == SIGUSR1)
	{
		res = res * 10;
		i++;
	}
	else if (signo == SIGUSR2)
	{
		res = res * 10 + 1;
		i++;
	}
	if (i == 8)
	{
		i = 0;
		c = bin_to_dec(res);
		res = 0;
		write(1, &c, 1);
	}
}

int	main(int argc, char **argv)
{
	pid_t	pid;
	int		res[2];

	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	pid = getpid();
	printf("pid: %d\n", pid);
	while (1)
	{
		sleep(1);
	}
	return (1);
}
