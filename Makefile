
# -------------------- config -------------------------

NAME := libasm.a

OS := $(shell uname -s)

# assembler config
AS = nasm
ASFLAGS = -wall -iinc -g

ifeq ($(OS), Darwin) # MacOS
ASFLAGS += -f macho64 -dMACOS=1
else ifeq ($(OS), Linux) # Linux
ASFLAGS += -f elf64 -F dwarf -dLINUX=1
else
$(error Unsupported operating system: $(OS))
endif


# linker config
LD = ld
# -m elf_i386 = architecture
LDFLAGS = 

# archive (library) config
AR = ar
ARFLAGS = rcs

# compiler config
CC = cc
CFLAGS = -Wall -Wextra -Wpedantic -Wconversion -g3 #-Werror

# utils config
RM = rm -rf
MKDIR = mkdir -p

# -------------------- dependencies ---------------------

SRC_BONUS = ft_atoi_base.asm \
            ft_list_push_front.asm \
            ft_list_remove_if.asm \
            ft_list_size.asm \
            ft_list_sort.asm
SDIR_BONUS = bonus

SRC = ft_write.asm \
      ft_read.asm \
      ft_strcmp.asm \
      ft_strcpy.asm \
      ft_strdup.asm \
      ft_strlen.asm \
      $(addprefix $(SDIR_BONUS)/, $(SRC_BONUS))
SDIR = src
SRC_FULL = $(addprefix $(SDIR)/, $(SRC))


IDIR = inc

ODIR = build
OBJ = $(patsubst $(SDIR)/%.asm, $(ODIR)/%.o, $(SRC_FULL))

TEST_DIR = test
# TEST_SRC = $(wildcard $(TEST_DIR)/*.c)
TEST_SRC = $(shell find $(TEST_DIR) -type f -name "*.c")
TESTER_NAME := tester

# -------------------- public rules ---------------------

$(NAME): $(ODIR) $(OBJ)
	$(AR) $(ARFLAGS) $@ $(OBJ)


all: $(NAME)

clean:
	$(RM) $(ODIR)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(TESTER_NAME)

re: fclean all

bonus: all

# test: CFLAGS += -DLIBASM_BONUS=1
test: all
	$(CC) $(CFLAGS) -I$(IDIR) $(TEST_SRC) $(OBJ) -o $(TESTER_NAME)
#	$(shell bash $(TEST_DIR)/run.sh)


.PHONY: $(NAME) all clean fclean re bonus

# -------------------- util rules -----------------------

# copy the directory tree from $(SDIR) to $(ODIR)
$(ODIR):
	$(MKDIR) $(patsubst $(SDIR)/%, $(ODIR)/% , $(shell find $(SDIR)/ -type d))

$(ODIR)/%.o: $(SDIR)/%.asm
	$(AS) $(ASFLAGS) $< -o $@ -I $(IDIR)