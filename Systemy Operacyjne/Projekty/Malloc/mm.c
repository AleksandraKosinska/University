/*
 * Aleksandra Kosińska 317841
 */

/*
 * mm-naive.c - The fastest, least memory-efficient malloc package.
 *
 * In this naive approach, a block is allocated by simply incrementing
 * the brk pointer.  Blocks are never coalesced or reused.  The size of
 * a block is found at the first aligned word before the block (we need
 * it for realloc).
 *
 * This code is correct and blazingly fast, but very bad usage-wise since
 * it never frees anything.
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <unistd.h>

#include "mm.h"
#include "memlib.h"

/* If you want debugging output, use the following macro.  When you hand
 * in, remove the #define DEBUG line. */
#define DEBUG
#ifdef DEBUG
#define debug(...) printf(__VA_ARGS__)
#else
#define debug(...)
#endif

/* do not change the following! */
#ifdef DRIVER
/* create aliases for driver tests */
#define malloc mm_malloc
#define free mm_free
#define realloc mm_realloc
#define calloc mm_calloc
#endif /* def DRIVER */

//------------------------------------------------------------------------------------

typedef int32_t word_t; // 4 bajty

static word_t *first;           // adres pierwszego bloku
static word_t *last;            // adres ostatniego bloku
static word_t *free_list_first; // adres pierwszego bloku listy wolnych bloków

static word_t max_free_size;

#define USED 1
#define FREE 0
#define BT_SIZE sizeof(word_t)

//-------------------------------------------------------------------------------------

// zaokraglenie podanego rozmiaru do wyrównania, zwraca wartość w bajtach
static size_t round_up(size_t size) {
  return (size + ALIGNMENT - 1) & -ALIGNMENT;
}

// zwraca rozmiar bloku po podaniu bt
static size_t get_size(word_t *bt) {
  return *bt & -2;
}

// sprawdza czy jest alocated
static bool is_alocated(word_t *bt) {
  return *bt & 1;
}

// zwraca aders payloadu po podaniu bt
static word_t *get_payload(word_t *bt) {
  return bt + 1;
}

// zwraca adres nastepnego headera
static word_t *next_header(word_t *header) {
  return header + get_size(header);
}

// zwraca adres poprzedniego headera
static word_t *prev_header(word_t *header) {
  return header - get_size(header - 1);
}

// ustawia header
static void set_header(word_t *header, size_t size, bool is_allocated) {
  *header = size | is_allocated;
}

// ustawia footer po podaniu wskaźnika na header
static void set_footer(word_t *header) {
  word_t *footer = header + get_size(header) - 1;
  *footer = *header;
}

static void set_first() {
  first = (word_t *)(mem_heap_lo()) + 3;
}

// ustawia last jako ostatni blok
static void set_last() {
  word_t *footer = (word_t *)(mem_heap_hi() + 1) - 1;
  last = footer - get_size(footer) + 1;
}

// ustawia 'wskaźnik' następnego wolnego bloku
static void set_next_free(word_t *header, word_t index) {
  word_t *next = header + 1;
  *next = index;
}

// ustawia 'wskaźnik poprzedniego wolnego bloku
static void set_prev_free(word_t *header, word_t index) {
  word_t *prev = header + 2;
  *prev = index;
}

// zwraca index następnego wolnego bloku w tablicy licząc od first
static word_t get_index_next_free(word_t *header) {
  return *(header + 1);
}

// zwraca index poprzedniego wolnego bloku w tablicy licząc od first
static word_t get_index_prev_free(word_t *header) {
  return *(header + 2);
}

// zwraca następny wolny blok w liście wolnych bloków
static word_t *get_next_free(word_t *header) {
  return first + *(header + 1);
}

// zwraca poprzedni wolny blok w liście wolnych bloków
static word_t *get_prev_free(word_t *header) {
  return first + *(header + 2);
}

// dodanie wolnego bloku do listy wolnych bloków
static void add_to_free_list(word_t *header) {
  if (free_list_first == NULL) { // gdy lista wolnych bloków jest pusta
    set_next_free(header,
                  header - first); // ustawia następny wolny blok na siebie
    set_prev_free(header,
                  header - first); // ustawia poprzedni wolny blok na siebie
    free_list_first = header;
    max_free_size = get_size(header);

  } else { // doklejamy nowy pusty blok w kolejności malejącej listy wolnych
           // bloków
    word_t *help_header = free_list_first;
    uint8_t loop = 0;
    while ((loop != 2) && get_size(help_header) > get_size(header)) {
      if (help_header == free_list_first) {
        loop += 1;
      }
      help_header = get_next_free(help_header);
    }
    set_next_free(header, help_header - first);
    set_prev_free(header, get_index_prev_free(help_header));
    set_next_free(get_prev_free(help_header), header - first);
    set_prev_free(help_header, header - first);
    if (help_header == free_list_first) {
      free_list_first = header;
      max_free_size = get_size(header);
    }
  }
}

// usuniecie wolnego bloku z listy wolnych bloków
static void remove_from_free_list(word_t *header) {
  if (header == free_list_first &&
      get_next_free(header) == free_list_first) { // usuwamy ostatni wolny blok
                                                  // na liście wolnych bloków
    free_list_first = NULL;
  } else {
    set_next_free(get_prev_free(header),
                  get_index_next_free(header)); // przepinamy
    set_prev_free(get_next_free(header), get_index_prev_free(header));
    if (header == free_list_first) { // gdy usunelismy pierwszy blok z listy
                                     // wolnych bloków to aktualizujemy zmienna
      free_list_first = get_next_free(header);
    }
  }
}

