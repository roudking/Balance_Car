#include "pid.h"


double xianfu(double value, double min, double max) {
    if (value > max) return max;
    if (value < min) return min;
    return value;
}

double position_divAPI_PID_Cal(double targetvalue,double currentvalue,double current_div,PID* pid) {
	
	pid->last_outvalue = pid->outvalue;
	// 1. 计算当前偏差
	double bias = targetvalue - currentvalue;

	// 2. 计算比例项
	double P = pid->kp * bias;

	// 3. 更新积分项（累积当前偏差）
	pid->integral += bias;

	// 4. 计算积分项和微分项
	double I = pid->ki * pid->integral;
		  //积分限幅 
	if(pid->integrate_xianfu > 0)
	 {
	  I = xianfu(I, -pid->integrate_xianfu, pid->integrate_xianfu);
	 }
	 
	double D = current_div * pid->kd;

	// 5. 计算总输出
	   pid->outvalue = P + I + D;

	// 6. 对输出进行限幅
	 if(pid->out_xianfu > 0)
	 {
	 	 pid->outvalue = xianfu(pid->outvalue, -pid->out_xianfu, pid->out_xianfu);
	 }

	return pid->outvalue;
}


// 位置式 PID 计算函数（带输出限幅和积分抗饱和）
double positionPid_Cal(double targetvalue, double currentvalue, PID* pid) {
    
	
		pid->last_outvalue = pid->outvalue;
	  // 1. 计算当前偏差
    double bias = targetvalue - currentvalue;

    // 2. 计算比例项
    double P = pid->kp * bias;

    // 3. 更新积分项（累积当前偏差）
    pid->integral += bias;

    // 4. 计算积分项和微分项
    double I = pid->ki * pid->integral;
	  //积分限幅 
	 if(pid->integrate_xianfu > 0)
	 {
	  I = xianfu(I, -pid->integrate_xianfu, pid->integrate_xianfu);
	 }
    double D = pid->kd * (bias - pid->last_bias);

    // 5. 计算总输出
     pid->outvalue = P + I + D;

	  // 6. 对输出进行限幅
	  if(pid->out_xianfu > 0)
		{
			  pid->outvalue = xianfu(pid->outvalue, -pid->out_xianfu, pid->out_xianfu);
		}

    // 8. 更新状态
    pid->last_bias = bias;      // 保存当前偏差，用于下一次微分计算

    return pid->outvalue;
}

double deltaPid_Cal(double targetvalue,double currentvalue,PID* pid)
{
	
		pid->last_outvalue = pid->outvalue;
	
	double bias,current_bias,outputvalue; 
	
	current_bias = targetvalue - currentvalue;

  bias = current_bias - pid->last_bias;
	
	pid -> outvalue += pid->kp * bias + pid->ki * current_bias;

	pid->last_bias = current_bias;
	
	if(pid->out_xianfu > 0)
	{
	  pid -> outvalue = xianfu(pid -> outvalue,-pid->out_xianfu,pid->out_xianfu);
	}

	return pid -> outvalue;
}

void pidmemory_clear(PID* pid)
{
	  pid->integral  = 0;
    pid -> last_bias = 0;
	  pid -> outvalue  = 0;
		pid->last_outvalue = 0;
}


