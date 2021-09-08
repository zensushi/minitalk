
#include "minitalk.h"

static t_msg g_msg;

void		       get_len(int bit)
{
	g_msg.c += ((bit & 1) << g_msg.size);
	g_msg.size++;
	if (g_msg.size == 7)
	{
		g_msg.len *= 10;
		g_msg.len += g_msg.c - '0';
		g_msg.c = 0;
		g_msg.size = 0;
	}
}

void			get_bit_by_bit(int bit)
{
	g_msg.c += ((bit & 1) << g_msg.size);
	g_msg.size++;
	if (g_msg.size == 7)
	{
		*g_msg.msg = g_msg.c;
		(*g_msg.msg)++;
		if (!g_msg.c)
		{
			*g_msg.msg = 0;
			(*g_msg.msg) -= g_msg.len;
			ft_putstr(g_msg.msg);
		}
		g_msg.c = 0;
		g_msg.size = 0;
	}
}

void            usr1(int s)
{

}

int				main(void)
{
	struct sigaction sa;
	sa.sa_handler = &usr1;
	sigaction(SIGUSR1, &sa, NULL);
	g_msg.c = 0;
	g_msg.size = 0;
	g_msg.len = 0;
	ft_putstr("server pid : ");
	ft_putnbr(getpid());
	ft_putchar('\n');
	signal(SIGUSR2, get_len);
	signal(SIGUSR1, get_len);
	g_msg.msg = malloc(g_msg.len);
	while (1)
	{
		signal(SIGUSR2, get_bit_by_bit);
		signal(SIGUSR1, get_bit_by_bit);
		pause();
	}
}
