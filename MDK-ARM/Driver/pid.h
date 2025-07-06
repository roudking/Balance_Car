#ifndef _PID_H
#define _PID_H

#include "math.h"

typedef struct
{
	double kp;
	double ki;
	double kd;
	double last_bias;
	double integral;
	double outvalue;
	double last_outvalue;
	double out_xianfu;
	double integrate_xianfu;
}PID;


//PID相关数学函数
  //限幅函数
double xianfu(double value, double min, double max);

//暴露微分
double position_divAPI_PID_Cal(double targetvalue,double currentvalue,double current_div,PID* pid);
// 位置式 PID 计算函数（带输出限幅和积分抗饱和）
double positionPid_Cal(double targetvalue, double currentvalue, PID* pid);
double deltaPid_Cal(double targetvalue,double currentvalue,PID* pid);
void pidmemory_clear(PID* pid);

#endif
