#include "usr/user_config.h"

#ifdef APP_CABINET
#include "usr/Cabinet_test/twinbearingless_control.h"
#include "usr/Cabinet_test/outloop_control.h"
#include "usr/Cabinet_test/cmd/cmd_BIM_ctrl.h"
#include "usr/Cabinet_test/task_cabinet.h"
#include "drv/cpu_timer.h"
#include "usr/Cabinet_test/cabinet.h"
#include "usr/Cabinet_test/analog_sensor.h"
#include "usr/Cabinet_test/mb_sensor.h"
#include "sys/defines.h"
#include "sys/commands.h"
#include "sys/debug.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "drv/analog.h"



//#define TS	(1.0 / TASK_CABINET_UPDATES_PER_SEC)// sample time

static command_entry_t cmd_entry;

#define NUM_HELP_ENTRIES	(12)
static command_help_t cmd_help[NUM_HELP_ENTRIES] = {
		{"init", "Initialize control loop"},
		{"deinit", "Deinitialize control loop"},
		{"reset", "Reset regulator"},
		{"set_vdc", "Set DC Bus for a Specific Inverter"},
		{"enable_ctrl", "Enable BIM control"},
		{"enable_vctrl", "Enable BIM velocity control"},
		{"enable_levctrl", "Enable BIM levitation control"},
		{"set_w", "Set rotor mechanical rotational speed rad/s"},
		{"set_id", "Set id"},
		{"set_Te", "Set Te"},
		{"set_deltaxy", "Set rotor position xy0"},
		{"disable_ctrl", "Disable BIM regulation"}

};

void cmd_BIM_register(void)
{
	
	// Populate the command entry block (struct)
	commands_cmd_init(&cmd_entry,
			"BIM", "Bearingless Induction Machine Control Commands",
			cmd_help, NUM_HELP_ENTRIES,
			cmd_BIM
	);

	// Register the command
	commands_cmd_register(&cmd_entry);
}

//
// Handles the 'cabinet' command
// and all sub-commands
//
int cmd_BIM(int argc, char **argv)
{

	if (strcmp("init", argv[1]) == 0) {
		// Check correct number of arguments
		if (argc != 2) return CMD_INVALID_ARGUMENTS;

		// Make sure cabinet task was not already inited
		init_bim();
		
		return CMD_SUCCESS;
	}

	if (strcmp("deinit", argv[1]) == 0) {
		// Check correct number of arguments
		if (argc != 2) return CMD_INVALID_ARGUMENTS;

		// Make sure cabinet task was not already inited
		deinit_bim();
		cmd_enable.enable_currentcontrol = 0;
		cmd_enable.enable_openloop = 0;
		cmd_enable.enable_testloop = 0;
		cmd_enable.enable_BIMcontrol = 0;
		return CMD_SUCCESS;
	}

	if (strcmp("reset", argv[1]) == 0) {
		// Check correct number of arguments
		if (argc != 2) return CMD_INVALID_ARGUMENTS;

		// Make sure cabinet task was not already inited
		reset_bim();
		
		return CMD_SUCCESS;
	}


	if (strcmp("set_vdc", argv[1]) == 0) {
		// Check correct number of arguments
		if (argc != 3) return CMD_INVALID_ARGUMENTS;

		//read in arguments
		double Vdc = strtod(argv[2], NULL);

		bim_control_data.current_control->twin_inv1.inv->Vdc = Vdc;
		bim_control_data.current_control->twin_inv2.inv->Vdc = Vdc;

		return CMD_SUCCESS;
	}

	
	if (strcmp("enable_ctrl", argv[1]) == 0) {
		// Check correct number of arguments
		if (argc != 2) return CMD_INVALID_ARGUMENTS;
		cmd_enable.enable_BIMcontrol = 1;
		cmd_enable.enable_currentcontrol = 0;
		cmd_enable.enable_openloop = 0;
		reset_bim();
		return CMD_SUCCESS;
	}

	if (strcmp("enable_vctrl", argv[1]) == 0) {
		// Check correct number of arguments
		if (argc != 2) return CMD_INVALID_ARGUMENTS;
		bim_control_data.bim_v_control.enable = 1;
		//reset_bim();
		return CMD_SUCCESS;
	}

	if (strcmp("enable_levctrl", argv[1]) == 0) {
		// Check correct number of arguments
		if (argc != 2) return CMD_INVALID_ARGUMENTS;
		bim_control_data.bim_lev_control.enable = 1;
		//reset_bim();
		return CMD_SUCCESS;
	}



	if (strcmp("enable_log", argv[1]) == 0) {
		// Check correct number of arguments
		if (argc != 2) return CMD_INVALID_ARGUMENTS;

		cmd_enable.enable_log = 1;
		
		return CMD_SUCCESS;
	}



	if (strcmp("set_deltaxy", argv[1]) == 0) {
		// Check correct number of arguments
		if (argc != 4) return CMD_INVALID_ARGUMENTS;

		//read in arguments
		double delta_x = strtod(argv[2], NULL);
		double delta_y = strtod(argv[3], NULL);

		bim_control_data.bim_lev_control.delta_ref[0] = delta_x;
		bim_control_data.bim_lev_control.delta_ref[1] = delta_y;
		
		return CMD_SUCCESS;
	}

	if (strcmp("set_w", argv[1]) == 0) {
		// Check correct number of arguments
		if (argc != 3) return CMD_INVALID_ARGUMENTS;

		//read in arguments
		double w = strtod(argv[2], NULL);
	

		bim_control_data.bim_v_control.wrm_ref = w;
		return CMD_SUCCESS;
	}

	if (strcmp("set_id", argv[1]) == 0) {
		// Check correct number of arguments
		if (argc != 3) return CMD_INVALID_ARGUMENTS;

		//read in arguments
		double id = strtod(argv[2], NULL);
	

		bim_control_data.bim_v_control.Idq0_ref[0] = id;
		return CMD_SUCCESS;
	}

	if (strcmp("set_Te", argv[1]) == 0) {
		// Check correct number of arguments
		if (argc != 3) return CMD_INVALID_ARGUMENTS;

		//read in arguments
		double Te = strtod(argv[2], NULL);
	

		bim_control_data.bim_v_control.Te_ref = Te;
		return CMD_SUCCESS;
	}


	
	if (strcmp("disable_ctrl", argv[1]) == 0) {
		// Check correct number of arguments
		if (argc != 2) return CMD_INVALID_ARGUMENTS;

		cmd_enable.enable_BIMcontrol = 0;
		cmd_enable.enable_currentcontrol = 0;
		cmd_enable.enable_openloop = 0;
		reset_bim();
		
		return CMD_SUCCESS;
	}

	return CMD_INVALID_ARGUMENTS;
}

#endif //APP_CABINET