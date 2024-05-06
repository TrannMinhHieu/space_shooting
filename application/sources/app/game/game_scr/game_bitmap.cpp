#include "game_bitmap.h"


/**
 * Made with Marlin Bitmap Converter
 * https://marlinfw.org/tools/u8glib/converter.html
 *
 * This bitmap from the file 'missile-enemy.png'
 */
// bitmap of space ship 1, 15x15px
const unsigned char PROGMEM bitmap_space_ship_1[] = {
    0x00, 0x00, // ................
    0x10, 0x20, // ...#......#.....
    0x10, 0x60, // ...#.....##.....
    0x08, 0x60, // ....#....##.....
    0x08, 0xE0, // ....#...###.....
    0x01, 0xD0, // .......###.#....
    0xFB, 0x3C, // #####.##..####..
    0x00, 0xFE, // ........#######
    0xFB, 0x3C, // #####.##..####..
    0x01, 0xD0, // .......###.#....
    0x08, 0xE0, // ....#...###.....
    0x08, 0x60, // ....#....##.....
    0x10, 0x60, // ...#.....##.....
    0x10, 0x20, // ...#......#.....
    0x00, 0x00  // ................
};
const unsigned char PROGMEM bitmap_space_ship_2[] = {
    0x00, 0x00, // ................
    0x00, 0x20, // ..........#.....
    0x00, 0x60, // .........##.....
    0x40, 0x60, // .#.......##.....
    0x20, 0xE0, // ..#.....###.....
    0x19, 0xD0, // ...##..###.#....
    0xFB, 0x3C, // #####.##..####..
    0x00, 0xFE, // ........#######.
    0xFB, 0x3C, // #####.##..####..
    0x19, 0xD0, // ...##..###.#....
    0x20, 0xE0, // ..#.....###.....
    0x40, 0x60, // .#.......##.....
    0x00, 0x60, // .........##.....
    0x00, 0x20, // ..........#.....
    0x00, 0x00  // ................
};
const unsigned char PROGMEM bitmap_space_ship_3[] = {
    0x00, 0x00, // ................
    0x00, 0x20, // ..........#.....
    0x00, 0x60, // .........##.....
    0x00, 0x60, // .........##.....
    0x60, 0xE0, // .##.....###.....
    0x19, 0xD0, // ...##..###.#....
    0xFB, 0x3C, // #####.##..####..
    0x00, 0xFE, // ........#######.
    0xFB, 0x3C, // #####.##..####..
    0x19, 0xD0, // ...##..###.#....
    0x60, 0xE0, // .##.....###.....
    0x00, 0x60, // .........##.....
    0x00, 0x60, // .........##.....
    0x00, 0x20, // ..........#.....
    0x00, 0x00  // ................
};
// 'bitmap_meteoroid_I', 20x10px
const unsigned char PROGMEM bitmap_asteroid_1[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x78, 0x00, 0xa8, 0x00, 0x00, 0xfe, 0x3e, 0x00, 0xa8,
    0x00, 0x00, 0xfc, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
// 'bitmap_meteoroid_II', 20x10px
const unsigned char PROGMEM bitmap_asteroid_2[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0xe3, 0xc0, 0xa8, 0x00, 0x00, 0xfd, 0xf1, 0xf0, 0xa8,
    0x00, 0x00, 0xfc, 0xe3, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
// 'bitmap_meteoroid_III', 20x10px
const unsigned char PROGMEM bitmap_asteroid_3[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x80, 0x40, 0xa8, 0x00, 0x00, 0xfb, 0xe0, 0x10, 0xa8,
    0x00, 0x00, 0xff, 0x80, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
// 'bitmap_missile', 10x5px
const unsigned char PROGMEM bitmap_missile[] = {
    0x00, 0x00, // ................
    0xCF, 0x80, // ##..#####.......
    0x70, 0x40, // .###.....#......
    0xCF, 0x80, // ##..#####.......
    0x00, 0x00  // ................
};
// 'bitmap_missile_enemy', 10x5px
const unsigned char PROGMEM bitmap_missile_enemy [] = {
  0x00,0x00, // ................
  0x7C,0xC0, // .#####..##......
  0x83,0x80, // #.....###.......
  0x7C,0xC0, // .#####..##......
  0x00,0x00  // ................
};
// 'bitmap_bang_I', 15x15px
const unsigned char PROGMEM bitmap_explosion_1[] = {
    0x00, 0x00, 0x02, 0x20, 0x02, 0x60, 0x23, 0xe0, 0x1f, 0xe0, 0x1f, 0x7c, 0x0c, 0x30, 0x78, 0x70,
    0x1c, 0x78, 0x0e, 0xfe, 0x1f, 0xe0, 0x13, 0x60, 0x03, 0x20, 0x02, 0x10, 0x00, 0x00};
// 'bitmap_bang_II', 15x15px
const unsigned char PROGMEM bitmap_explosion_2[] = {
    0x00, 0x00, 0x10, 0x80, 0x09, 0x80, 0x0d, 0x90, 0x0f, 0xf0, 0xfe, 0xe0, 0x3c, 0x70, 0x1c, 0x3c,
    0x18, 0x60, 0x7d, 0xf0, 0x0f, 0xf0, 0x0f, 0x88, 0x0c, 0x80, 0x08, 0x80, 0x00, 0x00};
// 'bitmap_bang_III', 10x10px
const unsigned char PROGMEM bitmap_explosion_3[] = {
    0x04, 0x00, 0x24, 0x00, 0x1d, 0x00, 0x1f, 0x00, 0x63, 0x80, 0x23, 0x00, 0x7f, 0x00, 0x1d, 0x80,
    0x14, 0x00, 0x00, 0x00};
/*****************************************************************************/
/* scr_menu_game - Bitmap*/
/*****************************************************************************/
const unsigned char PROGMEM dot_icon[] = {
    0x80, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80,
    0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80,
    0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80,
    0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00};