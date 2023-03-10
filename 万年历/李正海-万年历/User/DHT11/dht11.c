#include "dht11.h"
#include "delay.h"

/*-----------------------------------------------------------------------
DHT11_Rst  			 							  : 复位DHT11
																									 
	
输入参数                   			： 
                                  

-----------------------------------------------------------------------*/
void DHT11_Rst(void)	   
{                 
	DHT11_IO_OUT(); 	                                                          // SET OUTPUT
  DHT11_DQ_OUT=0; 	                                                          // 拉低DQ
  delay_ms(20);    	                                                          // 拉低至少18ms
  DHT11_DQ_OUT=1; 	                                                          // DQ=1 
	delay_us(30);     	                                                        // 主机拉高20~40us
}

/*-----------------------------------------------------------------------
DHT11_Check  			 						  : 等待DHT11的回应
																									 
	
输入参数                   			：返回1:未检测到DHT11的存在 返回0:存在
                                  

-----------------------------------------------------------------------*/
uint8_t DHT11_Check(void) 	   
{   
	uint8_t retry=0;
	DHT11_IO_IN();                                                              // SET INPUT	 
  while (DHT11_DQ_IN&&retry<100)                                              // DHT11会拉低40~80us
	{
		retry++;
		delay_us(1);
	};	 
	if(retry>=100)return 1;
	else retry=0;
  while (!DHT11_DQ_IN&&retry<100)                                             // DHT11拉低后会再次拉高40~80us
	{
		retry++;
		delay_us(1);
	};
	if(retry>=100)return 1;	    
	return 0;
}
 
/*-----------------------------------------------------------------------
DHT11_Read_Bit  			 				  : 从DHT11读取一个位
																									 
	
输入参数                   			： 
                                  

-----------------------------------------------------------------------*/
uint8_t DHT11_Read_Bit(void) 			 
{
 	uint8_t retry=0;
	while(DHT11_DQ_IN&&retry<100)                                               // 等待变为低电平
	{
		retry++;
		delay_us(1);
	}
	retry=0;
	while(!DHT11_DQ_IN&&retry<100)                                              // 等待变高电平
	{
		retry++;
		delay_us(1);
	}
	delay_us(40);                                                               // 等待40us
	if(DHT11_DQ_IN)return 1;
	else return 0;		   
}
 
/*-----------------------------------------------------------------------
DHT11_Read_Byte  			 				  : 从DHT11读取一个字节
																									 
	
输入参数                   			：到的数据
                                  

-----------------------------------------------------------------------*/
uint8_t DHT11_Read_Byte(void)    
{        
    uint8_t i,dat;
    dat=0;
	for (i=0;i<8;i++) 
	{
   		dat<<=1; 
	    dat|=DHT11_Read_Bit();
    }						    
    return dat;
}
 
/*-----------------------------------------------------------------------
DHT11_Read_Data  			 				  : 从DHT11读取一次数据
																									 
	
输入参数                   			：temp:温度值(范围:0~50°)humi:湿度值(范围:20%~90%)返回值：0,正常;1,读取失败
                                  

-----------------------------------------------------------------------*/
uint8_t DHT11_Read_Data(uint8_t *temph,uint8_t *templ,uint8_t *humih,uint8_t *humil,uint8_t * Val)    
{ 	
 	uint8_t buf[5];
	uint8_t i;
	DHT11_Rst();
	if(DHT11_Check()==0)
	{
		for(i=0;i<5;i++)                                                          // 读取40位数据
		{
			buf[i]=DHT11_Read_Byte();
		}
		if((buf[0]+buf[1]+buf[2]+buf[3])==buf[4])
		{
			*humih=buf[0];
			*humil=buf[1];
			
			*temph=buf[2];
			*templ=buf[3];
		}
		
		if((buf[1] & 0x80) == 0)      // 温度>0
		{
			*Val = 0;
		}
		if((buf[1] & 0x80) == 1)      // 温度<0
		{
			*Val = 1;
		}
		
	}else return 1;
	return 0;	    
}
 
/*-----------------------------------------------------------------------
DHT11_Init      			 				  : 初始化DHT11的IO口 DQ 同时检测DHT11的存在
																									 
	
输入参数                   			：返回1:不存在  返回0:存在 
                                  

-----------------------------------------------------------------------*/
uint8_t DHT11_Init(void)
{	 
 	GPIO_InitTypeDef  GPIO_InitStructure;
 	
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	                    // 使能PG端口时钟
	
 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;				                          // PA6端口配置
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		                      //推挽输出
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);				                            //初始化IO口
 	GPIO_SetBits(GPIOA,GPIO_Pin_6);						                                // PA6 输出高
			    
	DHT11_Rst();                                                              // 复位DHT11
	return DHT11_Check();                                                     // 等待DHT11的回应
} 







