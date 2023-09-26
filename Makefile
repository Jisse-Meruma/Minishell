### VAR #######################################################
NAME		:=	minishell

DEBUGGING	?=


LIBS		:=	./libft/libft.a -lreadline -I /Users/$(USER)/.homebrew/opt/readline/include -L/Users/$(USER)/.homebrew/opt/readline/lib -I /opt/homebrew/opt/readline/include -L/opt/homebrew/opt/readline/lib

HEADER		:=	-I libft -I includes -I /Users/$(USER)/.homebrew/opt/readline/include -I /opt/homebrew/opt/readline/include

HEADERS		:=	libft/libft.h includes/minishell.h includes/struct.h
OBJ_DIR		:=	./obj
SRC_DIR 	:=	./src

### UTILS #####################################################
CFLAGS	:=	-Wall -Wextra -Werror
RM		:=	rm -rf

SRC 	:=	main.c			\
			init.c			\
			shlvl.c			\
			path_creation.c \
			builtins/cmd_pwd.c 	\
			builtins/cmd_env.c 	\
			parser/parser.c			\
			parser/remove_quotes.c	\
			parser/parse_command.c	\
			parser/parse_redirect.c	\
			builtins/arg_error_blt.c\
			builtins/cmd_cd.c 		\
			builtins/cmd_unset.c	\
			builtins/cmd_export.c	\
			builtins/cmd_export_d.c	\
			builtins/cmd_get_env.c 	\
			builtins/cmd_exit.c 	\
			builtins/cmd_echo.c		\
			parser/list_env.c 		\
			signal/signal.c 		\
			parser/lexer/lexer.c	\
			parser/lexer/list_lexer.c	\
			parser/lexer/ft_islexer.c	\
			parser/lexer/tokenizer.c	\
			parser/lexer/lexer_cleanup.c\
			parser/expander/expander.c 	\
			parser/expander/exp_utils.c	\
			cleanup/free_cmd_struct.c	\
			redirects/here_doc.c		\
			redirects/open.c			\
			redirects/here_doc_utils.c	\
			execution/execution.c 		\
			execution/execution_cmd.c	\
			execution/get_envp.c		\
			execution/fds.c				\
			execution/fill_blt.c		\
			execution/built_exec.c		\
			utils/ret_error.c			\
			utils/compare.c				\
			utils/ft_isnumber.c			\
			utils/ft_2d_print.c			\
			utils/ft_our_lst_size.c		\
			utils/free_struc.c			\
			utils/ft_split_first.c		\
			utils/is_invalid_id.c		\

OBJ		:=	$(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))
SRC		:=	$(addprefix $(SRC_DIR)/,$(SRC))

## Regular Colors ##############################################
Color_Off	=	"\033[0m"			# Text Reset
Black		=	"\033[0;30m"		# Black
Red			=	"\033[0;31m"		# Red
Green		=	"\033[0;32m"		# Green
Yellow		=	"\033[0;33m"		# Yellow
Blue		=	"\033[0;34m"		# Blue
Purple		=	"\033[0;35m"		# Purple
Cyan		=	"\033[0;36m"		# Cyan
White		=	"\033[0;37m"		# White

### EXEC #######################################################

ifdef DEBUG
	DEBUGGING += -g
endif

all: $(NAME)

$(NAME): $(OBJ)
	@echo $(Yellow) Building.. 🏠$(Color_Off)
	@echo -----------------------
	@$(MAKE) -C libft bonus
	@$(CC) $^ $(LIBS) $(DEBUGGING) -o $(NAME)
	@echo $(Green) Complete ✅ $(Color_Off)
	@echo -----------------------

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) | $(OBJ_DIR)
	@mkdir -p $(@D)
	@echo $(Purple) Compiling.. 🧱 $< $(Color_Off)
	@echo -----------------------
	@$(CC) $(CFLAGS) $(HEADER) -c $< -o $@

$(OBJ_DIR):
	@mkdir $@

clean:
	@echo $(Cyan) Sweeping.. 💥 $(Color_Off)
	@echo -----------------------
	@$(MAKE) -C libft clean
	@rm -rf $(OBJ_DIR)
	@$(RM) $(OBJ) $(BON_OBJ)

fclean:
	@echo $(Red) Thorough sweeping.. 💥 $(Color_Off)
	@echo -----------------------
	@$(MAKE) -C libft fclean
	@rm -rf $(OBJ_DIR)
	@$(RM) $(NAME) $(OBJ) $(BON_OBJ)

re: fclean all

mem:
	memdetect $(SRC) $(LIBS) $(HEADER) -fail loop 290 -fl -fsanitize=address

.PHONY: clean all fclean re libmlx
