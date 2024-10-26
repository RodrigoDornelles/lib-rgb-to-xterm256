#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "rgb_to_xterm256.h"

uint32_t xterm256_colors[] = {
    0x000000, 0x800000, 0x008000, 0x808000, 0x000080, 0x800080, 0x008080,
    0xc0c0c0, 0x808080, 0xff0000, 0x00ff00, 0xffff00, 0x0000ff, 0xff00ff,
    0x00ffff, 0xffffff, 0x000000, 0x00005f, 0x000087, 0x0000af, 0x0000d7,
    0x0000ff, 0x005f00, 0x005f5f, 0x005f87, 0x005faf, 0x005fd7, 0x005fff,
    0x008700, 0x00875f, 0x008787, 0x0087af, 0x0087d7, 0x0087ff, 0x00af00,
    0x00af5f, 0x00af87, 0x00afaf, 0x00afd7, 0x00afff, 0x00d700, 0x00d75f,
    0x00d787, 0x00d7af, 0x00d7d7, 0x00d7ff, 0x00ff00, 0x00ff5f, 0x00ff87,
    0x00ffaf, 0x00ffd7, 0x00ffff, 0x5f0000, 0x5f005f, 0x5f0087, 0x5f00af,
    0x5f00d7, 0x5f00ff, 0x5f5f00, 0x5f5f5f, 0x5f5f87, 0x5f5faf, 0x5f5fd7,
    0x5f5fff, 0x5f8700, 0x5f875f, 0x5f8787, 0x5f87af, 0x5f87d7, 0x5f87ff,
    0x5faf00, 0x5faf5f, 0x5faf87, 0x5fafaf, 0x5fafd7, 0x5fafff, 0x5fd700,
    0x5fd75f, 0x5fd787, 0x5fd7af, 0x5fd7d7, 0x5fd7ff, 0x5fff00, 0x5fff5f,
    0x5fff87, 0x5fffaf, 0x5fffd7, 0x5fffff, 0x870000, 0x87005f, 0x870087,
    0x8700af, 0x8700d7, 0x8700ff, 0x875f00, 0x875f5f, 0x875f87, 0x875faf,
    0x875fd7, 0x875fff, 0x878700, 0x87875f, 0x878787, 0x8787af, 0x8787d7,
    0x8787ff, 0x87af00, 0x87af5f, 0x87af87, 0x87afaf, 0x87afd7, 0x87afff,
    0x87d700, 0x87d75f, 0x87d787, 0x87d7af, 0x87d7d7, 0x87d7ff, 0x87ff00,
    0x87ff5f, 0x87ff87, 0x87ffaf, 0x87ffd7, 0x87ffff, 0xaf0000, 0xaf005f,
    0xaf0087, 0xaf00af, 0xaf00d7, 0xaf00ff, 0xaf5f00, 0xaf5f5f, 0xaf5f87,
    0xaf5faf, 0xaf5fd7, 0xaf5fff, 0xaf8700, 0xaf875f, 0xaf8787, 0xaf87af,
    0xaf87d7, 0xaf87ff, 0xafaf00, 0xafaf5f, 0xafaf87, 0xafafaf, 0xafafd7,
    0xafafff, 0xafd700, 0xafd75f, 0xafd787, 0xafd7af, 0xafd7d7, 0xafd7ff,
    0xafff00, 0xafff5f, 0xafff87, 0xafffaf, 0xafffd7, 0xafffff, 0xd70000,
    0xd7005f, 0xd70087, 0xd700af, 0xd700d7, 0xd700ff, 0xd75f00, 0xd75f5f,
    0xd75f87, 0xd75faf, 0xd75fd7, 0xd75fff, 0xd78700, 0xd7875f, 0xd78787,
    0xd787af, 0xd787d7, 0xd787ff, 0xd7af00, 0xd7af5f, 0xd7af87, 0xd7afaf,
    0xd7afd7, 0xd7afff, 0xd7d700, 0xd7d75f, 0xd7d787, 0xd7d7af, 0xd7d7d7,
    0xd7d7ff, 0xd7ff00, 0xd7ff5f, 0xd7ff87, 0xd7ffaf, 0xd7ffd7, 0xd7ffff,
    0xff0000, 0xff005f, 0xff0087, 0xff00af, 0xff00d7, 0xff00ff, 0xff5f00,
    0xff5f5f, 0xff5f87, 0xff5faf, 0xff5fd7, 0xff5fff, 0xff8700, 0xff875f,
    0xff8787, 0xff87af, 0xff87d7, 0xff87ff, 0xffaf00, 0xffaf5f, 0xffaf87,
    0xffafaf, 0xffafd7, 0xffafff, 0xffd700, 0xffd75f, 0xffd787, 0xffd7af,
    0xffd7d7, 0xffd7ff, 0xffff00, 0xffff5f, 0xffff87, 0xffffaf, 0xffffd7,
    0xffffff, 0x080808, 0x121212, 0x1c1c1c, 0x262626, 0x303030, 0x3a3a3a,
    0x444444, 0x4e4e4e, 0x585858, 0x626262, 0x6c6c6c, 0x767676, 0x808080,
    0x8a8a8a, 0x949494, 0x9e9e9e, 0xa8a8a8, 0xb2b2b2, 0xbcbcbc, 0xc6c6c6,
    0xd0d0d0, 0xdadada, 0xe4e4e4, 0xeeeeee
};

uint8_t
bit_8to3(uint8_t input) {
    uint8_t output = 0;
    if (input > 0) {
        output = 1;
        while (input > 0x5f) {
            input -= 0x28;
            output += 1;
        }
    }
    return output;
}

