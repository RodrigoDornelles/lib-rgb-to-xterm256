#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "rgb_to_xterm256.h"

const uint32_t xterm256_colors[] = {
    0x000000, 0x800000, 0x008000, 0x808000, 0x000080, 0x800080, 0x008080, 0xc0c0c0, 0x808080, 0xff0000, 0x00ff00, 0xffff00, 0x0000ff, 0xff00ff,
    0x00ffff, 0xffffff, 0x000000, 0x00005f, 0x000087, 0x0000af, 0x0000d7, 0x0000ff, 0x005f00, 0x005f5f, 0x005f87, 0x005faf, 0x005fd7, 0x005fff,
    0x008700, 0x00875f, 0x008787, 0x0087af, 0x0087d7, 0x0087ff, 0x00af00, 0x00af5f, 0x00af87, 0x00afaf, 0x00afd7, 0x00afff, 0x00d700, 0x00d75f,
    0x00d787, 0x00d7af, 0x00d7d7, 0x00d7ff, 0x00ff00, 0x00ff5f, 0x00ff87, 0x00ffaf, 0x00ffd7, 0x00ffff, 0x5f0000, 0x5f005f, 0x5f0087, 0x5f00af,
    0x5f00d7, 0x5f00ff, 0x5f5f00, 0x5f5f5f, 0x5f5f87, 0x5f5faf, 0x5f5fd7, 0x5f5fff, 0x5f8700, 0x5f875f, 0x5f8787, 0x5f87af, 0x5f87d7, 0x5f87ff,
    0x5faf00, 0x5faf5f, 0x5faf87, 0x5fafaf, 0x5fafd7, 0x5fafff, 0x5fd700, 0x5fd75f, 0x5fd787, 0x5fd7af, 0x5fd7d7, 0x5fd7ff, 0x5fff00, 0x5fff5f,
    0x5fff87, 0x5fffaf, 0x5fffd7, 0x5fffff, 0x870000, 0x87005f, 0x870087, 0x8700af, 0x8700d7, 0x8700ff, 0x875f00, 0x875f5f, 0x875f87, 0x875faf,
    0x875fd7, 0x875fff, 0x878700, 0x87875f, 0x878787, 0x8787af, 0x8787d7, 0x8787ff, 0x87af00, 0x87af5f, 0x87af87, 0x87afaf, 0x87afd7, 0x87afff,
    0x87d700, 0x87d75f, 0x87d787, 0x87d7af, 0x87d7d7, 0x87d7ff, 0x87ff00, 0x87ff5f, 0x87ff87, 0x87ffaf, 0x87ffd7, 0x87ffff, 0xaf0000, 0xaf005f,
    0xaf0087, 0xaf00af, 0xaf00d7, 0xaf00ff, 0xaf5f00, 0xaf5f5f, 0xaf5f87, 0xaf5faf, 0xaf5fd7, 0xaf5fff, 0xaf8700, 0xaf875f, 0xaf8787, 0xaf87af,
    0xaf87d7, 0xaf87ff, 0xafaf00, 0xafaf5f, 0xafaf87, 0xafafaf, 0xafafd7, 0xafafff, 0xafd700, 0xafd75f, 0xafd787, 0xafd7af, 0xafd7d7, 0xafd7ff,
    0xafff00, 0xafff5f, 0xafff87, 0xafffaf, 0xafffd7, 0xafffff, 0xd70000, 0xd7005f, 0xd70087, 0xd700af, 0xd700d7, 0xd700ff, 0xd75f00, 0xd75f5f,
    0xd75f87, 0xd75faf, 0xd75fd7, 0xd75fff, 0xd78700, 0xd7875f, 0xd78787, 0xd787af, 0xd787d7, 0xd787ff, 0xd7af00, 0xd7af5f, 0xd7af87, 0xd7afaf,
    0xd7afd7, 0xd7afff, 0xd7d700, 0xd7d75f, 0xd7d787, 0xd7d7af, 0xd7d7d7, 0xd7d7ff, 0xd7ff00, 0xd7ff5f, 0xd7ff87, 0xd7ffaf, 0xd7ffd7, 0xd7ffff,
    0xff0000, 0xff005f, 0xff0087, 0xff00af, 0xff00d7, 0xff00ff, 0xff5f00, 0xff5f5f, 0xff5f87, 0xff5faf, 0xff5fd7, 0xff5fff, 0xff8700, 0xff875f,
    0xff8787, 0xff87af, 0xff87d7, 0xff87ff, 0xffaf00, 0xffaf5f, 0xffaf87, 0xffafaf, 0xffafd7, 0xffafff, 0xffd700, 0xffd75f, 0xffd787, 0xffd7af,
    0xffd7d7, 0xffd7ff, 0xffff00, 0xffff5f, 0xffff87, 0xffffaf, 0xffffd7, 0xffffff, 0x080808, 0x121212, 0x1c1c1c, 0x262626, 0x303030, 0x3a3a3a,
    0x444444, 0x4e4e4e, 0x585858, 0x626262, 0x6c6c6c, 0x767676, 0x808080, 0x8a8a8a, 0x949494, 0x9e9e9e, 0xa8a8a8, 0xb2b2b2, 0xbcbcbc, 0xc6c6c6,
    0xd0d0d0, 0xdadada, 0xe4e4e4, 0xeeeeee
};

