
# Names + files
NAME		= cub3D
FILES		= cubddd.c
F_CHECKS	= input_checks.c file_checks.c map_checks.c
FILES		+= $(addprefix checks/, $(F_CHECKS))
F_UTILS		= utils.c error.c split.c
FILES		+= $(addprefix utils/, $(F_UTILS))
F_GNL		= get_next_line.c get_next_line_utils.c
FILES		+= $(addprefix gnl/, $(F_GNL))

# Colors
_END		= \033[0m
_COMP		= \033[1;33m
_BUILD		= \033[1;32m
_REMOVE		= \033[1;31m
_LIB		= \033[1;30m
_FINISH		= \033[1;3;96m

# Messages
COMP		= Compiling
BUILD		= Building
REMOVE		= Removing
LIBX		= Building lib
FINISH		= \n\n\
			. . . . . . . . . . . . . . . . . . . . . . .\n\
			.         ______      __   _____ ____       .\n\
			.        / ____/_  __/ /_ |__  // __ \      .\n\
			.       / /   / / / / __ \ /_ </ / / /      .\n\
			.      / /___/ /_/ / /_/ /__/ / /_/ /       .\n\
			.      \____/\__,_/_.___/____/_____/        .\n\
			. . . . . . . . . . . . . . . . . . . . . . .\n\n\n\
MSG_COMP	= ${_COMP}${COMP}:	${_END}
MSG_BUILD	= ${_BUILD}${BUILD}:	${_END}
MSG_RMV		= ${_REMOVE}${REMOVE}:	${_END}
MSG_LIB		= ${_LIB}${LIBX}:	${_END}
MSG_FINISH	= ${_FINISH}${FINISH}${_END}

# Paths
SRCS_PATH	= srcs/
INCS_PATH	= usr/include headers/ mlx_linux
OBJS_PATH	= objs/

# Objects
OBJS	= $(addprefix $(OBJS_PATH), $(FILES:.c=.o))

# Flags + compilation
FLAGS	= -Wall -Wextra -Werror
CC		= cc
INC		= $(addprefix -I, $(INCS_PATH))
LIB_INC	= -Lmlx_linux -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz

# Create obj and dir
$(OBJS_PATH)%.o: $(SRCS_PATH)%.c
			@mkdir -p $(dir $@)
			@$(CC) $(FLAGS) $(INC) -O3 -c $< -o $@ 
			@echo "${MSG_COMP}$<"

# Compiling command
all:		${NAME}

${NAME}:	${OBJS}
			@$(CC) $(FLAGS) $(OBJS) $(LIB_INC) $(INC) -o $(NAME) 
			@echo "${MSG_BUILD}${NAME}${MSG_FINISH}"

clean:
			@rm -rf ${OBJS_PATH}
			@echo "${MSG_RMV}${OBJS_PATH}*"

fclean:		clean
		@rm -rf ${NAME}
			@echo "${MSG_RMV}${NAME}"

re:			fclean all

.PHONY:        all clean fclean re
