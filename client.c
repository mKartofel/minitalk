/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 11:28:56 by vfiszbin          #+#    #+#             */
/*   Updated: 2022/01/28 21:20:35 by vfiszbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/includes/ft_printf.h"
#include <stdlib.h>
#include <signal.h>

#include<stdio.h>

int g_message_over = 0;


void handle_exit()
{
    ft_printf("Erreur client\n");
    exit(2);
}

/*
La fonction est appelée par send_msg() une fois le message complètement envoyé, 
elle sert à envoyer le char null (8 bits 0) au serveur pour signaler la fin du message.
*/
void send_null_char_bit(int pid)
{
    static int s_pid = 0;
    static int nb_null_bits_sent = 0;

    if (pid != 0)
        s_pid = pid;
    if (kill(s_pid, SIGUSR1) == -1)
        handle_exit();
    nb_null_bits_sent++;
    //printf("nb_null_bits_sent=%d\n", nb_null_bits_sent);
    if (nb_null_bits_sent >= 8)
        {
            printf("Message envoyé au serveur\n");
            exit(0);
        }

}

/*
128 codé en binaire sur 8 bits = 10000000
C'est ce 1 qu'on déplace en utilisant un bitwise operator pour assigner un bit 0 ou 1 au char c

*/
void send_char_bit(int pid, char* msg)
{
    static char * s_msg = NULL;
    static int nb_bits_sent = 0;
    static int i = 0;
    static int s_pid = 0;

    if (msg != NULL)
        s_msg = msg;
    if (pid != 0)
        s_pid = pid;

    //printf("s_msg=%s\n",s_msg);
    if (s_msg[i] == '\0')
    {
        send_null_char_bit(s_pid);
        g_message_over = 1;
        return ;
    }
    if ((s_msg[i] & (128 >> nb_bits_sent)) != 0)
    {
        if (kill(s_pid, SIGUSR2) == -1)
            handle_exit();
        //printf("1\n"); 
    }
    else
    {
        if (kill(s_pid, SIGUSR1) == -1)
            handle_exit();
        //printf("0\n");
    }
    nb_bits_sent++;
    if (nb_bits_sent >= 8)
    {
        nb_bits_sent = 0;
        i++;
    }

}


void handle_SIGUSR(int signum)
{
    //printf("signum=%d\n",signum);
	if (signum == SIGUSR1)
    {
        if (g_message_over == 0)
            send_char_bit(0, NULL);
        else
            send_null_char_bit(0);
    }
    else if (signum == SIGUSR2)
    {
        ft_printf("Le serveur s'est interrompu, arrêt du client...\n");
        handle_exit();
    }
    
}


int main (int argc, char ** argv)
{
    int pid;

    if (argc != 3 || !argv[1] || !argv[2] || ft_strlen(argv[2]) == 0)
    {
        ft_printf("Usage : %s <PID> <Message>\n", argv[0]);
        exit(1);
    }
    pid = ft_atoi(argv[1]);
    if (!pid)
    {
        ft_printf("Incorrect PID\nUsage : %s <PID> <Message>\n", argv[0]);
        exit(1);
    }

	signal (SIGUSR1, handle_SIGUSR);
	signal (SIGUSR2, handle_SIGUSR);

    send_char_bit(pid, argv[2]);

    while (1)
        pause();
    
    return(0);
}
