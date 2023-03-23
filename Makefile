### VAR #######################################################
NAME		:=	minishell

DEBUGGING	?=

LIBS		:=	./libft/libft.a -lreadline

HEADER		:=	-I libft -I includes 
HEADERS		:=	libft/libft.h includes/minishell.h includes/struct.h
OBJ_DIR		:=	./obj
PARSE_DIR	:=	./src/parser
SRC_DIR 	:=	./src

### UTILS #####################################################
CFLAGS	:=	-Wall -Wextra 
RM		:=	rm -rf

SRC 	:=	main.c \
			path_creation.c \
			execution.c \
			ifcmd.c \
			cmd_pwd.c \
			cmd_env.c \
			compare.c
			execution.c	\
			parser/dubble_quotes.c

OBJ		:=	$(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))
SRC		:=	$(addprefix $(SRC_DIR)/,$(SRC))
## BON_SRC :=

## BON_OBJ :=  $(BON_SRC:_bonus.c=_bonus.o)

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
	DEBUGGING += -fsanitize=address -g
endif

all: $(NAME)

$(NAME): $(OBJ)
	@echo $(Yellow) Building.. 🏠$(Color_Off)
	@echo -----------------------
	@$(MAKE) -C libft
	@$(CC) $^ $(LIBS) $(DEBUGGING) -o $(NAME) 
	@echo $(Green) Complete ✅ $(Color_Off)
	@echo -----------------------

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) | $(OBJ_DIR)
	@mkdir -p $(@D)
	@echo $(Purple) Compiling.. 🧱 $< $(Color_Off)
	@echo -----------------------
	@$(CC) $(CFLAGS) $(HEADER) -c $< -o $@ 

clean:
	@echo $(Cyan) Sweeping.. 💥 $(Color_Off)
	@echo -----------------------
	@$(MAKE) -C libft clean
	@$(RM) $(OBJ) $(BON_OBJ)

fclean:
	@echo $(Red) Thorough sweeping.. 💥 $(Color_Off)
	@echo -----------------------
	@$(MAKE) -C libft fclean
	@$(RM) $(NAME) $(OBJ) $(BON_OBJ)

re: fclean all

.PHONY: clean all fclean re libmlx,