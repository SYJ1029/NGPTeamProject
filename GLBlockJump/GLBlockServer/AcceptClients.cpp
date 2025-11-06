#include "AcceptClients.h"


DWORD WINAPI ProcessServer(LPVOID arg)
{
	return 0;
}


int ConnectSocket(SOCKET& listen_sock)
{
	int retval = 0;
	// 데이터 통신에 사용할 변수
	ThreadParam client_param[MAX_CLIENTS];
	struct sockaddr_in clientaddr;
	int addrlen;
	HANDLE hThread[MAX_CLIENTS];

	while (1) {
		// accept()
		addrlen = sizeof(clientaddr);

		// 접속한 클라이언트의 주소를 담을 문자열
		char addr[INET_ADDRSTRLEN];

		for (int i = 0; i < MAX_CLIENTS; i++)
		{
			//반복문을 통해 2개의 클라리언트 소켓을 하나의 배열 안에 받음
			client_param[i].sock = accept(listen_sock, (struct sockaddr*)&clientaddr, &addrlen);
			if (client_param[i].sock == INVALID_SOCKET) {
				err_quit("accept()"); // err_display()에서 err_quit()로 변경, 오류 시 종료
			}

			// 접속한 클라이언트 정보 출력
			inet_ntop(AF_INET, &clientaddr.sin_addr, addr, sizeof(addr));
			printf("\n[TCP 서버] 클라이언트 접속: IP 주소=%s, 포트 번호=%d\n\n",
				addr, ntohs(clientaddr.sin_port));

			// id 설정
			client_param[i].id = i;
		}

		for (int i = 0; i < MAX_CLIENTS; i++) {
			// 쓰레드 생성 없이 전송(게임 시작 이전에 쓰레드를 만들면서 할 필요가 없음)

			WORD len = htons(sizeof(UINT));
			retval = send(client_param[i].sock, (char*)(&len), sizeof(WORD), 0);
			if (retval == SOCKET_ERROR) { err_quit("send()"); }

			std::cout << "길이 보냈음 " << std::endl;

			UINT nid = htonl(client_param[i].id);
			retval = send(client_param[i].sock, (char*)&nid, sizeof(UINT), 0);
			if (retval == SOCKET_ERROR) { err_quit("send()"); }

			std::cout << "ID 보냈음 " << std::endl;

			
		}
	}
}


