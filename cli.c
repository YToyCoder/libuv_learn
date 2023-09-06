#include <uv.h>
#include <stdio.h>

#define WriteContent "Hello, world!\n"

void on_write(uv_write_t* req, int status)
{
  if(status < 0 ) {
    printf("write error\n");
  }
  else {
    printf("write finish\n");
  }
}

void on_connect(uv_connect_t* req, int status) {
  switch(status) {
    case 0:
      {
        printf("connected server\n");
        uv_write_t* rReq = (uv_write_t*)malloc(sizeof(uv_write_t));
        ssize_t bufs = sizeof(WriteContent);
        uv_buf_t buf = uv_buf_init(WriteContent, bufs);
        uv_write(rReq,(uv_stream_t*) req->handle, &buf, 1, on_write);
      }
      break;
    default:
      printf("connected failed, status %d \n", status);
  }
}

int main() {
  uv_tcp_t* socket = (uv_tcp_t*)malloc(sizeof(uv_tcp_t));
  uv_tcp_init(uv_default_loop(), socket);

  uv_connect_t* connect = (uv_connect_t*) malloc(sizeof(uv_connect_t));

  struct sockaddr_in dst;
  uv_ip4_addr("127.0.0.1", 9001, &dst);

  uv_tcp_connect(connect, socket, (const struct sockaddr*)&dst, on_connect);
  return uv_run(uv_default_loop(), UV_RUN_DEFAULT);

}