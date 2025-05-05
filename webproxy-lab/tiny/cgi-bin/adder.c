/*
 * adder.c - a minimal CGI program that adds two numbers together
 */
/* $begin adder */
#include "../csapp.h"

int main(void)
{
  setbuf(stdout, NULL);  // Disable buffering for stdout

  char *buf, *p;
  char arg1[MAXLINE], arg2[MAXLINE], content[MAXLINE];
  int n1 = 0, n2 = 0;

  buf = getenv("QUERY_STRING");

  /* Extract the two arguments */
  if (buf != NULL)
  {
    p = strchr(buf, '&');
    if (p != NULL) {
      size_t len1 = p - buf;
      if (len1 >= MAXLINE) len1 = MAXLINE - 1;
      strncpy(arg1, buf, len1);
      arg1[len1] = '\0';
      snprintf(arg2, MAXLINE, "%s", p + 1);
    } else {
      snprintf(arg1, MAXLINE, "%s", buf);
      arg2[0] = '\0';
    }

    // Support both key=value and raw number inputs
    char *val1 = strchr(arg1, '=');
    char *val2 = strchr(arg2, '=');

    if (val1)
      n1 = atoi(val1 + 1);
    else
      n1 = atoi(arg1);

    if (val2)
      n2 = atoi(val2 + 1);
    else
      n2 = atoi(arg2);
  }

  /* Make the response body */
  sprintf(content, "QUERY_STRING=%s\r\n<p>", buf ? buf : "");
  sprintf(content + strlen(content), "Welcome to add.com: ");
  sprintf(content + strlen(content), "THE Internet addition portal.\r\n<p>");
  sprintf(content + strlen(content), "The answer is: %d + %d = %d\r\n<p>",
          n1, n2, n1 + n2);
  sprintf(content + strlen(content), "Thanks for visiting!\r\n");

  /* Generate the HTTP response */
  printf("Status: 200 OK\r\n");
  printf("Content-type: text/html\r\n");
  printf("Content-length: %d\r\n", (int)strlen(content));
  printf("\r\n\r\n");
  printf("%s", content);
  fflush(stdout);
  // close(STDOUT_FILENO);  // Removed to prevent unintended server loop issues

  exit(0);
}
/* $end adder */