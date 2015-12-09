
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


int disconnect(int next, int curr){
    map[curr][next] = 999;
    map[next][curr] = 999;
}

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
    dijkstra_run(0, 0, &st_path);
    int befo = stack_pop(&st_path);//before node
    int current = befo;//current is node that robot stopped
    printf("first current : %d\n", current);
    printf("st_path's top %d, top value %d\n", st_path.top,stack_top(&st_path));



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

		switch(Line_Value){

			//전진
			case 0xE7:	// 1110 0111
			case 0xEF:	// 1110 1111
			case 0xF7:	// 1111 0111
				RoboCAR_AllMotor_Control(FORWARD,50);
			break;

			//좌회전
			case 0xF3: //1111 0011
			case 0xFB: //1111 1011
			case 0xF9: //1111 1001
			case 0xFC: // 1111 1100
			case 0xFD: // 1111 1101
			case 0xFE: // 1111 1110
				RoboCAR_LeftMotor_Control(FORWARD,10);
				RoboCAR_RightMotor_Control(FORWARD,90);
			break;

			//우회전
			case 0xCF: // 1100 1111
			case 0xDF: // 1101 1111
			case 0x9F: // 1001 1111
			case 0x3F: //0011 1111
			case 0xBF: //1011 1111
			case 0x7F: //0111 1111
				RoboCAR_LeftMotor_Control(FORWARD,90);
				RoboCAR_RightMotor_Control(FORWARD,10);
			break;

            //left turn angle
            case 0xC0: // 1100 0000
            case 0xE0: // 1110 0000
            case 0xF0: // 1111 0000
            //right turn angle
            case 0x03: // 0000 0011
            case 0x07: // 0000 0111
            case 0x0F: // 0000 1111
            //cross road
            case 0x00: //0000 0000 cross road
                usleep(1000*10*15);
                befo = current;
                current = stack_pop(&st_path);
                next_dir = judgement(stack_top(&st_path), current, &dir);
	            printf("**************************\n");
                printf("path ");
                stack_print(&st_path);
                printf("NEXT_DIR : %d, current : %d, next_num : %d\n", next_dir, current, stack_top(&st_path));
                printf("st_path's top %d, top value %d\n", st_path.top,stack_top(&st_path));
	        	printf("InfraredRay = 0x%x\n",Line_Value);
	            printf("**************************\n");
                switch(next_dir){
                    case TU_FOWARD:
				        RoboCAR_AllMotor_Control(FORWARD,50);
                        break;
                    case TU_RIGHT:
                        RoboCAR_Move_Angle(RIGHT_ROTATION, 80 ,90);
                        usleep(1000*100*18);
                        break;
                    case TU_LEFT:
                        RoboCAR_Move_Angle(LEFT_ROTATION, 80 ,90);
                        usleep(1000*100*18);
                        break;
                }
 //               center(Line_Value);
                break;
			// 정지
			case 0xFF: //1111 1111
                RoboCAR_Move_Angle(RIGHT_ROTATION, 90 ,180);
                printf("==========UTURN==============\n");
	        	printf("InfraredRay = 0x%x\n",Line_Value);
                usleep(1000*100*26);
                if(dir == UP)
                    dir =DOWN;
                else if (dir == DOWN)
                    dir = UP;
                else if (dir == RIGHT)
                    dir = LEFT;
                else if (dir == LEFT)
                    dir = RIGHT;
                RoboCAR_AllMotor_Control(STOP, 0);
                disconnect(stack_top(&st_path), current);
                printf("map[%d][%d] : %d\n",stack_top(&st_path), current, map[stack_top(&st_path)][current]);
                dijkstra_run(current, 1, &st_path);
                printf("==========UTURN==============\n");
                befo = stack_pop(&st_path);
                current = befo;
                break;
            default:
                RoboCAR_AllMotor_Control(FORWARD, 50);
                break;
		}// end switch
	}//end while

	RoboCAR_AllMotor_Control(STOP,0);

	user_uart1_close();
	close_keyboard() ;

	return 0;
}