uint8_t
bit_3to8(uint8_t input) {
    static uint8_t incs[] = { 0x00, 0x5f, 0x87, 0xaf, 0xd7, 0xff };

    if (input >= sizeof(incs)) {
        return 0;
    }

    return incs[input];
}

void
split_rgb(uint32_t input,
          uint8_t *output_r,
          uint8_t *output_g,
          uint8_t *output_b) {
    *output_r = (input >> 16) & 0xFF;
    *output_g = (input >> 8) & 0xFF;
    *output_b = input & 0xFF;
}

uint32_t
join_rgb(uint8_t input_r, uint8_t input_g, uint8_t input_b) {
    return ((uint32_t)input_r << 16) | ((uint32_t)input_g << 8) |
           (uint32_t)input_b;
}

int
command_rgb2xterm_lib(int argc, char *argv[]) {
    int len = 0;
    uint32_t color = 0;
    uint8_t r, g, b;
    while (scanf("%x%n\n", &color, &len) == 1) {
        if (len != 6) {
            break;
        }
        split_rgb(color, &r, &g, &b);
        printf("%d\n", rgb_to_xterm256(r, g, b));
    }
    return 0;
}

int
command_rgb2xterm_true(int argc, char *argv[]) {
    int len = 0;
    uint32_t color = 0;
    while (scanf("%x%n\n", &color, &len) == 1) {
        if (len != 6) {
            break;
        }
        uint16_t i = 0;
        uint8_t id = 0;
        while (i < sizeof(xterm256_colors) / sizeof(*xterm256_colors)) {
            if (xterm256_colors[i] == color) {
                id = i;
                break;
            }
            i++;
        }
        printf("%d\n", id);
    }
    return 0;
}

int
command_xterm2rgb(int argc, char *argv[]) {
    int i = 0;
    while (scanf("%d\n", &i) == 1) {
        if (i < 0 || i > (sizeof(xterm256_colors) / sizeof(*xterm256_colors))) {
            break;
        }
        printf("%06x\n", xterm256_colors[i]);
    }
    return 0;
}

int
command_10to16(int argc, char *argv[]) {
    int i = 0;
    while (scanf("%d\n", &i) == 1) {
        printf("%02x\n", i);
    }
    return 0;
}

int
command_ladygaga(int argc, char *argv[]) {
    uint32_t i = 0;
    uint8_t r, g, b;

    while (i < 0x1b7) {
        b = i & 0x7;
        g = (i >> 3) & 0x7;
        r = (i >> 6) & 0x7;
        r = r ^ 7 ? r : 0;
        g = g ^ 7 ? g : 0;
        b = b ^ 7 ? b : 0;
        printf("%06x\n", join_rgb(r, g, b));
        i++;
    }

    return 0;
}

int
command_beyonce(int argc, char *argv[]) {
    return 0;
}

int
command_loop_rgb(int argc, char *argv[]) {
    uint16_t i = 0;
    while (i < sizeof(xterm256_colors) / sizeof(*xterm256_colors)) {
        printf("%06x\n", xterm256_colors[i++]);
    }
    return 0;
}

int
command_loop_256(int argc, char *argv[]) {
    uint16_t i = 0;
    while (i < sizeof(xterm256_colors) / sizeof(*xterm256_colors)) {
        printf("%d\n", i++);
    }
    return 0;
}

int
command_b8to3(int argc, char *argv[]) {
    int len = 0;
    uint32_t color = 0;
    uint8_t r, g, b;
    while (scanf("%x%n\n", &color, &len) == 1) {
        if (len != 6) {
            break;
        }
        split_rgb(color, &r, &g, &b);
        printf("%06x\n", join_rgb(bit_8to3(r), bit_8to3(g), bit_8to3(b)));
    }
    return 0;
}

int
command_b3to8(int argc, char *argv[]) {
    int len = 0;
    uint32_t color = 0;
    uint8_t r, g, b;
    while (scanf("%x%n\n", &color, &len) == 1) {
        if (len != 6) {
            break;
        }
        split_rgb(color, &r, &g, &b);
        printf("%06x\n", join_rgb(bit_3to8(r), bit_3to8(g), bit_3to8(b)));
    }
    return 0;
}

const struct {
    const char *str;
    int (*func)(int, char *[]);
} command_list[] = {
    { "rgb", command_loop_rgb }, // clang-format off
    { "823", command_b8to3 },
    { "328", command_b3to8 },
    { "10216", command_10to16 },
    { "xterm", command_loop_256 },
    { "xterm2rgb", command_xterm2rgb },
    { "rgb2xterm", command_rgb2xterm_lib },
    { "rgb2xterm2", command_rgb2xterm_true },
    { "ladygaga", command_ladygaga },
    { "beyonce", command_beyonce } // clang-format on
};

int
main(int argc, char *argv[]) {
    uint8_t i = 0;
    if (argc < 2) {
        fprintf(stderr, "command list:");
        while (i < sizeof(command_list) / sizeof(*command_list)) {
            fprintf(stderr, " %s", command_list[i++].str);
        }
        fprintf(stderr, "\n");
        return 1;
    }

    while (i < sizeof(command_list) / sizeof(*command_list)) {
        if (strcmp(argv[1], command_list[i].str) == 0) {
            return command_list[i].func(argc, argv);
        }
        i++;
    }

    fprintf(stderr, "command not found: %s\n", argv[1]);
    return 1;
}