#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>

int main(int argc, char* argv[]) {
  if (argc != 3) {
    fprintf(stderr, "Usage: %s <file> <content>\n", argv[0]);
    return 1;
  }
  // open up syslog
  openlog("writer", LOG_PID | LOG_CONS, LOG_USER);

  char* filepath = argv[1];
  char* content = argv[2];

  FILE* file = fopen(filepath, "w");
  if (!file) {
    fprintf(stderr, "Error opening file: %s\n", strerror(errno));
    return 1;
  }

  if (fputs(content, file) == EOF) {
    syslog(LOG_ERR, "Failed to write to file: %s\n", strerror(errno));
    fclose(file);
    closelog();
    return 1;
  }

  syslog(LOG_DEBUG, "Writing %s to %s", content, filepath);

  closelog();
  fclose(file);

  return 0;
}
