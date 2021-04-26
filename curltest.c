#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

void printOutput(char *stringOutput, size_t size, size_t nmemb, void *stream)
{    
  printf("\n%s\n", stringOutput);
}

int main(void)
{
  CURL *curl;

  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, "http://worldtimeapi.org/api/ip.txt");
    /* example.com is redirected, so we tell libcurl to follow redirection */ 
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, printOutput);
 
    /* Perform the request, res will get the return code */ 
 
    curl_easy_perform(curl);
    
    /* always cleanup */ 
    curl_easy_cleanup(curl);
  }
  return 0;
}