int mm_init(void) {
  /* Pad heap start so first payload is at ALIGNMENT. */
  if ((long)mem_sbrk(ALIGNMENT - BT_SIZE) < 0)
    return -1;

  first = NULL;
  last = NULL;
  free_list_first = NULL;
  return 0;
}

static void splitting(word_t *header, size_t size) {
  if (get_size(header) > size / 4) {
    remove_from_free_list(header);
    word_t *rest = header + size / 4;
    set_header(rest, get_size(header) - size / 4, FREE);
    set_footer(rest);
    add_to_free_list(rest);
  } else { // gdy rozmiar był równy
    remove_from_free_list(header);
  }
}

// bloki są malejaco, wiec przegladamy liste do tylu
word_t *first_fit(size_t size) {
  bool loop =
    0; // zmienna okreslająca czy zatoczyliśmy pętle w liście wolnych bloków
  word_t *header = get_prev_free(free_list_first);
  while ((!loop) && get_size(header) < (size / 4)) {
    if (header == free_list_first) {
      loop += 1;
    }
    header = get_prev_free(header);
  }
  if (loop == 1) {            // to znaczy, że nie znaleźliśmy
    if (!is_alocated(last)) { // gdy ostatni jest wolny
      remove_from_free_list(last);
      mem_sbrk(size - (get_size(last) *
                       4)); // powiekszamy heap o tyle ile potrzebujemy
      header = last;
    } else {
      header = mem_sbrk(size);
    }
  } else {
    splitting(header, size);
  }
  return header;
}

void *malloc(size_t size) {
  size = round_up(size + 2 * BT_SIZE);
  word_t *header;
  if (free_list_first == NULL ||
      ((max_free_size < size / 4) &&
       is_alocated(
         last))) { // jak lista jest pusta lub nie ma bloku takiej wielkosci
    header = mem_sbrk(size);
  } else {
    header = first_fit(size);
  }
  if (first == NULL) { // aktualizacja zmiennej
    set_first();
  }
  if ((long)header < 0) {
    return NULL;
  }
  set_header(header, size / 4, USED);
  set_footer(header);
  set_last();
  return get_payload(header);
}

static void coalesce(word_t *one, word_t *two) {
  set_header(one, get_size(one) + get_size(two), FREE);
  set_footer(one);
  add_to_free_list(one);
}

void free(void *ptr) {
  if (ptr) {
    bool not_coalesce = 1;
    word_t *header = (word_t *)ptr - 1;
    set_header(header, get_size(header), FREE);
    set_footer(header);
    if (header != last) {
      word_t *next = next_header(header);
      if (!is_alocated(next)) {
        not_coalesce = 0;
        // złaczenie z nastepnym
        remove_from_free_list(next);
        coalesce(header, next);
        set_last();
      }
    }
    if (header != first) {
      word_t *prev = prev_header(header);
      if (!is_alocated(prev)) {
        if (!not_coalesce) {
          remove_from_free_list(header);
        }
        not_coalesce = 0;
        // złączenie z poprzednim
        remove_from_free_list(prev);
        coalesce(prev, header);
        set_last();
      }
    }
    if (not_coalesce) {
      add_to_free_list(header);
    }
  }
}

void *realloc(void *old_ptr, size_t size) {
  /* If size == 0 then this is just free, and we return NULL. */
  if (size == 0) {
    free(old_ptr);
    return NULL;
  }

  /* If old_ptr is NULL, then this is just malloc. */
  if (!old_ptr)
    return malloc(size);

  void *new_ptr = malloc(size);

  /* If malloc() fails, the original block is left untouched. */
  if (!new_ptr)
    return NULL;

  /* Copy the old data. */
  word_t *block = old_ptr + BT_SIZE;
  size_t old_size = get_size(block - 1);
  if (size < old_size)
    old_size = size;
  memcpy(new_ptr, old_ptr, old_size);

  /* Free the old block. */
  free(old_ptr);

  return new_ptr;
}

void *calloc(size_t nmemb, size_t size) {
  size_t bytes = nmemb * size;
  void *new_ptr = malloc(bytes);

  /* If malloc() fails, skip zeroing out the memory. */
  if (new_ptr)
    memset(new_ptr, 0, bytes);

  return new_ptr;
}

void mm_checkheap(int verbose) {
  if (verbose)
    return;

  printf("\033[0;33mHeapsize: %luB, %lu words\033[0;37m\n", mem_heapsize(),
         mem_heapsize() / 4);
  printf("\033[0;36m%d ", *(word_t *)mem_heap_lo());
  printf("\033[0;36m%d ", *(((word_t *)mem_heap_lo()) + 1));
  printf("\033[0;36m%d ", *(((word_t *)mem_heap_lo()) + 2));

  printf("\033[0;32m"); // green
  printf("\033[0;31m"); // red

  size_t b_size = 0;
  for (word_t *block = ((word_t *)mem_heap_lo()) + 3;
       block < (word_t *)(mem_heap_hi() + 1); ++block) {
    if (*block & 1 && b_size == 0) { // is allocated
      printf("\033[0;32m");          // green
      b_size = *block - 1;
    } else if (b_size == 0) {
      printf("\033[0;31m"); // red
      b_size = *block;
    }
    if (block == first) {
      printf("F");
    }
    if (block == last) {
      printf("L");
    }
    // printf("i:%ld,", block - first); //i : index w tablicy
    printf("%d ", *block);
    --b_size;
  }

  printf("\033[0;37m\n");
}
