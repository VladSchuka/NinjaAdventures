#define _CRT_SECURE_NO_WARNINGS

#include <WinSock.h>
#include<Windows.h>
#include<iostream>

#define MAX_ROOMS 3

typedef enum { empty, waiting, full } Roomstate;

#define CHAT_MESSAGE 24
#define PLAYER_POSITION 7
#define SYSTEM_MESSAGE 5

#define ROOM_STATE_REQUEST 9

#define SERVER_FULL 666
#define CONNECTION_ACCEPTED 13

#define ROOM_READY 73
#define ROOM_NOT_READY 74

#pragma comment (lib, "ws2_32.lib")

struct Message {
	int type;
	int ID;
	union {
		struct {
			double x;
			double y;
			bool facingright;
			int currentstate;
		};
		char chatmsg[30];
		int systemmsg;
	};
};


typedef struct {
	SOCKET socket[2];
	bool activeconnection[2];
	HANDLE tread[2];
	Roomstate roomstate;
}GameRoom;

typedef struct {
	int roomID;
	GameRoom *room;
	int playerID;
}ThreadParam;

SOCKADDR_IN addr;
int addrlen = sizeof(addr);

SOCKET sConnect;
SOCKET sListen;

GameRoom gamerooms[MAX_ROOMS];


int InitWinSock()
{
	int Val = 0;
	WSAData wsaData;
	WORD DllVersion = MAKEWORD(2, 1);

	Val = WSAStartup(DllVersion, &wsaData);

	return Val;
}

int ServerThread(void *param)
{
	ThreadParam *p = (ThreadParam*)param;
	Message Buffer;
	int size = 0;

	GameRoom *room = p->room;
	int ID = p->playerID;
	int secondplayer = 1 - ID;

	while (true)
	{
		ZeroMemory(&Buffer, sizeof(Buffer));

		if ((size = recv(room->socket[ID], (char*)&Buffer, sizeof(Buffer), NULL)) > 0)
		{
			switch (Buffer.type) {
			case SYSTEM_MESSAGE:
				switch (Buffer.systemmsg) {
				case ROOM_STATE_REQUEST:
					if (room->roomstate == full) { Buffer.systemmsg = ROOM_READY; }
					else { Buffer.systemmsg = ROOM_NOT_READY; }
					send(room->socket[ID], (char*)&Buffer, sizeof(Buffer), NULL);
					break;
				}
				break;
			case CHAT_MESSAGE: case PLAYER_POSITION: 
				send(room->socket[secondplayer], (char*)&Buffer, sizeof(Buffer), NULL);
				break;
			}
		}
		else {
			printf("User disconnected.\n");
			room->activeconnection[ID] = false;
			if (!room->activeconnection[secondplayer]) { room->roomstate = empty; }
			closesocket(room->socket[ID]);
			return 0;
		}
	}
}

int FindRoom(SOCKET sConnect) {
	for (int i = 0; i < MAX_ROOMS; i++) {
		if (gamerooms[i].roomstate == waiting) {

			int c;
			if (gamerooms[i].activeconnection[0]) { c = 1; }
			else { c = 0; }

			gamerooms[i].socket[c] = sConnect;
			gamerooms[i].activeconnection[c] = true;
			static ThreadParam param;
			param.roomID = i;
			param.room = &gamerooms[i];
			param.playerID = c;
			gamerooms[i].tread[c] = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ServerThread, (void *)(&param), NULL, NULL);
			gamerooms[i].roomstate = full;
			return i;
		}
	}
	for (int i = 0; i < MAX_ROOMS; i++) {
		if (gamerooms[i].roomstate == empty) {

			int c;
			if (gamerooms[i].activeconnection[0]) { c = 1; }
			else { c = 0; }

			gamerooms[i].socket[c] = sConnect;
			gamerooms[i].activeconnection[c] = true;
			static ThreadParam param;
			param.roomID = i;
			param.room = &gamerooms[i];
			param.playerID = c;
			gamerooms[i].tread[c] = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ServerThread, (LPVOID)(&param), NULL, NULL);
			gamerooms[i].roomstate = waiting;
			return i;
		}
	}
	return -1;
}

int main()
{
	int a = sizeof(double);
	int b = sizeof(Message);

	system("color 0a");

	printf("Server Started.\n");

	int Val = InitWinSock();

	if (Val != 0)
	{
		MessageBoxA(NULL, "Error while attemting to Startuo WinSock!", "Error", MB_OK | MB_ICONERROR);
		exit(1);
	}

	sListen = socket(AF_INET, SOCK_STREAM, NULL);
	sConnect = socket(AF_INET, SOCK_STREAM, NULL);

	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(27015);
	addr.sin_family = AF_INET;


	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));

	listen(sListen, 64);

	while (true)
	{
		if (sConnect = accept(sListen, (SOCKADDR*)&addr, &addrlen))
		{
			printf("New Connection request.\n");
			int roomindex = FindRoom(sConnect);
			Message msg;
			msg.type = SYSTEM_MESSAGE;
			if (roomindex == -1) {
				msg.systemmsg = SERVER_FULL;
				printf("Connectioin declined.!\n");
			}
			else {
				msg.systemmsg = CONNECTION_ACCEPTED;
				printf("Connectioin accepted.!\n");
			}

			send(sConnect, (char*)&msg, sizeof(msg), NULL);			
		}
	}
}

