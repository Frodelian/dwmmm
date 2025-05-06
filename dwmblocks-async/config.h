#ifndef CONFIG_H
#define CONFIG_H
#define STATUSBAR "dwmblocks"

// String used to delimit block outputs in the status.
#define DELIMITER "   "

// Maximum number of Unicode characters that a block can output.
#define MAX_BLOCK_OUTPUT_LENGTH 45

// Control whether blocks are clickable.
#define CLICKABLE_BLOCKS 1

// Control whether a leading delimiter should be prepended to the status.
#define LEADING_DELIMITER 0

// Control whether a trailing delimiter should be appended to the status.
#define TRAILING_DELIMITER 0

// Define blocks for the status feed as X(icon, cmd, interval, signal).
#define BLOCKS(X)             \
    X("", "/home/frodelian/Downloads/dwmblocks-async/sb-kb", 1, 12) \
    X("", "/home/frodelian/Downloads/dwmblocks-async/sb-memory", 5, 4) \
    X("", "/home/frodelian/Downloads/dwmblocks-async/sb-volume", 1, 8)  \
    X("", "/home/frodelian/Downloads/dwmblocks-async/sb-battery", 5, 9) \
    X("", "/home/frodelian/Downloads/dwmblocks-async/sb-date", 1, 10)
#endif  // CONFIG_H
