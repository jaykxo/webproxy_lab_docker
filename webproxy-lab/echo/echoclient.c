#include  "csapp.h" // robust I/O 및 네트워크 함수가 정의된 헤더 포함

int main(int argc, char **argv)
{
    int clientfd; // 클라이언트 소켓 디스크립터
    char *host, *port, buf[MAXLINE]; // 호스트명, 포트번호, 데이터 버퍼
    rio_t rio; // robust I/O용 구조체

    if (argc != 3) {
        fprintf(stderr, "usage: %s <host> <port>\n", argv[0]); // 사용법 안내 메시지 출력
        exit(0); // 인자 개수 틀릴 경우 종료
    }
    host = argv[1]; // 첫 번째 인자: 호스트명
    port = argv[2]; // 두 번째 인자: 포트번호

    clientfd = Open_clientfd(host, port); // 서버와 연결
    Rio_readinitb(&rio, clientfd); // robust I/O 초기화

    while (Fgets(buf, MAXLINE, stdin) != NULL) { // 사용자 입력을 한 줄 읽음
        Rio_writen(clientfd, buf, strlen(buf)); // 입력 내용을 서버에 전송
        Rio_readlineb(&rio, buf, MAXLINE); // 서버 응답 수신
        Fputs(buf, stdout); // 응답 출력
    }
    Close(clientfd); // 소켓 닫기
    exit(0); // 정상 종료
}