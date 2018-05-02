#ifndef __DEFINE_H
#define __DEFINE_H

#define STR_BUFFER				128
#define TEMP_BUFFER				1024


#define OPT_USEC	1111
#define PASSES_PER_SEC	(1000000 / OPT_USEC)	// 1000000 / 1111 = 900 번.
#define RL_SEC		* PASSES_PER_SEC



// RL_SEC = 10
#define PULSE_SAVE_ALL			( 20 RL_SEC)	// 로그찍는다  // 20 * 10 = 200


#define PULSE_CONNECT_TIMEOUT	120	// 2분 동안 들어오는 값이 없으면 접속을 끊는다.. 600
#define LOSE_CONNECT_TIMEOUT	20	// keep패킷을 보낸후 20초동안 응답이 없으면 짜른다.


//#define	PULSE_GAME_TIMEOUT		( 180 RL_SEC )	// 게임내에서 3분동안 아무 응답이 없으면 짤린것으로 간주한다.

#define PULSE_COUNTER_TIMEOUT	300000 //5분 카운터 서버로  인원을맞춘다....


//모바일이 이시간동안 아무 패킷이 없으면 끊어버린다.
#define PULSE_MOBILE_CONNECT_TIMEOUT	( 300 RL_SEC ) // 5분이다.


#define PULSE_DB_TIMEOUT		( 20 RL_SEC )	// DB에서 처리해야 할일이 30초이상되면 짤라버린다.

#define PULSE_FRIST_TIMEOUT		( 30 RL_SEC )	// 유저가 처음에 Connect하고 30초동안 아무정보를 날리지 않으면 짤라버린다.


#define DAY_LOOPING				864000			//하루에 Looping도는 횟수이다.(게임시작후 24시간 후를 가르킨다.)


#define MAX_BUFFER_SIZE			2048
//*******************RECEIVE SOCKET BUFFER*******************************//
//클라이언트로 받아서 분리한후 큐에 넣는 버퍼길이.
#define MAX_INPUT_LENGTH		MAX_BUFFER_SIZE					//Max length per *line* of input
//한 cmd의 길이가 이것을 넘으면 안된다. 실제들어온 사이즈
#define MAX_RAW_INPUT_LENGTH	MAX_BUFFER_SIZE					/* Max size of *raw* input */
//BufferSize  // ClientSocket에서 들어온 하나이 패킷이다.
#define INPUT_Q_BUFSIZE			MAX_BUFFER_SIZE					/* Static output buffer size   */
//***********************************************************************//
//*******************SEND(LISTEN)SOCKET BUFFER***************************//
#define MAX_SOCK_BUF            (12 * 1024)		/* Size of kernel's sock buf   */
//***********************************************************************//



#define MAX_PROMPT_LENGTH       96				/* Max length of prompt        */
#define GARBAGE_SPACE			32				/* Space for **OVERFLOW** etc  */
#define SMALL_BUFSIZE			4096			/* Static output buffer size   */



/* Max amount of output that can be buffered */
#define LARGE_BUFSIZE	   (MAX_SOCK_BUF - GARBAGE_SPACE - MAX_PROMPT_LENGTH)

//#define MAX_BUFFER				8192
#define NORMAL_SEND_BUFFER		2048
#define MID_SEND_BUFFER			2048
#define LARGE_SEND_BUFFER		5000

#define MAX_STRING_LENGTH		4096			// temp Buffer

#define HOST_LENGTH				 40		/* Used in char_file_u *DO*NOT*CHANGE* */




#define STATE(d)			((d)->m_nUserMode) //UserMode
#define STATEDBMODE(d)      ((d)->m_nDBMode)

//디비를 기다려야 하는지. ( 디비를 기다리는동안에 패킷이 날라오면 안되니깐.
#define WAITTING_DB(d)	((d)->m_bWaitDb)

//디비를 업데이트만 하는지. ( 업데이트가 너무 오래걸리면 짤라야하니깐. )
#define UPDATE_DB(d) ((d)->m_bUpdateDb)

//디비를 호출한후에 실해하면 
#define ACCESSED_DB(d)	((d)->m_bDbAccess)

//유저가 게임방인지 대기실인지 알기위해.
#define USERPOSITION(d)	((d)->m_nGameMode)


#define ISNEWL(ch) ((ch) == '~') 
#define ISNEWLP(ch) ((ch) == '|') 

#define CLOSE_SOCKET(sock)	closesocket(sock)
#define SEND_TO_Q(messg, desc, length)  (desc)->WriteToOutput(messg, length)


#define INIT_USER_NO			1			//처음 유저 넘버 시작.


#define MAX_Q_NUM  100000
#define MAX_JACKPOTQ_NUM	1000

