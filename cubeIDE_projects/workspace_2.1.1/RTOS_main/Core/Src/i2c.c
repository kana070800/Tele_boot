
//#include "main.h"
//#include "stm32f4xx.h"
//#include "uart.h"
//
//#define INA3221_addr	(0x41)
//
//#define INA3221_Config	(0)
//#define INA3221_Shunt1	(1)
//#define INA3221_Bus1	(2)
//#define INA3221_Shunt2	(3)
//#define INA3221_Bus2	(4)
//#define INA3221_Shunt3	(5)
//#define INA3221_Bus3	(6)
//
//#define INA226_addr		(0x40)
//#define INA226_Config	(0)
//#define INA226_Shunt	(1)
//#define INA226_Bus		(2)
//#define INA226_Power    (3)
//#define INA226_Cali     (5)
//
//typedef enum {
//	I2C_IDLE,
//
//	I2C_SEND_REG8_1,
//    I2C_SEND_REG8_high,
//	I2C_SEND_REG8_low,
//	I2C_SEND_REG8_2,
//
//	I2C_SET_REG,
//    I2C_READ_DATA,
//	I2C_READ_DATA_H,
//	I2C_READ_DATA_L
//} I2C_State;
//
//typedef struct {
//    uint8_t slave_addr;
//    uint8_t reg_addr;
//    uint8_t data_h;
//    uint8_t data_l;
//    uint8_t set_regs;
//    I2C_State state;
//} I2C_Handle;
//
//static volatile I2C_Handle h_I2C1; // 이 파일 전용 전역 변수
//static uint8_t read_end = 0;
//
//extern uint8_t data_H;
//extern uint8_t data_L;
//
//
//void I2C1_init(void)
//{
//	//gpio init
//    // RCC GPIOB clk enable
//    RCC->AHB1ENR |= (0x1UL << 1) ;
//
//    // gpio pin for i2c1(PB7, PB8) set
//    GPIOB->MODER &= ~((3 << (9 * 2)) | (3 << (8 * 2)));  //Alternate function mode
//    GPIOB->MODER |= ((2 << (9 * 2)) | (2 << (8 * 2)));
//    GPIOB->OTYPER |= (1 << 9) | (1 << 8);                //open drain
//    GPIOB->AFR[1] &= ~(0xF << ((9 - 8) * 4));     //PB7 pin AF
//    GPIOB->AFR[1] |= (4 << ((9 - 8) * 4));
//    GPIOB->AFR[1] &= ~(0xF << ((8 - 8) * 4));  //PB8 pin AF
//    GPIOB->AFR[1] |= (4 << ((8 - 8) * 4));
//
//	//i2c1 init
//    RCC->APB1ENR |= (0x1UL << 21); //i2c1 clk enable
//    I2C1->CR1 |= (0x1UL << 15);    //reset
//    I2C1->CR1 &= ~(0x1UL << 15);   //reset end
//
//    // APB1 = 42MHz, interrupt enable
//    I2C1->CR2 |= (0x1UL << 10)|(0x1UL << 9)|(42 << 0);
//
//    I2C1->CCR |= 210; // for 100kHz scl in APB1 = 42MHz
//    I2C1->TRISE |= 43;
//    I2C1->CR1 |= (0x1UL << 0); //i2c1 enable
//}
//
//void I2C1_write(int sensor,uint8_t reg,uint16_t data)
//{
//	while (h_I2C1.state != I2C_IDLE) {};
//	//set values
//	if (sensor == 3221){
//		h_I2C1.slave_addr = (INA3221_addr << 1)|(0);
//	}
//	else if (sensor == 226){
//		h_I2C1.slave_addr = (INA226_addr << 1)|(0);
//	}
//	else{
//		UART3_Printf("sensor number error");
//		return;
//	}
//	h_I2C1.reg_addr = reg;
//	h_I2C1.data_h = (uint8_t)(data >> 8);
//	h_I2C1.data_l = (uint8_t)(data);
//	h_I2C1.state = I2C_SEND_REG8_1;
//
//	//write sequence
//	I2C1->CR1 |= (1 << 8); //start generation
//}
//
//
//void __I2C1_read(int sensor)
//{
//	while(h_I2C1.set_regs){};
//
//	//set values
//	if (sensor == 3221){
//		h_I2C1.slave_addr = (INA3221_addr << 1)|(1);
//	}
//	else if (sensor == 226){
//		h_I2C1.slave_addr = (INA226_addr << 1)|(1);
//	}
//	else{
//		UART3_Printf("sensor number error");
//		return;
//	}
//	h_I2C1.data_h = 0;
//	h_I2C1.data_l = 0;
//	h_I2C1.state = I2C_READ_DATA;
//	I2C1->CR1 |= (1 << 8); //start generation
//
//	while(read_end){};
//}
//
//void I2C1_read(int sensor, uint8_t reg)
//{
//	read_end = 1;
//	while (h_I2C1.state != I2C_IDLE) {};
//	//set values
//	if (sensor == 3221){
//		h_I2C1.slave_addr = (INA3221_addr << 1)|(0);
//	}
//	else if (sensor == 226){
//		h_I2C1.slave_addr = (INA226_addr << 1)|(0);
//		}
//	else{
//		UART3_Printf("sensor number error");
//		return;
//	}
//	h_I2C1.reg_addr = reg;
//	h_I2C1.data_h = 0;
//	h_I2C1.data_l = 0;
//	h_I2C1.state = I2C_SET_REG;
//	h_I2C1.set_regs = 1; //for sync
//
//	//set register pointer sequence
//	I2C1->CR1 |= (1 << 8); //start generation
//	__I2C1_read(sensor);
//}
//
////----------------------------- init
//
//void init_ina3221(void)
//{
//	I2C1_write(3221, INA3221_Config, 0x7727);
//}
//
//void init_ina226(void)
//{
//	I2C1_write(226, INA226_Config, 0x2727);
//	I2C1_write(226, INA226_Cali, 168); //set cali
//}
//
////-----------------------handler
//
//void I2C1_EV_IRQHandler(void)
//{
//	//start, stop, txe, rxne, addr
//	uint32_t sr1 = I2C1->SR1;
//
//	// start condition = EV5
//	if (sr1 & I2C_SR1_SB) {
//		I2C1->DR = h_I2C1.slave_addr;
//		return;
//	}
//	// addr condition = EV6
//	if (sr1 & I2C_SR1_ADDR)
//	{
//		if (h_I2C1.state == I2C_READ_DATA)
//		{
//			h_I2C1.state = I2C_READ_DATA_H;
//			I2C1->CR1 |= (1 << 10); // ACK set++++++++++++++++++++++++++++
//		}
//		sr1 = I2C1->SR2; //clear ADDR (read SR2)
//		return;
//	}
//
//	// txe condition = EV8_1, EV8, EV8_2
//	if (sr1 & I2C_SR1_TXE)
//	{
//		//UART3_Printf("TXE %d\n", h_I2C1.state);
//		switch (h_I2C1.state){
//			case I2C_SEND_REG8_1:
//				I2C1->DR = h_I2C1.reg_addr;
//				h_I2C1.state = I2C_SEND_REG8_high;
//				break;
//			case I2C_SEND_REG8_high:
//				I2C1->DR = h_I2C1.data_h;
//				h_I2C1.state = I2C_SEND_REG8_low;
//				break;
//			case I2C_SEND_REG8_low:
//				I2C1->DR = h_I2C1.data_l;
//				h_I2C1.state = I2C_SEND_REG8_2;
//				break;
//			case I2C_SEND_REG8_2: //end if transmit
//				// btf condition = EV8_2
//
//				I2C1->CR1 |= (1 << 9);// stop request
//				h_I2C1.set_regs = 0;
//				h_I2C1.state = I2C_IDLE;
//				break;
//
//			case I2C_SET_REG: //register pointer setting (before read)
//				I2C1->DR = h_I2C1.reg_addr;
//				h_I2C1.state = I2C_SEND_REG8_2;
//				break;
//
//		}
//		return;
//	}
//
//	if (sr1 & I2C_SR1_RXNE){
//		switch (h_I2C1.state){
//			case I2C_READ_DATA_H: //EV7_1
//				data_H = I2C1->DR;
//				I2C1->CR1 &= ~(1 << 10); // NACK send
//				I2C1->CR1 |= (1 << 9);   // STOP
//				h_I2C1.state = I2C_READ_DATA_L;
//				break;
//			case I2C_READ_DATA_L: //EV7
//				data_L = I2C1->DR;
//				h_I2C1.state = I2C_IDLE;
//				read_end = 0;
//				break;
//			default:
//				UART3_Printf("RXNE warning");
//		}
//		return;
//	}
//
//	return;
//}

