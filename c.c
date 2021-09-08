
#include "minitalk.h"

void		send_bit_by_bit(int pid, char *str)
{
	int		shift;
	size_t	i;

	i = 0;
	while (str[i])
	{
		shift = 0;
		while (shift < 7)
		{
			if ((str[i] >> shift) & 1)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			shift++;
			usleep(100);
		}
		i++;
	}
}

int			main(int ac, char **av)
{
	int		pid;

	if (ac == 3)
	{
		pid = atoi(av[1]);
		send_bit_by_bit(pid, itoa(ft_strlen(av[2])));
        sen_bit_by_bit(pid, " ");
        send_bit_by_bit(pid, av[1]);
	}
	else
		ft_putstr("usage: client server_pid msg_to_send\n");
	return (0);
}
