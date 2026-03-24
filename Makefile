# TODO: will automate the compiler at some point too
CC = gcc
# needed compiler flags. will change this so that it works with clang too.
CFLAGS = -Wall -Wextra -I./include/ -I./builtins/ -I./src/
# required libraries
LIBS = -lreadline
# automatation of source files
SRCS_DIR = src builtins
SRCS = $(wildcard $(addsuffix /*.c, $(SRCS_DIR)))
# automation of object files
OBJDIR = obj
OBJS = $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.c=.o)))
# automation of dependencies
DEPS = $(OBJS:.o=.d)
vpath %.c src builtins
TARGET = ./jayshell

BLACK   := \033[30m
RED     := \033[31m
GREEN   := \033[32m
YELLOW  := \033[33m
BLUE    := \033[34m
MAGENTA := \033[35m
CYAN    := \033[36m
WHITE   := \033[37m
BOLD    := \033[1m
RESET   := \033[0m

run: run-release

run-debug: debug
	$(TARGET)
debug: CFLAGS += -g
debug: jayshell

run-release: release
	$(TARGET)
release: CFLAGS += -O3
release: jayshell


check:
	@echo -e "$(BLUE)$(BOLD)=== Syntax Check via GCC ===$(RESET)"
	$(CC) -fsyntax-only $(CFLAGS) $(SRCS)
	@echo -e "$(BLUE)$(BOLD)=== Clang-Tidy ===$(RESET)"
	@if command -v clang-tidy > /dev/null; then \
		clang-tidy $(CLANG_TIDY_FLAGS) $(SRCS) -- $(CFLAGS) \
			&& echo -e "$(GREEN)$(BOLD)[PASS] Check cleared.$(RESET)"; \
	else \
		echo -e "$(RED)$(BOLD)[ERROR] clang-tidy not found.$(RESET)"; \
	fi

expand:
	@echo 'Expanding macros to .i files ...'
	@rm -rf debug_preproc
	@mkdir -p debug_preproc
	@$(foreach FILE, $(SRCS), \
		$(CC) -E -P $(CFLAGS) $(FILE) -o debug_preproc/$(notdir $(FILE:.c=.i));)
	@echo 'Expansion complete . Check debug_preproc/ .'

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -f jayshell jayshell.hex
	rm -rf $(OBJDIR)
	rm -rf debug_preproc/

help:
	@echo ''
	@echo 'Usage:'
	@echo '  $(GREEN)make run$(RESET)            Alias for run-release'
	@echo '  $(GREEN)make run-release$(RESET)    Build jayshell for release and run it'
	@echo '  $(GREEN)make run-debug$(RESET)      Build jayshell for debug and run it'
	@echo '  $(GREEN)make release$(RESET)        Build jayshell for release'
	@echo '  $(GREEN)make debug$(RESET)          Build jayshell with debugging information'
	@echo '  $(GREEN)make check$(RESET)          Check for syntax errors'
	@echo '  $(GREEN)make expand$(RESET)         Only expansion, no compilation'
	@echo '  $(GREEN)make clean$(RESET)          Clean object/intermediary/executable files'
	@echo '  $(GREEN)make help$(RESET)           Print this message'
	@echo ''

# jayshell: CFLAGS += -MMD
jayshell: $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

# compile every source file with its dependencies
obj/%.o : %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# cli options
.PHONY: release debug check expand clean help run run-release run-debug

-include $(DEPS)
