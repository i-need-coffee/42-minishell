cmake_minimum_required(VERSION 4.2)
project(minishell C)

set(CMAKE_C_STANDARD 11)

SET(LIBS ft readline)

#ftif (APPLE)
#    FIND_LIBRARY(OPENGL_LIBRARY OpenGL)
#    FIND_LIBRARY(APPKIT_LIBRARY AppKit)
#    SET(LIBS ${LIBS} ${OPENGL_LIBRARY} ${APPKIT_LIBRARY})
#else ()
#    SET(LIBS ${LIBS} Xext X11 m)
#endif ()

link_directories(libft /usr/local/Cellar/readline/8.3.3/lib)

include_directories(include libft/include /usr/local/Cellar/readline/8.3.3/include)

add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)


add_executable(minishell
	src/debug.c
	src/main.c
	src/utils/misc.c
	src/utils/cleanup.c
	src/utils/errors.c
	src/tokenization/tokenize_input.c
	src/tokenization/utils.c
	src/tokenization/add_word_token.c
	src/signals/signal_config.c
	src/env/environement.c
	src/env/utils_node.c
	src/parsing/parsing.c
	src/parsing/parsing_utils.c
	src/parsing/handle_literal.c
	src/parsing/parsing_word_token.c
	src/parsing/expension.c
	src/parsing/handle_quote.c
	src/parsing/parse_pipe_token.c
	src/parsing/parse_redirection_token.c
	src/parsing/wrapper.c
	src/parsing/redirection_utils/common_redirection_utils.c
	src/execution/execute_input.c
	src/execution/heredoc.c
	src/execution/utils.c
	src/execution/pipes.c
	src/execution/children.c
	src/execution/files.c
	src/execution/exec.c
	src/execution/dup.c
	src/built-in/execute_built_in.c
	src/built-in/echo.c
	src/built-in/pwd.c
	src/built-in/cd.c
	src/built-in/utils.c
	src/built-in/env.c
	src/built-in/unset.c
	src/built-in/export.c
	src/built-in/export_one_arg.c
	src/built-in/exit_minishell.c)

TARGET_LINK_LIBRARIES(minishell ${LIBS})
