#include <uv.h>
#include <stdio.h>

void on_connect(uv_connect_t* req, int status) {
  switch(status) {
    case 0:
      printf("connected server\n");
      break;
    default:
      printf("connected failed\n");
  }
}

int main() {
  uv_tcp_t* socket = (uv_tcp_t*)malloc(sizeof(uv_tcp_t));
  uv_tcp_init(uv_default_loop(), socket);

  uv_connect_t* connect = (uv_connect_t*) malloc(sizeof(uv_connect_t));

  struct sockaddr_in dst;
  uv_ip4_addr("0.0.0.0", 9001, &dst);

  uv_tcp_connect(connect, socket, (const struct sockaddr*)&dst, on_connect);
  uv_run(uv_default_loop(), UV_RUN_DEFAULT);

  return 0;
}