#include "ft_printf/includes/ft_printf.h"
#include <signal.h>


void termination_handler (int signum)
{
  ft_printf("SIGUSR1 reçu !");
}

int
main (void)
{
    ft_printf("%d", getpid());

    struct sigaction new_action, old_action;

    /* Set up the structure to specify the new action. */
    new_action.sa_handler = termination_handler;
    sigemptyset (&new_action.sa_mask);
    new_action.sa_flags = 0;

    sigaction (SIGUSR1, &new_action, NULL);

    pause();

}
