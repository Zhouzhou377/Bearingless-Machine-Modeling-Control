#include "sys/injection.h"
#include "usr/Machine_Control/BP3/bp3_outloop_control.h"
#include "usr/Machine_Control/BP3/bp3_id.h"
#include "sys/util.h"
#include "drv/cpu_timer.h"
#include <math.h>

static double t = 0.0;
static uint32_t time = 0;

// Injection contexts for controller commands
inj_ctx_t inj_ctx_ctrl_bp3[19] = { 0 };
void bp3_injection_init (void){
	injection_ctx_init(&inj_ctx_ctrl_bp3[0], "vd_ref");
	injection_ctx_init(&inj_ctx_ctrl_bp3[1], "vq_ref");

	injection_ctx_init(&inj_ctx_ctrl_bp3[2], "vx_ref");
	injection_ctx_init(&inj_ctx_ctrl_bp3[3], "vy_ref");

	injection_ctx_init(&inj_ctx_ctrl_bp3[4], "id_ref");
	injection_ctx_init(&inj_ctx_ctrl_bp3[5], "iq_ref");

	injection_ctx_init(&inj_ctx_ctrl_bp3[6], "ix_ref");
	injection_ctx_init(&inj_ctx_ctrl_bp3[7], "iy_ref");

	injection_ctx_init(&inj_ctx_ctrl_bp3[8], "wrm_ref");

	injection_ctx_init(&inj_ctx_ctrl_bp3[9], "Fx_ref");
	injection_ctx_init(&inj_ctx_ctrl_bp3[10], "Fy_ref");

	injection_ctx_init(&inj_ctx_ctrl_bp3[11], "vd2_ref");
	injection_ctx_init(&inj_ctx_ctrl_bp3[12], "vq2_ref");

	injection_ctx_init(&inj_ctx_ctrl_bp3[13], "vx2_ref");
	injection_ctx_init(&inj_ctx_ctrl_bp3[14], "vy2_ref");

	injection_ctx_init(&inj_ctx_ctrl_bp3[15], "id2_ref");
	injection_ctx_init(&inj_ctx_ctrl_bp3[16], "iq2_ref");

	injection_ctx_init(&inj_ctx_ctrl_bp3[17], "ix2_ref");
	injection_ctx_init(&inj_ctx_ctrl_bp3[18], "iy2_ref");

	 // Register all signal injection points
    for (int i = 0; i < ARRAY_SIZE(inj_ctx_ctrl_bp3); i++) {
        injection_ctx_register(&inj_ctx_ctrl_bp3[i]);
    }
	t = 0.0;
	time = 0;
}
void bp3_injection_callback (bp3_control *data){
	injection_inj(&(data->current_control->tq.vdq0_ref_inject[0]), &inj_ctx_ctrl_bp3[0], data->current_control->tq.PI_regulator->Ts);
	injection_inj(&(data->current_control->tq.vdq0_ref_inject[1]), &inj_ctx_ctrl_bp3[1], data->current_control->tq.PI_regulator->Ts);

	injection_inj(&(data->current_control->s1.vdq0_ref_inject[0]), &inj_ctx_ctrl_bp3[2], data->current_control->s1.PI_regulator->Ts);
	injection_inj(&(data->current_control->s1.vdq0_ref_inject[1]), &inj_ctx_ctrl_bp3[3], data->current_control->s1.PI_regulator->Ts);

	injection_inj(&(data->current_control->tq.Idq0_ref_inject[0]), &inj_ctx_ctrl_bp3[4], data->current_control->tq.PI_regulator->Ts);
	injection_inj(&(data->current_control->tq.Idq0_ref_inject[1]), &inj_ctx_ctrl_bp3[5], data->current_control->tq.PI_regulator->Ts);

	injection_inj(&(data->current_control->s1.Idq0_ref_inject[0]), &inj_ctx_ctrl_bp3[6], data->current_control->s1.PI_regulator->Ts);
	injection_inj(&(data->current_control->s1.Idq0_ref_inject[1]), &inj_ctx_ctrl_bp3[7], data->current_control->s1.PI_regulator->Ts);

	injection_inj(&(data->bp3_v_control.wrm_ref_inject), &inj_ctx_ctrl_bp3[8], data->bp3_v_control.Ts);

	injection_inj(&(data->bp3_lev_control.F_xy_inject[0]), &inj_ctx_ctrl_bp3[9], data->bp3_v_control.Ts);
	injection_inj(&(data->bp3_lev_control.F_xy_inject[1]), &inj_ctx_ctrl_bp3[10], data->bp3_v_control.Ts);

	injection_inj(&(data->current_control->tq2.vdq0_ref_inject[0]), &inj_ctx_ctrl_bp3[11], data->current_control->tq2.PI_regulator->Ts);
	injection_inj(&(data->current_control->tq2.vdq0_ref_inject[1]), &inj_ctx_ctrl_bp3[12], data->current_control->tq2.PI_regulator->Ts);

	injection_inj(&(data->current_control->s2.vdq0_ref_inject[0]), &inj_ctx_ctrl_bp3[13], data->current_control->s2.PI_regulator->Ts);
	injection_inj(&(data->current_control->s2.vdq0_ref_inject[1]), &inj_ctx_ctrl_bp3[14], data->current_control->s2.PI_regulator->Ts);

	injection_inj(&(data->current_control->tq2.Idq0_ref_inject[0]), &inj_ctx_ctrl_bp3[15], data->current_control->tq2.PI_regulator->Ts);
	injection_inj(&(data->current_control->tq2.Idq0_ref_inject[1]), &inj_ctx_ctrl_bp3[16], data->current_control->tq2.PI_regulator->Ts);

	injection_inj(&(data->current_control->s2.Idq0_ref_inject[0]), &inj_ctx_ctrl_bp3[17], data->current_control->s2.PI_regulator->Ts);
	injection_inj(&(data->current_control->s2.Idq0_ref_inject[1]), &inj_ctx_ctrl_bp3[18], data->current_control->s2.PI_regulator->Ts);

}

void bp3_injection_sin(double w, double mag, double *theta, double *out, int Num_var){
	uint32_t time_now =  cpu_timer_now();
	double t_delta;
	if (time == 0 && t == 0.0){
		t = 0.0;
		time = time_now;
		t_delta = 0.0;
	}else if(time_now>time){
		
		t_delta = cpu_timer_ticks_to_sec(time_now-time);
		time = time_now;
	}else{
		
		t_delta = cpu_timer_ticks_to_sec(time_now +(0xFFFF-time));
		time = time_now;
	}
	t = t + t_delta;
	int i=0;
	for(i=0; i<Num_var; i++){
		out[i] = mag*cos(w*t+theta[i]);
	}

}
