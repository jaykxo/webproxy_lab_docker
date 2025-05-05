#include "csapp.h" // robust I/O와 네트워크 함수들이 정의된 헤더 포함

void echo(int connfd); // echo 함수 선언 (echo.c에서 정의됨)

int main(int argc, char **argv)
{
    int listenfd, connfd; // 리슨용 소켓과 클라이언트 연결용 소켓
    socklen_t clientlen; // 클라이언트 주소 크기
    struct sockaddr_storage clientaddr; // 클라이언트 주소 정보 저장
    char client_hostname[MAXLINE], client_port[MAXLINE]; // 호스트명과 포트 번호 저장용 문자열

    if (argc != 2) {
        fprintf(stderr, "usage: %s <port>\n", argv[0]); // 사용법 출력
        exit(0);
    }

    listenfd = Open_listenfd(argv[1]); // 포트 번호로 리슨 소켓 생성
    while (1) {
        clientlen = sizeof(struct sockaddr_storage); // 주소 크기 설정
        connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen); // 연결 요청 수락
        Getnameinfo((SA*) &clientaddr, clientlen, client_hostname, MAXLINE,
                    client_port, MAXLINE, 0); // 클라이언트 주소를 호스트/포트 문자열로 변환
        printf("Connected to (%s, %s)\n", client_hostname, client_port); // 접속 정보 출력
        echo(connfd); // 클라이언트와 통신 수행
        Close(connfd); // 연결 종료
    
    }
    exit(0); // 프로그램 종료
}