#include "usr/Machine_Control/BP3/bp3_log.h"
#include "usr/Machine_Control/BP3/bp3_outloop_control.h"
#include "usr/Machine_Control/log_parameter.h"

 double LOG_theta_offset = 0.0;

void bp3_log (bp3_control *data){
    LOG_wrm = data->bp3_v_control.wrm_mes;
	LOG_wrm_ref = data->bp3_v_control.wrm_ref_lpf;
	LOG_wrm_inject = data->bp3_v_control.wrm_ref_inject;
	LOG_wrm_hf = data->bp3_v_control.wrm_est_hf;
	LOG_theta_offset = data->bp3_v_control.theta_rm_mes_offset;
	LOG_theta_rm = data->bp3_v_control.theta_rm_mes;
	LOG_theta_e = data->bp3_v_control.theta_re_ref;
    //LOG_theta_rm_pre = data->bp3_v_control.theta_rm_mes_pre[0];
	//LOG_Te_ref
	

	LOG_Itq_d_ref = data->current_control->tq.Idq0_ref[0];
	LOG_Itq_q_ref = data->current_control->tq.Idq0_ref[1];

	LOG_Itq_d = data->current_control->tq.Idq0[0];
	LOG_Itq_q = data->current_control->tq.Idq0[1];

	LOG_Iabc1_a = data->current_control->c_loop_inv1.Iabc[0];
	LOG_Iabc1_b = data->current_control->c_loop_inv1.Iabc[1];
	LOG_Iabc1_c = data->current_control->c_loop_inv1.Iabc[2];
	LOG_Iabc2_a = data->current_control->c_loop_inv2.Iabc[0];
	LOG_Iabc2_b = data->current_control->c_loop_inv2.Iabc[1];
	LOG_Iabc2_c = data->current_control->c_loop_inv2.Iabc[2];

	LOG_Te = data->bp3_v_control.Te_ref;

	LOG_va1_ref = data->current_control->c_loop_inv1.vabc_ref[0];
	LOG_vb1_ref = data->current_control->c_loop_inv1.vabc_ref[1];
	LOG_vc1_ref = data->current_control->c_loop_inv1.vabc_ref[2];

	LOG_va2_ref = data->current_control->c_loop_inv2.vabc_ref[0];
	LOG_vb2_ref = data->current_control->c_loop_inv2.vabc_ref[1];
	LOG_vc2_ref = data->current_control->c_loop_inv2.vabc_ref[2];

	LOG_vd_ref = data->current_control->tq.vdq0_ref[0];
	LOG_vq_ref = data->current_control->tq.vdq0_ref[1];
	LOG_v0_ref = data->current_control->tq.vdq0_ref[2];
	LOG_vd_inject = data->current_control->tq.vdq0_ref_inject[0];
	LOG_vq_inject = data->current_control->tq.vdq0_ref_inject[1];

	LOG_vx_ref = data->current_control->s1.vdq0_ref[0];
	LOG_vy_ref = data->current_control->s1.vdq0_ref[1];

	LOG_vx_inject = data->current_control->s1.vdq0_ref_inject[0];
	LOG_vy_inject = data->current_control->s1.vdq0_ref_inject[1];

	LOG_vd2_ref = data->current_control->tq2.vdq0_ref[0];
	LOG_vq2_ref = data->current_control->tq2.vdq0_ref[1];
	LOG_vd2_inject = data->current_control->tq2.vdq0_ref_inject[0];
	LOG_vq2_inject = data->current_control->tq2.vdq0_ref_inject[1];

	LOG_vx2_ref = data->current_control->s2.vdq0_ref[0];
	LOG_vy2_ref = data->current_control->s2.vdq0_ref[1];

	LOG_vx2_inject = data->current_control->s2.vdq0_ref_inject[0];
	LOG_vy2_inject = data->current_control->s2.vdq0_ref_inject[1];

	LOG_Is1_x = data->current_control->s1.Idq0[0];
	LOG_Is1_y = data->current_control->s1.Idq0[1];
	LOG_Is1_x_ref = data->current_control->s1.Idq0_ref[0];
	LOG_Is1_y_ref = data->current_control->s1.Idq0_ref[1];

	LOG_delta_x = data->bp3_lev_control.delta_mes[0];
	LOG_delta_y = data->bp3_lev_control.delta_mes[1];

	LOG_delta_x_ref = data->bp3_lev_control.delta_ref[0];
	LOG_delta_y_ref = data->bp3_lev_control.delta_ref[1];

	LOG_delta_x_ref_lpf = data->bp3_lev_control.delta_ref_lpf[0];
	LOG_delta_y_ref_lpf = data->bp3_lev_control.delta_ref_lpf[1];

	LOG_F_x = data->bp3_lev_control.F_xy_out[0];
	LOG_F_y = data->bp3_lev_control.F_xy_out[1];
	LOG_F_x_inject = data->bp3_lev_control.F_xy_inject[0];
	LOG_F_y_inject = data->bp3_lev_control.F_xy_inject[1];

	LOG_error_x = data->bp3_lev_control.err_delta[0];
	LOG_error_y = data->bp3_lev_control.err_delta[1];



}
