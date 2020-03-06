#ifndef _REQUESTS_
#define _REQUESTS_

char *compute_get_request(char *host,const char *url,const char *url_params,const char *authorization,const char *cookie1_get,const char *cookie2_get);
char *compute_post_request(char *host,const char *url, char *form_data,const char *type,const char *cookie1,const char *cookie2);

#endif
