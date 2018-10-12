/***********************************************************
*  Author: zsr
*  Date: 2018_09_25
***********************************************************/
#ifndef SLINK_MAIN_2018_H
#define SLINK_MAIN_2018_H


#ifdef __cplusplus
extern "C" {
#endif

   #define   SLINK_FILE_SYSTEM     0       /// 硬件平台是否包含 文件系统              
   #if (SLINK_FILE_SYSTEM == 1)

        

   #endif 






/*----------------------------------------------------------------------

                           <打印接口>

windows/linux :   printf
non-os        :   uart_log_send
free-rtos     :   printf

------------------------------------------------------------------------*/


extern void slink_printf_log(char * format,char *log_str);
extern void slink_printf_error(char * format,char *error_str);
extern void slink_printf_warring(char * format,char *warring_str);




/*----------------------------------------------------------------------

                           <数学接口>

1.针对各种硬件平台  提供常用运算操作

------------------------------------------------------------------------*/


extern int   slink_atoi(char *str);
extern char* slink_itoa(int value_int);


/*----------------------------------------------------------------------

                           <字符串操作接口>

1.针对各种硬件平台  提供常用字符操作库

------------------------------------------------------------------------*/

extern char slink_strcmp(char *str1,char *str2);
extern char slilnk_strcpy(char *des_str,char *res_str);



/*----------------------------------------------------------------------

                           <文件接口>

1.针对各种硬件平台  提供常用字符操作库

------------------------------------------------------------------------*/


typedef struct{

    char *path;
	char state;
	

}slink_flie;

extern char slink_create(char *file_name ,char * path);
extern int  zlink_file_write(char *slink_flie,char* str);
extern int  slink_file_read(char *slink_flie,char* str);
extern char * slink_file_getInf();


/*----------------------------------------------------------------------

                           <线程接口>

1.针对各种硬件平台  提供常用字符操作库

------------------------------------------------------------------------*/

typedef struct{

   char state;     // 0 : free   1 : run   2: wait  3 : sleep
   int  ID;        
   char name[24];
   
   int  stack_size;    
   char priority;
   void *thead_cb;
   
}slink_thread;

//extern slink_thread  slink_thread_new(char *name,int stack_size,char priority,slink_thead_cb slink_thead_cb_);
extern char slink_thread_run(slink_thread slink_thread_);
extern char slink_thread_sleep(slink_thread slink_thread_);
extern char slink_thread_kill(slink_thread slink_thread_);

extern char* slink_thread_getInf();


/*----------------------------------------------------------------------

                           <IOT接口>

1.针对各种硬件平台  提供常用字符操作库

------------------------------------------------------------------------*/

extern char slink_start_smartLink(char link_mode);
extern char slink_link_getState();
extern char slink_link_stop();


extern void slink_link_Init_udp_(int udp);
extern char slink_register_udp_broadcast_recv_cb();
extern char slink_link_udp_broadcast_send(char *str,int len,int server_port);


/*以下根据不同的云端进行定制*/
extern char slink_link_send_str_to_tuya(char *str,int len);
extern char slink_link_register_tuya_recv_cb(char *str,int rec_len);






#ifdef __cplusplus
}
#endif
#endif