#include "main.h"
#include "stm32f4xx.h"
#include "uart.h"
#include "string.h"
#include "cmsis_os.h"

#define INA3221_addr	(0x41)

#define INA3221_Config	(0)
#define INA3221_Shunt1	(1)
#define INA3221_Bus1	(2)
#define INA3221_Shunt2	(3)
#define INA3221_Bus2	(4)
#define INA3221_Shunt3	(5)
#define INA3221_Bus3	(6)

#define INA226_addr		(0x40)

#define INA226_Config	(0)
#define INA226_Shunt	(1)
#define INA226_Bus		(2)
#define INA226_Power    (3)
#define INA226_Cali     (5)

typedef enum {

	I2C_IDLE,

	I2C_SEND_REG8_1,
    I2C_SEND_REG8_high,
	I2C_SEND_REG8_low,
	I2C_SEND_REG8_2,

	I2C_SET_REG,
    I2C_READ_DATA,
	I2C_READ_DATA_H,
	I2C_READ_DATA_L
} I2C_State;

typedef struct {
    uint8_t slave_addr;
    uint8_t reg_addr;
    uint8_t data_h;
    uint8_t data_l;
    uint8_t set_regs;
    I2C_State state;
} I2C_Handle;

static int g_i2c_bus_error_flag = 0;

