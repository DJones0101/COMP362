/**
* Darius Jones
* Lab 3 Task 4
* 2/12/2018
**/

#include "messg.h"

MESSG msg_rcvd[4], msg_send;

STAT stat; // holds response codes from functions
key_t key; // "address" of the process queue

float new_server_temp = 0;
float server_temp = 0;
int  equal_flag = 0;
float total_client_temp = 0;
int mailbox_num;
#define DONE -1
#define THRESHOLD .1

int main(int argc, char *argv[])
{
	msg_send.priority = DEFAULT_PRIORITY; // or "type"; can be used for selective reception

	
	server_temp = atoi(argv[1]);
	
	key = SRV_PORT;
	

	msg_send.sender = msgget(key, 0666 | IPC_CREAT); // 0666 will be explained later in the course

	if (msg_send.sender < 0) {
		oops("SRV: FAILED TO CREATE MESSAGE QUEUE.\n", 1);
		exit(EXIT_FAILURE);
	}

	while (TRUE) // check the defines in the h file
	{
		// recall: the first part of the message (long) is mandatory
		// the system want size of your part
		// the last '0' tells the system to block
		// alternatively, IPC_NOWAIT could be used if no blocking needed (no in this program)
		
		equal_flag =  0;
		total_client_temp = 0;

		for (mailbox_num = 0; mailbox_num < 4; mailbox_num++) {

			stat = msgrcv(msg_send.sender, &msg_rcvd[mailbox_num], sizeof(MESSG) - sizeof(long), DEFAULT_PRIORITY, 0);

			if (stat < 0)
			{
				printf("SRV: FAILED TO RECEIVE MESSAGE FROM CLIENT.\n");
				exit(EXIT_FAILURE);
			}
			else {
				printf("SRV: CLIENT %d REPORTS: %f\n", msg_rcvd[mailbox_num].sender, msg_rcvd[mailbox_num].num);
			}

			total_client_temp +=  msg_rcvd[mailbox_num].num;

			if (equal_flag == 0 && mailbox_num != 0) {

				if (fabs(msg_rcvd[mailbox_num].num - msg_rcvd[0].num) > THRESHOLD) {
					equal_flag = 1;
				}
			}

		}

		if (equal_flag == 0) {

			msg_send.num = DONE;

			for (mailbox_num = 0; mailbox_num < 4; mailbox_num++) {

				stat = msgsnd(msg_rcvd[mailbox_num].sender, &msg_send, sizeof(MESSG) - sizeof(long), 0);

				if (stat < 0) {
					printf("SRV: FAILED TO RECEIVE MESSAGE FROM CLIENT.\n");
					exit(EXIT_FAILURE);

				}

			}
			break;
		}


		msg_send.num = (2 * server_temp  + total_client_temp) / 6;


		for (mailbox_num = 0; mailbox_num < 4; mailbox_num++) {

			stat = msgsnd(msg_rcvd[mailbox_num].sender, &msg_send, sizeof(MESSG) - sizeof(long), 0);

			if (stat < 0) {
				printf("SRV: FAILED TO SEND RESPONSE TO CLIENT.\n");
				exit(EXIT_FAILURE);
			}

			
		}

	}


	stat = msgctl(msg_send.sender, IPC_RMID, NULL);

	printf("SRV: ALL CLIENTS STABLE\n");

	exit(EXIT_SUCCESS);
}
