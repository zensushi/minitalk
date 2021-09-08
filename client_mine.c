#include "minitalk.h"

void		send_bit_by_bit(int pid, char *msg, size_t len)
{
	int8_t      r;
	int8_t      l;
	size_t      i;

	i = 0;
	while (i <= len)
	{
		r = 0;
		l = 7;
		while ((msg[i] >> l) == 0 && l > 1)
			l--;
		while (r <= l)
		{
			if ((msg[i] >> r) & 1)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			r++;
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
		send_bit_by_bit(pid, av[2], ft_strlen(av[2]));
	}
	else
		ft_putstr("usage:\n./client [server_pid] \"[msg_to_send]\"\n");
	return (0);
}
