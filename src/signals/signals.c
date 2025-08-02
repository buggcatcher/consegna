/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mailinci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:55:15 by mailinci          #+#    #+#             */
/*   Updated: 2025/07/24 17:55:18 by mailinci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* * *
 * Gestisce il segnale SIGINT (Ctrl+C) durante l'input da readline.
 * Imposta la variabile globale g_sigint, stampa una nuova riga,
 * pulisce la riga corrente e mostra un nuovo prompt.
 */
void	handle_sigint(int sig)
{
	(void)sig;
	g_sigint = 1;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

/* * *
 * Configura i gestori dei segnali per la shell interattiva.
 * Imposta handle_sigint come gestore per SIGINT (Ctrl+C) e
 * ignora il segnale SIGQUIT (Ctrl+\) per evitare l'uscita indesiderata.
 */
void	setup_signals(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = handle_sigint;
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = SIG_IGN;
	sa.sa_flags = 0;
	sigaction(SIGQUIT, &sa, NULL);
}

/**
 * Ripristina i gestori di segnali al comportamento predefinito del sistema.
 * Utilizzata tipicamente prima di eseguire comandi esterni per assicurarsi
 * che abbiano il normale comportamento dei segnali.
 */
void	restore_default_signals(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = SIG_DFL;
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

/**
 * Configura i segnali SIGINT e SIGQUIT per essere completamente ignorati.
 * Utilizzata durante l'esecuzione di comandi che non dovrebbero essere
 * interrotti da questi segnali.
 */
void	ignore_signals(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = SIG_IGN;
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

/**
 * Signal handler specifico per heredoc.
 * Non usa readline functions, solo imposta g_sigint.
 */
void	handle_hdoc_sigint(int sig)
{
	(void)sig;
	g_sigint = 1;
	write(1, "\n", 1);
}

/**
 * Setup segnali specifico per heredoc (senza readline).
 */
void	setup_hdoc_signals(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = handle_hdoc_sigint;
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = SIG_IGN;
	sa.sa_flags = 0;
	sigaction(SIGQUIT, &sa, NULL);
}

