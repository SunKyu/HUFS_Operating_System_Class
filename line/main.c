
/*********************************************************
	적외선 센서를 이용한 라인트레이서 예제 프로그램
**********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "uart_api.h"
#include "robot_protocol.h"
#include "keyboard.h"
#include "stack.h"
#include "dijkstra.h"
#include "Node.h"
#define TU_FOWARD 6
#define TU_RIGHT 7
#define TU_LEFT 8
#define TU_UTURN 9

int judgement(int next, int curr, int * dir){
    int i = 0;
    switch (*dir){
        case UP:
            for ( i = 0; i <4; i++){
                if(node_arr[curr].dir[i] == next){
                    if( i == UP){
                        *dir = i;
                        return TU_FOWARD;
                    }
                    else if (i== LEFT){
                        *dir = i;
                        return TU_LEFT;
                    }
                    else if (i == RIGHT){
                        *dir = i;
                        return TU_RIGHT;
                    }
                }
            }

            break;
        case DOWN:
            for ( i = 0; i <4; i++){
                if(node_arr[curr].dir[i] == next){
                    if( i == DOWN){
                        *dir = i;
                        return TU_FOWARD;
                    }
                    else if (i == LEFT){
                        *dir = i;
                        return TU_RIGHT;
                    }
                    else if (i == RIGHT){
                        *dir = i;
                        return TU_LEFT;
                    }
                }
            }
            break;
        case LEFT:
            for ( i = 0; i <4; i++){
                if(node_arr[curr].dir[i] == next){
                    if( i == UP){
                        *dir = i;
                        return TU_RIGHT;
                    }
                    else if (i== LEFT){
                        *dir = i;
                        return TU_FOWARD;
                    }
                    else if (i == DOWN){
                        *dir = i;
                        return TU_LEFT;
                    }
                }
            }
            break;
        case RIGHT:
            for ( i = 0; i <4; i++){
                if(node_arr[curr].dir[i] == next){
                    if( i == UP){
                        *dir = i;
                        return TU_LEFT;
                    }
                    else if (i== DOWN){
                        *dir = i;
                        return TU_RIGHT;
                    }
                    else if (i == RIGHT){
                        *dir = i;
                        return TU_FOWARD;
                    }
                }
            }
            break;
    }


}


int main()
{
	int ret;
    int dir = UP;
    int next_dir = 0;
    struct stack st_path;
    st_path = dijkstra_run(0);
    int befo = stack_pop(&st_path);//before node
    int current = befo;//current is node that robot stopped



	unsigned char Line_Value,tmp_line=0xff;

	ret = user_uart1_open("SAC1");
    node_init();

	if (ret < 0)
	{
		printf("\n UART1 Open error!");
		exit(0);
	}

	user_uart1_config(115200, 8, UART_PARNONE, 1);

	init_keyboard();

	printf("**************************\n");
	printf(" RoboCAR Linetracer exam\n");
	printf("**************************\n");

	RoboCAR_AllMotor_Control(STOP,0);

	while(1)
	{
		if(kbhit()) break;

		usleep(10*1000);

		Line_Value= RoboCAR_Get_InfraredRay_Data();

		printf("InfraredRay = 0x%x\n",Line_Value);

		if(tmp_line == Line_Value) continue;

		tmp_line = Line_Value;

		switch(Line_Value){

			//전진
			case 0xE7:	// 1110 0111
			case 0xEF:	// 1110 1111
			case 0xF7:	// 1111 0111
				RoboCAR_AllMotor_Control(FORWARD,60);
			break;

			//좌회전
			case 0xF3: //1111 0011
			case 0xFB: //1111 1011
			case 0xF9: //1111 1001
				RoboCAR_LeftMotor_Control(FORWARD,40);
				RoboCAR_RightMotor_Control(FORWARD,60);
			break;
			//우측으로 후진
			case 0xFC: // 1111 1100
			case 0xFD: // 1111 1101
			case 0xFE: // 1111 1110
				RoboCAR_LeftMotor_Control(BACKWARD,60);
				RoboCAR_RightMotor_Control(BACKWARD,40);
			break;

			//우회전
			case 0xCF: // 1100 1111
			case 0xDF: // 1101 1111
			case 0x9F: // 1001 1111
				RoboCAR_LeftMotor_Control(FORWARD,60);
				RoboCAR_RightMotor_Control(FORWARD,40);
			break;
			//좌측으로 후진
			case 0x3F: //0011 1111
			case 0xBF: //1011 1111
			case 0x7F: //0111 1111
				RoboCAR_LeftMotor_Control(BACKWARD,40);
				RoboCAR_RightMotor_Control(BACKWARD,60);
			break;

            //left turn angle
            case 0xE0: // 1110 0000
            case 0xF0: // 1111 0000
            case 0xF8: // 1111 1000
            //right turn angle
            case 0x07: // 0000 0111
            case 0x0F: // 0000 1111
            case 0x1F: // 0001 1111
            //cross road
            case 0x00: //0000 0000 cross road
                RoboCAR_AllMotor_Control(STOP, 0);
                befo = current;
                current = stack_pop(&st_path);
                next_dir = judgement(stack_top(&st_path), current, &dir);
                switch(next_dir){
                    case TU_FOWARD:
				        RoboCAR_AllMotor_Control(FORWARD,60);
                        break;
                    case TU_RIGHT:
                        usleep(1000*100*15);
                        RoboCAR_Move_Angle(RIGHT_ROTATION, 80 ,90);
                        usleep(1000*100*15);
                        break;
                    case TU_LEFT:
                        usleep(1000*100*15);
                        RoboCAR_Move_Angle(LEFT_ROTATION, 80 ,90);
                        usleep(1000*100*15);
                        break;
                }

            break;
			// 정지
			case 0xFF: //1111 1111
                RoboCAR_AllMotor_Control(STOP, 0);
                usleep(1000*100*20);
                RoboCAR_Move_Angle(RIGHT_ROTATION, 80 ,180);
                usleep(1000*100*20);
                st_path = dijkstra_run(current);
                befo = stack_pop(&st_path);
                break;
            break;
		}// end switch
	}//end while

	RoboCAR_AllMotor_Control(STOP,0);

	user_uart1_close();
	close_keyboard() ;

	return 0;
}


