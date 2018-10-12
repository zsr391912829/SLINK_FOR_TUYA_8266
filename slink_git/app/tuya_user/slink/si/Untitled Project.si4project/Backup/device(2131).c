 /***********************************************************
*  File: device.c  
*  Author: husai
*  Date: 20151215
***********************************************************/
#define __DEVICE_GLOBALS
#include "slink_lib.h"

#include "device.h"
#include "tuya_smart_api.h"
#include "slink_main.h"


/***********************************************************
*************************micro define***********************
***********************************************************/
#define SYN_TIME  2  //同步开关状态
#define ONE_SEC   1
#define WM_SUCCESS 0
#define WM_FAIL 1

#define DEVICE_MOD "device_mod"
#define DEVICE_PART "device_part"
#define APPT_POSIX_KEY "appt_posix_key"
#define POWER_STAT_KEY "power_stat_key"

#define TIME_POSIX_2016 1451577600 //2016年时间戳


// wifi direct led
#define WF_DIR_LED GPIO_ID_PIN(4)   //WiFi指示灯


/***********************************************************
*************************variable define********************
***********************************************************/
LED_HANDLE wf_light = NULL;


/***********************************************************
*************************function define***********************
***********************************************************/
//STATIC VOID key_process(INT gpio_no,PUSH_KEY_TYPE_E type,INT cnt);
STATIC VOID wfl_timer_cb(UINT timerID,PVOID pTimerArg);
STATIC OPERATE_RET device_differ_init(VOID);

/*
KEY_ENTITY_S key_tbl[] = {
    {WF_RESET_KEY,3000,key_process,0,0,0,0},
};
*/
BOOL gpio_func_test(VOID)
{
	return TRUE;
}


VOID pre_app_init(VOID)
{
     //don't add code 
}


VOID app_init(VOID)
{
   app_cfg_set(0,NULL);
   set_console(FALSE);
}

VOID set_firmware_tp(IN OUT CHAR *firm_name, IN OUT CHAR *firm_ver)
{
	strcpy(firm_name,APP_BIN_NAME);
	strcpy(firm_ver,USER_SW_VER);
	return;
}



STATIC VOID msg_send(INT cmd)
{
/*
    if(cmd == ty_msg.power) {
        msg_upload_proc(cmd);
    }else {
        PostSemaphore(ty_msg.press_key_sem);
    }*/
    
}





STATIC VOID syn_timer_cb(UINT timerID,PVOID pTimerArg)
{
    if( FALSE == tuya_get_cloud_stat() ) {
        return;
    }

    PR_DEBUG("syn timer cb ...");
}



STATIC VOID syn_active_data(VOID)
{
	//msg_upload_proc(ty_msg.power);
}

/***********************************************************
*  Function: device_init
*  Input: 
*  Output: 
*  Return: 
***********************************************************/
OPERATE_RET device_init(VOID)
{
 

    slink_main(1234,"test param");
    SLINK_LOG("fireware info name:%s version:%s",APP_BIN_NAME,USER_SW_VER);
    OPERATE_RET op_ret;


	op_ret = tuya_psm_register_module(DEVICE_MOD, DEVICE_PART);
    if(op_ret != OPRT_OK && op_ret != OPRT_PSM_E_EXIST) {
        PR_ERR("tuya_psm_register_module error:%d",op_ret);
        return op_ret;
    }



	tuya_active_reg(syn_active_data);



    op_ret = device_differ_init();
    if(op_ret != OPRT_OK) {
        return op_ret;
    }

    return op_ret;
}

/*
STATIC VOID key_process(INT gpio_no,PUSH_KEY_TYPE_E type,INT cnt)
{
    PR_DEBUG("gpio_no: %d",gpio_no);
    PR_DEBUG("type: %d",type);
    PR_DEBUG("cnt: %d",cnt);

    if(WF_RESET_KEY == gpio_no) {
        if(LONG_KEY == type) {
            tuya_dev_reset_factory();
        }else if(SEQ_KEY == type && cnt == 2) {
            ShowSysMemPoolInfo();
        }else if(NORMAL_KEY == type) {
            PostSemaphore(ty_msg.press_key_sem);
        }
    }
}
*/


STATIC OPERATE_RET device_differ_init(VOID)
{
    OPERATE_RET op_ret;

    
    // create led handle
    op_ret = tuya_create_led_handle(WF_DIR_LED,&wf_light);
    if(OPRT_OK  != op_ret) {
        return op_ret;
    }

    TIMER_ID timer;
    op_ret = sys_add_timer(wfl_timer_cb,NULL,&timer);
    if(OPRT_OK != op_ret) {
        return op_ret;
    }else {
        sys_start_timer(timer,300,TIMER_CYCLE);
    }

    return OPRT_OK;
}

STATIC VOID wfl_timer_cb(UINT timerID,PVOID pTimerArg)
{
    STATIC UINT last_wf_stat = 0xffffffff;
    GW_WIFI_STAT_E wf_stat = tuya_get_wf_status();
    
    if(last_wf_stat != wf_stat) {
        PR_DEBUG("wf_stat:%d",wf_stat);
        switch(wf_stat) {
            case STAT_UNPROVISION: {
                tuya_set_led_type(wf_light,OL_FLASH_HIGH,250);
            }
            break;
            
            case STAT_AP_STA_UNCONN:
            case STAT_AP_STA_CONN: {
                tuya_set_led_type(wf_light,OL_FLASH_HIGH,1500);
            }
            break;

			case STAT_LOW_POWER:
            case STAT_STA_UNCONN: {
                tuya_set_led_type(wf_light,OL_HIGH,0);
            }
            break;
            
            case STAT_STA_CONN: {
                tuya_set_led_type(wf_light,OL_LOW,0);
            }
            break;
        }

        last_wf_stat = wf_stat;
    }
}



