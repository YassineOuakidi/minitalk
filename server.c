

#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include "libft/libft.h"


void get(int signum , siginfo_t *info , void *context)
{
	
	static int	bit_count = 0;
	static char	c = 0;
	
	c|=(signum==SIGUSR2) << (7 - bit_count);
	bit_count++;

	if(bit_count==8)
	{
		write(1 , &c , 1);
		c = 0;
		bit_count = 0;
	}
}

int main()
{
	char 	*prompt;
	char	*tmp;

	tmp = ft_strjoin("PID>> " , ft_itoa(getpid()));
	prompt = ft_strjoin( tmp , "\n"); 
	free(tmp);
	
	write(1 , prompt , 7 + ft_strlen(ft_itoa(getpid())));

	struct sigaction psa;
	psa.sa_sigaction = get;

	sigaction(SIGUSR1 , &psa , NULL);
	sigaction(SIGUSR2 , &psa , NULL);

	while(1)	pause();
	
	return 0;
}
