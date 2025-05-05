
#include "csapp.h" // robust I/O와 네트워크 함수들이 정의된 헤더 포함
#include "csapp.h"

void echo(int connfd) { // 클라이언트 연결 소켓을 인자로 받는 echo 함수
    size_t n;             // 읽은 바이트 수
    char buf[MAXLINE];    // 입력 데이터를 담을 버퍼
    rio_t rio;            // robust I/O 구조체

    Rio_readinitb(&rio, connfd); // connfd를 기반으로 rio 초기화
    while ((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0) { // 한 줄씩 읽기
        printf("server received %zu bytes\n", n); // 읽은 바이트 수 출력
        Rio_writen(connfd, buf, n); // 클라이언트에게 다시 전송 (echo)
    }
}