const uint8_t legacy_xterm256_colors_3bits[] = {
    0x00, 0x11, 0x12, 0x13, 0x14, 0x0c, 0x00, 0x00, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x16, 0x16, 0x1c, 0x1d, 0x1e, 0x1f, 0x20, 0x21, 0x1c, 0x1c,
    0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x22, 0x22, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x28, 0x28, 0x0a, 0x2f, 0x30, 0x31, 0x32, 0x0e, 0x0a, 0x0a,
    0x00, 0x11, 0x12, 0x13, 0x14, 0x0c, 0x00, 0x00, 0x00, 0x11, 0x12, 0x13, 0x14, 0x0c, 0x00, 0x00, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x34, 0x34,
    0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f, 0x3a, 0x3a, 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x40, 0x40, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x46, 0x46,
    0x4c, 0x4d, 0x4e, 0x4f, 0x50, 0x51, 0x4c, 0x4c, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x52, 0x52, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x34, 0x34,
    0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x34, 0x34, 0x58, 0x59, 0x5a, 0x5b, 0x5c, 0x5d, 0x58, 0x58, 0x5e, 0x5f, 0x60, 0x61, 0x62, 0x63, 0x5e, 0x5e,
    0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x64, 0x64, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f, 0x6a, 0x6a, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x70, 0x70,
    0x76, 0x77, 0x78, 0x79, 0x7a, 0x7b, 0x76, 0x76, 0x58, 0x59, 0x5a, 0x5b, 0x5c, 0x5d, 0x58, 0x58, 0x58, 0x59, 0x5a, 0x5b, 0x5c, 0x5d, 0x58, 0x58,
    0x7c, 0x7d, 0x7e, 0x7f, 0x80, 0x81, 0x7c, 0x7c, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x82, 0x82, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x88, 0x88,
    0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x8e, 0x8e, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x94, 0x94, 0x9a, 0x9b, 0x9c, 0x9d, 0x9e, 0x9f, 0x9a, 0x9a,
    0x7c, 0x7d, 0x7e, 0x7f, 0x80, 0x81, 0x7c, 0x7c, 0x7c, 0x7d, 0x7e, 0x7f, 0x80, 0x81, 0x7c, 0x7c, 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa0, 0xa0,
    0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xa6, 0xa6, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xac, 0xac, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6, 0xb7, 0xb2, 0xb2,
    0xb8, 0xb9, 0xba, 0xbb, 0xbc, 0xbd, 0xb8, 0xb8, 0xbe, 0xbf, 0xc0, 0xc1, 0xc2, 0xc3, 0xbe, 0xbe, 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa0, 0xa0,
    0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa0, 0xa0, 0x09, 0xc5, 0xc6, 0xc7, 0xc8, 0x0d, 0x09, 0x09, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xca, 0xca,
    0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0xd5, 0xd0, 0xd0, 0xd6, 0xd7, 0xd8, 0xd9, 0xda, 0xdb, 0xd6, 0xd6, 0xdc, 0xdd, 0xde, 0xdf, 0xe0, 0xe1, 0xdc, 0xdc,
    0x0b, 0xe3, 0xe4, 0xe5, 0xe6, 0x0f, 0x0b, 0x0b, 0x09, 0xc5, 0xc6, 0xc7, 0xc8, 0x0d, 0x09, 0x09, 0x09, 0xc5, 0xc6, 0xc7, 0xc8, 0x0d, 0x09, 0x09,
    0x00, 0x11, 0x12, 0x13, 0x14, 0x0c, 0x00, 0x00, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x16, 0x16, 0x1c, 0x1d, 0x1e, 0x1f, 0x20, 0x21, 0x1c, 0x1c,
    0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x22, 0x22, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x28, 0x28, 0x0a, 0x2f, 0x30, 0x31, 0x32, 0x0e, 0x0a, 0x0a,
    0x00, 0x11, 0x12, 0x13, 0x14, 0x0c, 0x00
};