static volatile I2C_Handle h_I2C1; // 이 파일 전용 전역 변수

static uint8_t data_H;
static uint8_t data_L;


void I2C1_init(void)
{
	//gpio init
    // RCC GPIOB clk enable
    RCC->AHB1ENR |= (0x1UL << 1) ;

    // gpio pin for i2c1(PB7, PB8) set
    GPIOB->MODER &= ~((3 << (9 * 2)) | (3 << (8 * 2)));  //Alternate function mode
    GPIOB->MODER |= ((2 << (9 * 2)) | (2 << (8 * 2)));
    GPIOB->OTYPER |= (1 << 9) | (1 << 8);                //open drain
    GPIOB->AFR[1] &= ~(0xF << ((9 - 8) * 4));     //PB7 pin AF
    GPIOB->AFR[1] |= (4 << ((9 - 8) * 4));
    GPIOB->AFR[1] &= ~(0xF << ((8 - 8) * 4));  //PB8 pin AF
    GPIOB->AFR[1] |= (4 << ((8 - 8) * 4));

	//i2c1 init
    RCC->APB1ENR |= (0x1UL << 21); //i2c1 clk enable
    I2C1->CR1 |= (0x1UL << 15);    //reset
    I2C1->CR1 &= ~(0x1UL << 15);   //reset end

    // APB1 = 42MHz, interrupt enable
    I2C1->CR2 |= (0x1UL << 10)|(0x1UL << 9)|(42 << 0);

    I2C1->CR2 |= I2C_CR2_ITERREN; //error

    I2C1->CCR |= 210; // for 100kHz scl in APB1 = 42MHz
    I2C1->TRISE |= 43;
    I2C1->CR1 |= (0x1UL << 0); //i2c1 enable
}

void I2C1_write(int sensor,uint8_t reg,uint16_t data)
{
	while (h_I2C1.state != I2C_IDLE) {};
	//set values
	if (sensor == 3221)
		h_I2C1.slave_addr = (INA3221_addr << 1)|(0);
	else if (sensor == 226)
		h_I2C1.slave_addr = (INA226_addr << 1)|(0);
	else{
		return;
	}

	h_I2C1.reg_addr = reg;
	h_I2C1.data_h = (uint8_t)(data >> 8);
	h_I2C1.data_l = (uint8_t)(data);
	h_I2C1.state = I2C_SEND_REG8_1;

	//write sequence
	I2C1->CR1 |= (1 << 8); //start generation
}

void __I2C1_read(int sensor)
{
	while(h_I2C1.set_regs){};

	//set values
	if (sensor == 3221)
		h_I2C1.slave_addr = (INA3221_addr << 1)|(1);
	else
		h_I2C1.slave_addr = (INA226_addr << 1)|(1);
	h_I2C1.data_h = 0;
	h_I2C1.data_l = 0;
	h_I2C1.state = I2C_READ_DATA;
	I2C1->CR1 |= (1 << 8); //start generation
}

