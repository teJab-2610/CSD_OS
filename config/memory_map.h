/**
 * Memory Map Layout:
 * | OS | stack | heap | display io map| ........| Font Map | keyboard buffer | temp |
 * 
 * Total: 200KB
 * 
 * OS : 100KB
 * stack: 10KB 
 * heap: 40KB
 * Display io map: 29KB
 * keyboard buffer: 32B
 * fontmap: 2KB
 * temp: 5KB
*/

//TODO: To include a common keyboard file for all processes to read from.
//TODO: To incldue location for PCBs based on the size available.

#define MEMORY_SIZE 1024 * 200
#define OS_SIZE 1024 * 100
#define OS_START 0
#define OS_END OS_START + OS_SIZE
#define STACK_SIZE 1024 * 10
#define STACK_START OS_END
#define STACK_END STACK_START + STACK_SIZE
#define HEAP_SIZE 1024 * 40
#define HEAP_START STACK_END
#define HEAP_END HEAP_START + HEAP_SIZE

#define IO_DISPLAY_SIZE 1024 * 29
#define IO_DISPLAY_START HEAP_END
#define IO_DISPLAY_END IO_DISPLAY_START + IO_DISPLAY_SIZE

#define TEMP_SIZE 1024 * 5
#define TEMP_START MEMORY_SIZE - TEMP_SIZE

#define FONTMAP_SIZE 1024 * 2
#define FONTMAP_END TEMP_START
#define FONTMAP_START FONTMAP_END - FONTMAP_SIZE

#define KEYBOARD_BUFFER_SIZE 32
#define KEYBOARD_BUFFER_END FONTMAP_START
#define KEYBOARD_BUFFER_START KEYBOARD_BUFFER_END - KEYBOARD_BUFFER_SIZE
