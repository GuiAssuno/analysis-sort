CC = gcc
# -fPIC é obrigatório para criar bibliotecas compartilhadas (.so)
CFLAGS = -Wall -O2 -fPIC
# Nome do arquivo final deve ser .so
TARGET = libsorting.so

SOURCES = bogo_sort.c bubble_sort.c bucket_sort.c comb_sort.c counting_sort.c gnome_sort.c heap_sort.c insertion_sort.c \
          intro_sort.c merge_sort.c quick_sort.c radix_sort.c selection_sort.c shell_sort.c tim_sort.c

OBJECTS = $(SOURCES:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	# -shared: Cria a biblioteca dinâmica ao invés de executável
	# -lm: Linka a biblioteca matemática (necessária para log2 no intro_sort)
	$(CC) -shared -o $(TARGET) $(OBJECTS) -lm

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean

