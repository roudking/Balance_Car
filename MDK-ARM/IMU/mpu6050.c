#include "mpu6050.h"

KALMAN KalmanX = {
        .Q_angle = 0.001f,
        .Q_bias = 0.003f,
        .R_measure = 0.03f
};

KALMAN KalmanY = {
        .Q_angle = 0.001f,
        .Q_bias = 0.003f,
        .R_measure = 0.03f,
};


void Mpu_creat(MPU *mpu,MPU_CONFIG config_struct,KALMAN Kalmanx,KALMAN Kalmany)
{
   mpu->config = config_struct;
	 mpu->kalmanx = Kalmanx;
	 mpu->kalmany = Kalmany;
}


int Mpu_test_who_am_i(MPU *mpu)
{
    mpu_iicgetdata(mpu->config,MPU_DEVICE_ID_REG,&(mpu->config.Who_am_I_ID),1);
	   return mpu->config.Who_am_I_ID;
}

void Mpu_init(MPU *mpu)
{
	  while(Mpu_test_who_am_i(mpu) != 0x68);
	
		  uint8_t c = 0x80;
	  mpu_iicsend(mpu->config, PWR_MGMT_1,   &c, 1);  // 电源管理寄存器
		Debugger_printf("MPU Init Success\n");
		  delay_ms(1000);

		mpu_iicsend(mpu->config, PWR_MGMT_1,   &(mpu_config.clock_config), 1);  // 电源管理寄存器
	    mpu_iicsend(mpu->config, MPU_CFG_REG,  &(mpu_config.DLFP_Config),  1);   // 配置寄存器
        mpu_iicsend(mpu->config, MPU_SAMPLE_RATE_REG,&(mpu_config.samping_rate),1) ;// 采样率分频器寄存器
	    mpu_iicsend(mpu->config, GYRO_CONFIG,  &(mpu_config.gyro_config),  1);  // 陀螺仪配置寄存器
	    mpu_iicsend(mpu->config, ACCEL_CONFIG, &(mpu_config.accel_config), 1);  // 加速度计配置寄存器
        mpu_iicsend(mpu->config, MPU_INTBP_CFG_REG, &(mpu_config.intpin_config), 1);  // 中断引脚配置寄存器
        mpu_iicsend(mpu->config, MPU_INT_EN_REG,   &(mpu_config.inten_config), 1);  // 中断使能寄存器
  

}

uint8_t Mpu_clearinterrupt(MPU *mpu)
{
    uint8_t buf;
    // 读取中断状态寄存器，清除中断标志
    mpu_iicgetdata(mpu->config, MPU_INT_STA_REG, &buf, 1);
    return buf;
}

static void Mpu_getdata_original(MPU_RAW *mpu_raw,MPU_CONFIG config)
{
    uint8_t buf[14];
    // �� ACCEL_XOUT_H ��ʼ�������� 14 �ֽ�
    mpu_iicgetdata(config,ACCEL_XOUT_H, buf, 14);

    // �ߵ��ֽ���װ
    mpu_raw->accel_x = (int16_t)((buf[0] << 8) | buf[1]);
    mpu_raw->accel_y = (int16_t)((buf[2] << 8) | buf[3]);
    mpu_raw->accel_z = (int16_t)((buf[4] << 8) | buf[5]);
    mpu_raw->gyro_x  = (int16_t)((buf[8] << 8) | buf[9]);
    mpu_raw->gyro_y  = (int16_t)((buf[10]<< 8) | buf[11]);
    mpu_raw->gyro_z  = (int16_t)((buf[12]<< 8) | buf[13]);
}

// ���̶�Ӧ�ķ�ĸ�������� ��2 g �� ��2000 ��/s��
const float accel_sens = 16384.0f;
const float gyro_sens  = 16.4f;



