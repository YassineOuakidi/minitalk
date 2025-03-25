
#include <unistd.h>
#include <signal.h>
#include "libft/libft.h"



void send_char(int server_pid , char c)
{
	int	 i = 7;
	
	while(i>=0)
	{
		if((c>>i) & 1)
			kill(server_pid , SIGUSR2);
		else 
			kill(server_pid , SIGUSR1);
		i--;
		usleep(1000);
	}
}

void post(char **argv)
{
	int	server_pid;
	char	*message;
	size_t 	i;

	server_pid = ft_atoi(argv[1]);
	message = ft_strdup(argv[2]);

	i=0;
	while(message[i])
		send_char(server_pid , message[i++]);

	write(1 , "$\n" , 2);
}

int main(int argc , char **argv)
{
	if(argc!=3)
	{
		write(1 , "Usage: ./client <PID> <MESSAGE>\n" , 32);
	}
	else 
	{
		post(argv);
	}
}