const uint32_t gray_colors[] = { 0x00, 0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, 0xef, 0xf0, 0x3b, 0xf1, 0xf2, 0xf3, 0x08, 0x66,
                                 0xf5, 0xf6, 0xf7, 0xf8, 0x91, 0xf9, 0xfa, 0x07, 0xfb, 0xfc, 0xbc, 0xfd, 0xfe, 0xff, 0x0f };

auto
lead(auto format) {
    if (format == std::hex) {
        return 6;
    }
    return 0;
}

auto
one(std::function<uint32_t(uint32_t)> func) {
    return [func](auto a, auto b, auto c, auto d) { return func(a); };
}

auto
channel(std::function<uint32_t(uint32_t)> func) {
    return [func](auto a, auto b, auto c, auto d) { return (func(b) << 16) | (func(c) << 8) | func(d); };
}

auto
three(std::function<uint32_t(uint32_t, uint32_t, uint32_t)> func) {
    return [func](auto a, auto b, auto c, auto d) { return func(b, c, d); };
}

unsigned char
new_rgb_to_xterm256(unsigned char color_r, unsigned char color_g, unsigned char color_b) {

    if (color_r == color_g && color_g == color_b) {
        return 232 + (color_r * 23) / 255;
    }

    unsigned char r_index = (color_r * 5) / 255;
    unsigned char g_index = (color_g * 5) / 255;
    unsigned char b_index = (color_b * 5) / 255;

    unsigned char result = 16 + 36 * r_index + 6 * g_index + b_index;

    return result;
}

unsigned char
old_rgb_to_xterm256(unsigned char r, unsigned char g, unsigned char b) {

    unsigned char c3r = 0;
    unsigned char c3g = 0;
    unsigned char c3b = 0;

    if (r > 0) {
        c3r = 1;
        while (r > 0x5f) {
            r -= 0x28;
            c3r += 1;
        }
    }

    if (g > 0) {
        c3g = 1;
        while (g > 0x5f) {
            g -= 0x28;
            c3g += 1;
        }
    }

    if (b > 0) {
        c3b = 1;
        while (b > 0x5f) {
            b -= 0x28;
            c3b += 1;
        }
    }

    return legacy_xterm256_colors_3bits[(c3r << 6) | (c3g << 3) | c3b];
}

uint32_t
bit_8to3(uint32_t input) {
    uint32_t output = 0;
    if (input > 0) {
        output = 1;
        while (input > 0x5f) {
            input -= 0x28;
            output += 1;
        }
    }
    return output;
}

uint32_t
bit_3to8(uint32_t input) {
    static uint32_t incs[] = { 0x00, 0x5f, 0x87, 0xaf, 0xd7, 0xff };

    if (input >= sizeof(incs)) {
        return 0;
    }

    return incs[input];
}

uint32_t
xterm256_to_rgb(uint32_t color_id) {
    uint32_t i = 0;
    if (i < 0 || i > (sizeof(xterm256_colors) / sizeof(*xterm256_colors))) {
        0;
    }
    return xterm256_colors[i];
}

uint32_t
original_to_xterm256(uint32_t color) {
    uint16_t i = 0;
    while (i < sizeof(xterm256_colors) / sizeof(*xterm256_colors)) {
        if (xterm256_colors[i] == color) {
            return i;
        }
        i++;
    }
    return 0;
}

uint32_t perfect_to_xterm256(uint32_t r, uint32_t g, uint32_t b)
{
    uint16_t i = 0;
    uint32_t nestest_color = 0;
    int64_t nestest_distance = -1;
    while (i < sizeof(xterm256_colors) / sizeof(*xterm256_colors)) {
        uint32_t cur_color = xterm256_colors[i];
        uint32_t x = (cur_color >> 16) & 0xFF;
        uint32_t y = (cur_color >> 8) & 0xFF;
        uint32_t z = cur_color & 0xFF;
        uint64_t cur_distance = std::sqrt(std::pow(x - r, 2) + std::pow(y - g, 2) + std::pow(z - b, 2));
        if (nestest_distance == -1 || cur_distance <= nestest_distance) {
            nestest_distance = cur_distance;
            nestest_color = i;
        }
        i++;
    }

    return nestest_color;
}

