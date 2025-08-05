#include "minishell.h"

char *token_type_to_string(t_token_type type)
{
	switch (type)
	{
		case TK_WORD_0:         return "WORD";
		case TK_PIPE_1:         return "PIPE";
		case TK_REDIR_IN_2:     return "REDIR_IN";
		case TK_REDIR_OUT_3:    return "REDIR_OUT";
		case TK_REDIR_APPEND_4: return "REDIR_APPEND";
		case TK_HEREDOC_5:      return "HEREDOC";
		case TK_S_QUOTE_6:      return "S_QUOTE";
		case TK_D_QUOTE_7:      return "D_QUOTE";
		case TK_DOLLAR_8:       return "DOLLAR";
		default:                return "UNKNOWN";
	}
}

void debug_status(int status)
{
	printf("[DEBUG] Exit status: %d\n", status);
}

void debug_pipe_test(t_node *node)
{
	if (!node || !node->next)
		return;

	printf("[DEBUG] cmd1 = %s\n", node->argv[0]);
	printf("[DEBUG] cmd2 = %s\n", node->next->argv[0]);
}

static const char *redirect_type_to_string(int type)
{
	switch (type)
	{
		case TK_REDIR_IN_2:     return "REDIR_IN";
		case TK_REDIR_OUT_3:    return "REDIR_OUT";
		case TK_REDIR_APPEND_4: return "REDIR_APPEND";
		case TK_HEREDOC_5:      return "HEREDOC";
		default:                return "UNKNOWN";
	}
}

void debug_redirect_info(t_redir *redir)
{
	while (redir)
	{
		printf("  Redirect: %s (%d), filename=%s\n", 
			redirect_type_to_string(redir->type), redir->type, 
			redir->filename ? redir->filename : "NULL");
		redir = redir->next;
	}
}

void debug_print_nodes(t_node *node)
{
	int i = 0;
	int node_count = 0;
	t_node *current = node;
	
	if (!node)
	{
		printf("=== [DEBUG] NO NODES ===\n");
		return;
	}
	while (current)
	{
            node_count++;
		printf("---------- NODE %d ---------\n", node_count);
		if (current->argv)
		{
			i = 0;
			while (current->argv[i])
			{
				printf("argv[%d]: \"%s\"\n", i, current->argv[i]);
				i++;
			}
		}
		else
		{
			printf("argv: NULL\n");
		}
		if (current->token)
			printf("token type: %d (%s)\n", current->token->type, 
				token_type_to_string(current->token->type));
		else
			printf("token: NULL\n");
		if (current->redirs)
		{
			debug_redirect_info(current->redirs);
		}
		else
		{
			printf("Redirections: None\n");
		}
		printf("Node address: %p\n", (void *)current);
		if (current->next)
		{
			printf("Has next: Yes\n");
		}
		else
		{
			printf("Has next: No\n");
		}
		printf("-------- END NODE %d --------\n\n", node_count);
		current = current->next;
	}

	printf("[debug] total nodes: %d\n\n", node_count);
}

void debug_print_pipeline(t_node *head)
{
	int i = 0;
	while (head)
	{
		printf("[DEBUG] [Pipe %d] cmd: %s\n", i, head->argv[0]);
		head = head->next;
		i++;
	}
}

void debug_print_env(t_env *env)
{
	while (env)
	{
		printf("[DEBUG] ENV: %s=%s\n", env->key, env->value);
		env = env->next;
	}
}

void debug_print_array(char **arr)
{
	int i = 0;
	while (arr && arr[i])
	{
		printf("arr[%d]: %s\n", i, arr[i]);
		i++;
	}
}

void debug_execve_args(char *path, char **argv, char **env)
{
	printf("[DEBUG] execve path: %s\n", path);
	debug_print_array(argv);
	(void)env; // Ignora parametro non usato
}

void debug_path_resolution(char *cmd, t_env *env)
{
    printf("[DEBUG] Resolving path for: %s\n", cmd);
    char *path_var = get_env_value("PATH", env);
    printf("[DEBUG] PATH = %s\n", path_var ? path_var : "NULL");

}