int16_t I2C1_read(int sensor, uint8_t reg)
{
	while (h_I2C1.state != I2C_IDLE) {};
	//set values
	if (sensor == 3221)
		h_I2C1.slave_addr = (INA3221_addr << 1)|(0);
	else if (sensor == 226)
		h_I2C1.slave_addr = (INA226_addr << 1)|(0);
	else
		return -1;
	h_I2C1.reg_addr = reg;
	h_I2C1.data_h = 0;
	h_I2C1.data_l = 0;
	h_I2C1.state = I2C_SET_REG;
	h_I2C1.set_regs = 1; //for sync

	//set register pointer sequence
	I2C1->CR1 |= (1 << 8); //start generation
	__I2C1_read(sensor);

	while (h_I2C1.state != I2C_IDLE) {}; //wait read
	return (data_H << 8)|(data_L);

}

//----------------------------- init

void init_ina3221(void)
{
	I2C1_write(3221, INA3221_Config, 0x7327);
}

void init_ina226(void)
{
	I2C1_write(226, INA226_Config, 0x2327);
	I2C1_write(226, INA226_Cali, 168); //set cali
}

//-----------------------handler

void I2C1_EV_IRQHandler(void)
{
	//start, stop, txe, rxne, addr
	uint32_t sr1 = I2C1->SR1;

	// start condition = EV5
	if (sr1 & I2C_SR1_SB) {
		//UART3_Printf("S %d\n", h_I2C1.state);
		I2C1->DR = h_I2C1.slave_addr;
		return;
	}
	// addr condition = EV6
	if (sr1 & I2C_SR1_ADDR)
	{
		if (h_I2C1.state == I2C_READ_DATA)
		{
			h_I2C1.state = I2C_READ_DATA_H;
			I2C1->CR1 |= (1 << 10); // ACK set++++++++++++++++++++++++++++
		}
		//UART3_Printf("add %d\n", h_I2C1.state);
		sr1 = I2C1->SR2; //clear ADDR
		return;
	}

	// txe condition = EV8_1, EV8, EV8_2
	if (sr1 & I2C_SR1_TXE)
	{
		//UART3_Printf("TXE %d\n", h_I2C1.state);
		switch (h_I2C1.state){
			case I2C_SEND_REG8_1:
				I2C1->DR = h_I2C1.reg_addr;
				h_I2C1.state = I2C_SEND_REG8_high;
				break;
			case I2C_SEND_REG8_high:
				I2C1->DR = h_I2C1.data_h;
				h_I2C1.state = I2C_SEND_REG8_low;
				break;
			case I2C_SEND_REG8_low:
				I2C1->DR = h_I2C1.data_l;
				h_I2C1.state = I2C_SEND_REG8_2;
				break;
			case I2C_SEND_REG8_2: //end if transmit
				// btf condition = EV8_2

				I2C1->CR1 |= (1 << 9);// stop request
				h_I2C1.set_regs = 0;
				h_I2C1.state = I2C_IDLE;
				break;

			case I2C_SET_REG: //register pointer setting (before read)
				I2C1->DR = h_I2C1.reg_addr;
				h_I2C1.state = I2C_SEND_REG8_2;
				break;
		}
		return;
	}

	if (sr1 & I2C_SR1_RXNE){
		switch (h_I2C1.state){
			case I2C_READ_DATA_H: //EV7_1
				data_H = I2C1->DR;
				I2C1->CR1 &= ~(1 << 10); // NACK send
				I2C1->CR1 |= (1 << 9);   // STOP
				h_I2C1.state = I2C_READ_DATA_L;
				break;
			case I2C_READ_DATA_L: //EV7
				data_L = I2C1->DR;
				h_I2C1.state = I2C_IDLE;
				break;
		}
		return;
	}

	return;
}