static void Mpu_convert_raw_to_data(MPU_DATA *mpu_data,MPU_RAW *mpu_raw)
{
    mpu_data->ax = (float)mpu_raw->accel_x / accel_sens;
    mpu_data->ay = (float)mpu_raw->accel_y / accel_sens;
    mpu_data->az = (float)mpu_raw->accel_z / accel_sens;

    mpu_data->gx = (float)mpu_raw->gyro_x / gyro_sens;
    mpu_data->gy = (float)mpu_raw->gyro_y / gyro_sens;
    mpu_data->gz = (float)mpu_raw->gyro_z / gyro_sens;
}

void Mpu_getdata(MPU *mpu) 
{
	  Mpu_getdata_original(&(mpu->mpu_raw),mpu->config);
    Mpu_convert_raw_to_data(&(mpu->mpu_data),&(mpu->mpu_raw));
}


#define RAD_TO_DEG 57.295779513082320876798154814105
static float Kalman_getAngle(KALMAN *Kalman, float newAngle, float newRate, float dt) {
    float rate = newRate - Kalman->bias;
    Kalman->angle += dt * rate;

    Kalman->P[0][0] += dt * (dt * Kalman->P[1][1] - Kalman->P[0][1] - Kalman->P[1][0] + Kalman->Q_angle);
    Kalman->P[0][1] -= dt * Kalman->P[1][1];
    Kalman->P[1][0] -= dt * Kalman->P[1][1];
    Kalman->P[1][1] += Kalman->Q_bias * dt;

    float S = Kalman->P[0][0] + Kalman->R_measure;
    float K[2];
    K[0] = Kalman->P[0][0] / S;
    K[1] = Kalman->P[1][0] / S;

    float y = newAngle - Kalman->angle;
    Kalman->angle += K[0] * y;
    Kalman->bias += K[1] * y;

    float P00_temp = Kalman->P[0][0];
    float P01_temp = Kalman->P[0][1];

    Kalman->P[0][0] -= K[0] * P00_temp;
    Kalman->P[0][1] -= K[0] * P01_temp;
    Kalman->P[1][0] -= K[1] * P00_temp;
    Kalman->P[1][1] -= K[1] * P01_temp;

    return Kalman->angle;
};


//TODO: kalmen计算帧率动态可调

static uint32_t mpu_timer = 0;
#define RAD_TO_DEG 57.295779513082320876798154814105
double timer = 0.0;

void Mpu_getKalmandata(MPU *mpu){
    uint8_t Rec_Data[14];
    int16_t temp;

    // Read 14 BYTES of data starting from ACCEL_XOUT_H register
    Mpu_getdata_original(&(mpu->mpu_raw),mpu->config);
    Mpu_convert_raw_to_data(&(mpu->mpu_data),&(mpu->mpu_raw));

        // Kalman angle solve
    double dt = (double) (HAL_GetTick() - timer) / 1000;
    timer = HAL_GetTick();

    // 4.2 ���ٶȼ�˲ʱ Roll/Pitch ����
    float roll_sqrt = sqrt(
        mpu->mpu_raw.accel_x * mpu->mpu_raw.accel_x +
        mpu->mpu_raw.accel_z * mpu->mpu_raw.accel_z);
    float roll  = (roll_sqrt > 0.0)
                   ? atan((float)mpu->mpu_raw.accel_y / roll_sqrt) * RAD_TO_DEG
                   : 0.0;
    float pitch = atan2(
                       -(float)mpu->mpu_raw.accel_x,
                       (float)mpu->mpu_raw.accel_z
                   ) * RAD_TO_DEG;

    if ((pitch < -90.0 && mpu->roll > 90.0) ||
        (pitch >  90.0 && mpu->roll < -90.0))
    {
        mpu->kalmany.angle       = pitch;
        mpu->roll   = pitch;
    }
    else
    {
        mpu->roll = Kalman_getAngle(
            &(mpu->kalmany),
            pitch,
            mpu->mpu_data.gy,
            dt
        );
    }

    if (fabs(mpu->roll) > 90.0)
        mpu->mpu_data.gx = -mpu->mpu_data.gx;

    mpu->pitch = Kalman_getAngle(
        &(mpu->kalmanx),
        roll,
        mpu->mpu_data.gy,
        dt
    );
}


