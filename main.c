#include <stdio.h>
#include <uv.h>
/*
int64_t counter = 0;

void wait_for_a_while(uv_idle_t* handle) {
  counter++;

  if(counter >= 10e6)
    uv_idle_stop(handle);
}

int main() {
  uv_idle_t idler;

  uv_idle_init(uv_default_loop(), &idler);
  uv_idle_start(&idler, wait_for_a_while);

  printf("Idling...\n");
  uv_run(uv_default_loop(), UV_RUN_DEFAULT);

  uv_loop_close(uv_default_loop());
  return 0;
}

*/

/** tcp connection 
 */

uv_loop_t* loop;
uv_tcp_t addr;

void echo_read(uv_stream_t* stream, ssize_t size, const uv_buf_t* buf) {
  printf("read \n");
}

void on_alloc(uv_handle_t* handle, size_t suggested_size, uv_buf_t* buf) {
  buf->base = malloc(suggested_size);
  buf->len = suggested_size;
}

void on_new_connection(uv_stream_t* server, int status) {
  if(status < 0) {
    fprintf(stderr, "new connnection error %s \n", uv_strerror(status));
    return ;
  }

  uv_tcp_t *client = (uv_tcp_t*) malloc(sizeof(uv_tcp_t));
  uv_tcp_init(loop, client);
  if(uv_accept(server, (uv_stream_t*)client) == 0) {
    printf("connected cli\n");
    uv_read_start((uv_stream_t*) client, on_alloc, echo_read);
  }
  else {
    uv_close((uv_handle_t*) client, NULL);
  }
}

int main() {
  loop = uv_default_loop();

  uv_tcp_t server;
  uv_tcp_init(loop, &server);

  uv_ip4_addr("0.0.0.0", 9001, &addr);

  uv_tcp_bind(&server, (const struct sockaddr*)&addr, 0);
  int r = uv_listen((uv_stream_t*)&server, 2, on_new_connection);

  if(r) {
    fprintf(stderr, "Listen error %s \n", uv_strerror(r));
    return 1;
  }
  return uv_run(loop, UV_RUN_DEFAULT);
}