// I2C1 에러 인터럽트 핸들러 (이름은 MCU startup 파일의 벡터 테이블 참조)
void I2C1_ER_IRQHandler(void) {
    uint32_t sr1 = I2C1->SR1;

    // 1. AF (Acknowledge Failure) - 가장 흔함! 배선 단선 또는 주소/데이터 NACK
    if (sr1 & I2C_SR1_AF) {
        I2C1->SR1 &= ~I2C_SR1_AF; // 플래그 클리어
        I2C1->CR1 |= I2C_CR1_STOP; // STOP 신호 전송하여 통신 종료
    }

    // 2. BERR (Bus Error) - 통신 중 배선이 흔들려 불법적인 START/STOP 발생 시
    if (sr1 & I2C_SR1_BERR) {
        I2C1->SR1 &= ~I2C_SR1_BERR;
    }

    // 3. ARLO (Arbitration Lost) - 버스 충돌 또는 노이즈로 인한 라인 제어권 상실
    if (sr1 & I2C_SR1_ARLO) {
        I2C1->SR1 &= ~I2C_SR1_ARLO;
    }

    // 4. OVR (Overrun/Underrun) - 데이터 수신 속도를 소프트웨어가 따라가지 못할 때
    if (sr1 & I2C_SR1_OVR) {
        I2C1->SR1 &= ~I2C_SR1_OVR;
    }

    // 🟢 인터럽트 발생 시 통신을 중단하고 소프트웨어 리셋 및 복구 플래그 설정
    // RTOS를 사용 중이시라면 여기서 전역 플래그를 세팅하거나 세마포어를 주어
    // Task에서 I2C_Bus_Recovery()를 안전하게 호출하도록 유도합니다.
    g_i2c_bus_error_flag = 1;
}


void Current_Task(void *argument)
{
  /* USER CODE BEGIN 5 */
	I2C1_init();
	//init_ina3221();
	init_ina226();
  /* Infinite loop */
	for(;;)
	{
		UART3_Printf("start loop \n");
		if (g_i2c_bus_error_flag) {
		    I2C1_init();      //초기화
		    //init_ina3221();
		    init_ina226();
		    g_i2c_bus_error_flag = 0;
		    continue;                // 이번 루프는 건너뛰고 다음 주기에 재시도
		}

		// ==========================================================
		// 1. INA3221
		// ==========================================================
		// 상위 13비트만 유효 >> 3
//		int16_t bus3221_raw   = (int16_t)I2C1_read(3221, INA3221_Bus1) >> 3;
//		int16_t shunt3221_raw = (int16_t)I2C1_read(3221, INA3221_Shunt1) >> 3;
//
//		UART3_Printf("ina3221 shunt1 raw : %d\n", shunt3221_raw);
//		UART3_Printf("ina3221 bus1 raw   : %d\n", bus3221_raw);
//
//		// Bus 단위 = 8mV
//		int32_t bus3221_mv = bus3221_raw * 8;
//
//		// Shunt 단위 = 40uV (0.04mV). 전류(mA) = (raw * 40uV) === 0.1옴 = (raw * 4) / 10 mA
//		int32_t current3221_ma = (shunt3221_raw * 4) / 10; // 0.1옴 기준 mA 단위
//
//		int32_t power3221_mw = (bus3221_mv * current3221_ma) / 1000;
//
//		UART3_Printf("INA3221 -> Bus: %ld mV | Cur: %ld mA | Power: %ld mW\n", bus3221_mv, current3221_ma, power3221_mw);

		// ==========================================================
		// 2. INA226
		// ==========================================================
		int16_t bus226_raw   = (int16_t)I2C1_read(226, INA226_Bus);
		int16_t shunt226_raw = (int16_t)I2C1_read(226, INA226_Shunt);
		int16_t power226_raw = (int16_t)I2C1_read(226, INA226_Power);

		UART3_Printf("ina226 shunt raw : %d\n", shunt226_raw);
		UART3_Printf("ina226 bus raw   : %d\n", bus226_raw);

		// Bus 단위 = 1.25mV
		int32_t bus226_mv = (bus226_raw * 125) / 100;

		// Shunt 단위 = 2.5uV. 전류(mA) = (raw * 2.5uV) === 0.1옴 = (raw * 25) / 1000 mA
		int32_t current226_ma = (shunt226_raw * 25) / 1000;

		// 전력 계산 (연산 vs Power 레지스터 읽기)
		int32_t power226_calc_mw = (bus226_mv * current226_ma) / 1000;
		int32_t power226_reg_mw  = (int32_t)(power226_raw * 7.619);

		UART3_Printf("INA226  -> Bus: %ld mV | Cur: %ld mA | Calc Power: %ld mW\n", bus226_mv, current226_ma, power226_calc_mw); // 연산
		UART3_Printf("INA226 Reg Power: %ld mW\n", power226_reg_mw); // 레지스터 연산과 비교
		UART3_Printf("end loop\n");
		for (volatile int i = 0; i < 5000000; i++){};
	}
  /* USER CODE END 5 */
}




void Current_init(void){
	BaseType_t ret = xTaskCreate(Current_Task, "current sensor", 128*4,NULL, osPriorityNormal,NULL);
	if (ret != pdPASS){
		UART3_Printf("end loop\n");
		return;
	}
}
