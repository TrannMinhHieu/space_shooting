#include "game_bitmap.h"

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
/* scr_charts_game - Bitmap*/
/*****************************************************************************/
// 'bitmap_icon_charts', 60x20px
const unsigned char PROGMEM bitmap_icon_high_score[] = {
    0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x39, 0xc0, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x30, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x80, 0x00, 0x00, 0x00,
    0x7e, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x07, 0xe0, 0xe7, 0x00, 0x00, 0x1f, 0x80, 0x00, 0x0e, 0x70,
    0xe7, 0x00, 0x00, 0x39, 0xc0, 0x00, 0x0e, 0x70, 0x7f, 0x00, 0x60, 0x70, 0xe0, 0x60, 0x0f, 0xe0,
    0x03, 0xc0, 0xfe, 0xe0, 0x77, 0xf0, 0x3c, 0x00, 0x01, 0xf9, 0xc7, 0x80, 0x1e, 0x39, 0xf8, 0x00,
    0x00, 0xff, 0x87, 0x00, 0x0e, 0x1f, 0x70, 0x00, 0x00, 0x73, 0xce, 0x00, 0x07, 0x7c, 0xe0, 0x00,
    0x00, 0x38, 0x7c, 0x00, 0x03, 0xe1, 0xc0, 0x00, 0x00, 0x1c, 0x18, 0x00, 0x00, 0x03, 0x80, 0x00,
    0x00, 0x0e, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00,
    0x00, 0x03, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00};

/*****************************************************************************/
/* scr_game_over - Bitmap*/
/*****************************************************************************/
// 'icon_restart', 15x15px
const unsigned char PROGMEM icon_restart[] = {
    0x01, 0x00, 0x07, 0x00, 0x0f, 0xc0, 0x0f, 0xf0, 0x07, 0x78, 0x63, 0x9c, 0x61, 0x0c, 0x60, 0x0c,
    0x60, 0x0c, 0x60, 0x0c, 0x60, 0x0c, 0x70, 0x1c, 0x38, 0x38, 0x1f, 0xf0, 0x07, 0xc0};
// 'icon_rank', 17x15px
const unsigned char PROGMEM icon_rank[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x08, 0x00, 0x00, 0x28, 0x00, 0x00,
    0xa8, 0x00, 0x00, 0xa8, 0x00, 0x02, 0xa8, 0x00, 0x02, 0xa8, 0x00, 0x0a, 0xa8, 0x00, 0x0a, 0xa8,
    0x00, 0x00, 0x00, 0x00, 0x1f, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
// 'icon_go_home', 16x16px
const unsigned char PROGMEM icon_go_home[] = {
    0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x02, 0x40, 0x05, 0xa0, 0x0b, 0xd0, 0x17, 0xe8, 0x2f, 0xf4,
    0x5f, 0xfb, 0xbc, 0x3d, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x1c, 0x38, 0x00, 0x00};

/*****************************************************************************/
/* scr_game_setting - Bitmap*/
/*****************************************************************************/
// 'chosse_icon', 20x20px
const unsigned char PROGMEM chosse_icon[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xf8, 0x00, 0xff, 0xfc, 0x00, 0x7f,
    0xfe, 0x00, 0x3f, 0xff, 0x00, 0x1f, 0xff, 0x80, 0x0f, 0xff, 0xc0, 0x07, 0xff, 0xe0, 0x04, 0x00,
    0x20, 0x08, 0x00, 0x40, 0x10, 0x00, 0x80, 0x20, 0x01, 0x00, 0x40, 0x02, 0x00, 0x80, 0x04, 0x00,
    0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
// 'speaker_1', 7x7px
const unsigned char PROGMEM speaker_1[] = {
    0x20, 0x62, 0xea, 0xea, 0xea, 0x62, 0x20};
// 'speaker_2', 7x7px
const unsigned char PROGMEM speaker_2[] = {
    0x20, 0x60, 0xea, 0xe4, 0xea, 0x60, 0x20};