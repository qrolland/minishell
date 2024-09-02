SRCS	=	lexer/lexer.c\
			lexer/token_list_utils.c\
			lexer/check_error.c\
			lexer/lexer_utils.c\
			parser/parser.c\
			parser/parse_input.c\
			parser/parse_output.c\
			parser/parse_heredoc.c\
			parser/command_utils.c\
			expansion/env.c\
			expansion/quote_expansion.c\
			expansion/var_expansion_heredoc.c\
			expansion/var_expansion.c\
			expansion/var_split.c\
			expansion/expansion_utils.c\
			execution/execution.c\
			execution/exec_child.c\
			execution/exec_utils.c\
			builtin/cd.c\
			builtin/echo.c\
			builtin/env.c\
			builtin/exit.c\
			builtin/export.c\
			builtin/pwd.c\
			builtin/unset.c\
			builtin/builtin_utils.c\
			builtin/env_utils.c\
			builtin/env_utils2.c\
			utils/error.c\
			utils/free.c\
			utils/fd_utils.c\
			utils/signals.c\
			utils/init.c\
			main.c

OBJS	= ${SRCS:.c=.o}

NAME	= minishell

LIBFT	= ./libft/libft.a

INC		= -I ./includes -I ./libft

CC		= cc

RM		= rm -f

CFLAGS	= -Wall -Wextra -Werror

%.o:		%.c
		${CC} ${CFLAGS} -c $< -o $@ ${INC}

all:	${NAME}

${LIBFT}:
		@make all -C libft
		@make bonus -C libft

${NAME}:	${LIBFT} ${OBJS}
		${CC} ${OBJS} -o ${NAME} ${INC} ${LIBFT} -l readline

clean:
		${RM} ${OBJS}
		@make clean -C libft

fclean:		clean
		${RM} ${NAME}
		@make fclean -C libft

re:		fclean
		make all

.PHONY:		all clean fclean re bonus