#define SAFE_DELETE(pointer)				if ( (pointer) != NULL ) { delete (pointer);	(pointer) = NULL; }
#define SAFE_DELETE_ARRAY(pointer)			if ( (pointer) != NULL ) { delete [] (pointer);	(pointer) = NULL; }

#define is_space(c)		(c == 0x20 || (c >= 0x09 && c <= 0x0D))



#define REMOVE_FROM_LIST(item, head, next)	\
			if ((item) == (head))		\
				head = (item)->next;		\
			else {				\
				temp = head;			\
				while (temp && (temp->next != (item))) \
					temp = temp->next;		\
				if (temp)				\
					temp->next = (item)->next;	\
			}					\
			

#define REMOVE_CHANNEL_LIST( DeleteUser, List, m_User, m_NextList ) \
			if ( List != NULL ) {							\
				if ( List->m_User == DeleteUser ) {			\
					pTemp = List;							\
					List = List->m_NextList;				\
					SAFE_DELETE(pTemp);						\
				}											\
				else {										\
					pTemp = List;							\
					while ( pTemp && ( pTemp->m_NextList->m_User != DeleteUser ) )  \
						pTemp = pTemp->m_NextList;									\
					if (pTemp) {													\
						pTempNext = pTemp->m_NextList;								\
						pTemp->m_NextList = pTemp->m_NextList->m_NextList;			\
						SAFE_DELETE(pTempNext);										\
					}																\
				}																	\
			}																	

  
//REMOVE_FROM_LIST(d, m_UserDescriptorList, m_pNext);

#define CREATE(result, type, number)  do {\
	if ((number) <= 0)	\
		LogFile("SYSERR: Zero bytes or less requested at");	\
	if (!((result) = new type [(number)]))	\
		{ LogFile ("SYSERR: new failure"); exit(0); } } while(0)

#define CLOSE_SOCKET(sock)	closesocket(sock)

#define LOWER(c)   (((c)>='A'  && (c) <= 'Z') ? ((c)+('a'-'A')) : (c))



//RAMDOM
#define	m  (unsigned long)2147483647
#define	q  (unsigned long)127773

#define	a (unsigned int)16807
#define	r (unsigned int)2836


#define MAX_BURDEN_WEIGHT_PER		10	  // 부담중량을 10 %중에 뽑아야 하므로.
#define MAX_BURDEN_WEIGHT			20    // 20Kg에서 랜덤으로 뽑아야 하므로.




//**********************************
//USERSTATE
#define CMD_WAIT				0		//	Client의 로그인이 처리되고 나서 이후 패킷에 대한 정보를 가지고 분리한다.
#define NONE					1
//#define GAMING_EXITUPDATE		4		// 유저가 게임중 나갔을때.
//#define DBUP					5
#define GETUSER					6
#define USER_UPDATE				7


#define CLIENT_WILL_DISCONNECT	101		//  클라이언트가 끊겼다. DB에 요청해야한다.
#define CLIENT_DISCONNECTED		102		//	DB에도 정상적으로 요청했다. 지우면된다.
/**********************************/

//*********************************
//GameMode
#define USERNONE				0		//유저가 접속했을때나 삭제했을때.
#define USERWAIT				1		//유저가 대기실에 있을때.
#define USERGAME				2		//유저가 게임방에 있을때.



#define REALTIME_REFRESH




#define DBCONNECT
#define PACKETANALY


// Tick을 잡기 위한(초 단위)
#define TICS_GAP_SEC             1    // 기본 tics는 1초
#define REFRESH_TICS             86400 // 24시간마다 tics를 새로 셋팅








#define		MAX_EVALUTON_CNT					10


#define		POKER_ROYAL_STRAIGHT_FLUSH			11
#define		POKER_STRAIGHT_FLUSH				10
#define		POKER_FOUR_CARD						9
#define		POKER_FULL_HOUSE					8
#define		POKER_FLUSH							7
#define		POKER_MOUNTAIN						6
#define		POKER_BACK_STRAIGHT					5
#define		POKER_STRAIGHT						4
#define		POKER_THREE_CARD					3
#define		POKER_TWO_PAIR						2
#define		POKER_ONE_PAIR						1
#define		POKER_NO_PAIR						0





#define		BADUKI_MADE_GOLF					0
#define		BADUKI_MADE_SECOND					1
#define		BADUKI_MADE_THIRD					2
#define		BADUKI_MADE							3
#define		BADUKI_BASE							4
#define		BADUKI_TWO_BASE						5
#define		BADUKI_TOP							6



#define		BADUKI_ERROR						7







enum BettingHistory { FULL, HALF, QUATER, DDADANG, BBING, CHECK };

#endif
