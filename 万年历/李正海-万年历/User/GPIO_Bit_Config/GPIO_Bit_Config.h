#ifndef __GPIO_Bit_Config_H
#define __GPIO_Bit_Config_H

/*-----------------------------------------------------------------------

		单独操作 GPIO的某一个IO口，n(0,1,2...16),n表示具体是哪一个IO口
		
-----------------------------------------------------------------------*/
#define GPIOA_ODR_Addr   (GPIOA_BASE+0x0C)
#define PAout(n)        *(unsigned int*)((GPIOA_ODR_Addr & 0xF0000000)+0x02000000+((GPIOA_ODR_Addr &0x00FFFFFF)<<5)+(n<<2)) //输出
#define GPIOA_IDR_Addr   (GPIOA_BASE+0x08)
#define PAin(n)         *(unsigned int*)((GPIOA_IDR_Addr & 0xF0000000)+0x02000000+((GPIOA_IDR_Addr &0x00FFFFFF)<<5)+(n<<2)) //输入
	
#define GPIOB_ODR_Addr   (GPIOB_BASE+0x0C)
#define PBout(n)        *(unsigned int*)((GPIOB_ODR_Addr & 0xF0000000)+0x02000000+((GPIOB_ODR_Addr &0x00FFFFFF)<<5)+(n<<2)) //输出
#define GPIOB_IDR_Addr   (GPIOB_BASE+0x08)
#define PBin(n)         *(unsigned int*)((GPIOB_IDR_Addr & 0xF0000000)+0x02000000+((GPIOB_IDR_Addr &0x00FFFFFF)<<5)+(n<<2)) //输入

#define GPIOC_ODR_Addr   (GPIOC_BASE+0x0C)
#define PCout(n)        *(unsigned int*)((GPIOC_ODR_Addr & 0xF0000000)+0x02000000+((GPIOC_ODR_Addr &0x00FFFFFF)<<5)+(n<<2)) //输出
#define GPIOC_IDR_Addr   (GPIOC_BASE+0x08)
#define PCin(n)         *(unsigned int*)((GPIOC_IDR_Addr & 0xF0000000)+0x02000000+((GPIOC_IDR_Addr &0x00FFFFFF)<<5)+(n<<2)) //输入
	
#define GPIOD_ODR_Addr   (GPIOD_BASE+0x0C)
#define PDout(n)        *(unsigned int*)((GPIOD_ODR_Addr & 0xF0000000)+0x02000000+((GPIOD_ODR_Addr &0x00FFFFFF)<<5)+(n<<2)) //输出
#define GPIOD_IDR_Addr   (GPIOD_BASE+0x08)
#define PDin(n)         *(unsigned int*)((GPIOD_IDR_Addr & 0xF0000000)+0x02000000+((GPIOD_IDR_Addr &0x00FFFFFF)<<5)+(n<<2)) //输入

#define GPIOE_ODR_Addr   (GPIOE_BASE+0x0C)
#define PEout(n)        *(unsigned int*)((GPIOE_ODR_Addr & 0xF0000000)+0x02000000+((GPIOE_ODR_Addr &0x00FFFFFF)<<5)+(n<<2)) //输出
#define GPIOE_IDR_Addr   (GPIOE_BASE+0x08) 
#define PEin(n)         *(unsigned int*)((GPIOE_IDR_Addr & 0xF0000000)+0x02000000+((GPIOE_IDR_Addr &0x00FFFFFF)<<5)+(n<<2)) //输入
	
#define GPIOF_ODR_Addr   (GPIOF_BASE+0x0C)
#define PFout(n)        *(unsigned int*)((GPIOF_ODR_Addr & 0xF0000000)+0x02000000+((GPIOF_ODR_Addr &0x00FFFFFF)<<5)+(n<<2)) //输出
#define GPIOF_IDR_Addr   (GPIOF_BASE+0x08)
#define PFin(n)         *(unsigned int*)((GPIOF_IDR_Addr & 0xF0000000)+0x02000000+((GPIOF_IDR_Addr &0x00FFFFFF)<<5)+(n<<2)) //输入
	
#define GPIOG_ODR_Addr   (GPIOG_BASE+0x0C) 
#define PGout(n)        *(unsigned int*)((GPIOG_ODR_Addr & 0xF0000000)+0x02000000+((GPIOG_ODR_Addr &0x00FFFFFF)<<5)+(n<<2)) //输出
#define GPIOG_IDR_Addr   (GPIOG_BASE+0x08)
#define PGin(n)         *(unsigned int*)((GPIOG_IDR_Addr & 0xF0000000)+0x02000000+((GPIOG_IDR_Addr &0x00FFFFFF)<<5)+(n<<2)) //输入

#endif

