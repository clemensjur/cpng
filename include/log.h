#define DEBUG(val) fprintf(stdout, "\x1b[38;5;28m[DEBUG]\x1b[0m %s\n", val)
#define INFO(val) fprintf(stdout, "\x1b[38;5;39m[INFO]\x1b[0m %s\n", val)
#define WARN(val) fprintf(stdout, "\x1b[38;5;208m[WARN]\x1b[0m %s\n", val)
#define ERR(val) fprintf(stderr, "\x1b[38;5;160m[ERROR]\x1b[0m %s\n", val)