int
xterm_to_color() {
    int i = 0;
    while (scanf("%d\n", &i) == 1) {
        printf("\033[48;5;%dm  ", i);
    }
    printf("\n\033[0m");
    return 0;
}

auto
command_range(auto start, auto end, auto increment, auto format) {
    return [start, end, increment, format]() {
        auto i = start;
        while (i <= end) {
            std::cout << std::setfill('0') << std::setw(lead(format)) << format << i << std::endl;
            i += increment;
        }
        return 0;
    };
}

auto
command_map(auto input, auto end, auto format) {
    return [input, end, format]() {
        auto i = 0;
        while (i < end / sizeof(*input)) {
            std::cout << std::setfill('0') << std::setw(lead(format)) << format << input[i++] << std::endl;
        }
        return 0;
    };
}

auto
command_conversor(std::function<uint32_t(uint32_t, uint32_t, uint32_t, uint32_t)> func, auto format_in, auto format_out) {

    return [func, format_in, format_out]() {
        uint32_t number, len;
        if (format_in == std::hex) {
            uint8_t r, g, b;
            while (scanf("%x%n\n", &number, &len) == 1) {
                if (len != 6) {
                    break;
                }
                r = (number >> 16) & 0xFF;
                g = (number >> 8) & 0xFF;
                b = number & 0xFF;
                number = func(number, r, g, b);
                std::cout << std::setfill('0') << std::setw(lead(format_out)) << format_out << number << std::endl;
            }
        } else {
            while (scanf("%d\n", &number) == 1) {
                std::cout << std::setfill('0') << std::setw(lead(format_out)) << format_out << func(number, 0, 0, 0) << std::endl;
            }
        }
        return 0;
    };
}

static const std::map<std::string, std::function<int()>> commands = {
    { "rgb", command_map(xterm256_colors, sizeof(xterm256_colors), std::hex) },
    { "full", command_range(0, 0xFFFFFF, 1, std::hex) },
    { "all", command_range(0, 255, 1, std::dec) },
    { "term", command_range(0, 15, 1, std::dec) },
    { "xterm", command_range(16, 230, 1, std::dec) },
    { "grayterm", command_map(gray_colors, sizeof(gray_colors), std::dec) },
    { "red", command_range(0x0, 0xFF0000, 0x10000, std::hex) },
    { "green", command_range(0x0, 0xFF00, 0x100, std::hex) },
    { "blue", command_range(0x0, 0xFF, 0x1, std::hex) },
    { "cyan", command_range(0x0, 0x00FFFF, 0x0101, std::hex) },
    { "yellow", command_range(0x0, 0xFFFF00, 0x010100, std::hex) },
    { "purple", command_range(0x0, 0xFF00FF, 0x010001, std::hex) },
    { "white", command_range(0x0, 0xFFFFFF, 0x010101, std::hex) },
    { "823", command_conversor(channel(bit_8to3), std::hex, std::hex) },
    { "328", command_conversor(channel(bit_3to8), std::hex, std::hex) },
    { "dec2hex", command_conversor(one([](int x) { return x; }), std::dec, std::hex) },
    { "hex2dec", command_conversor(one([](int x) { return x; }), std::hex, std::dec) },
    { "rgb2xterm", command_conversor(three(rgb_to_xterm256), std::hex, std::dec) },
    { "mateus2xterm", command_conversor(three(new_rgb_to_xterm256), std::hex, std::dec) },
    { "dornelles2xterm", command_conversor(three(old_rgb_to_xterm256), std::hex, std::dec) },
    { "original2xterm", command_conversor(one(original_to_xterm256), std::hex, std::dec) },
    { "perfect2xterm", command_conversor(three(perfect_to_xterm256), std::hex, std::dec) },
    { "xterm2rgb", command_conversor(one(xterm256_to_rgb), std::dec, std::hex) },
    { "xterm2color", xterm_to_color },
};

int
main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "command list:";
        for (const auto &command : commands) {
            std::cerr << " " << command.first;
        }
        std::cerr << std::endl;
        return 1;
    }

    auto command = commands.find(argv[1]);

    if (command == commands.end()) {
        std::cerr << "command not found: " << argv[1] << std::endl;
        return 1;
    }

    return command->second();
}
