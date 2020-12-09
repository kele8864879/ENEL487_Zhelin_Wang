1. I think all of function is finished. 
I do the help command, mode fsm, mode scm, atm x, and error enter detect, and mode refresh on putty.

2. one blue led flashing has little bug at vedio, but this bug is fixed now.

operation guide: I used USART2 to do the project and bitrate is 115200, please use correct putty setting.
enter help can get the recommanded command that you can enter.
The begin mode is fsm, so enter scm to change mode to scm.
enter ATM 1-100 can change the speed, but you need to enter fsm or scm to reopen the mode.
enter wrong command will show the Invalid command ....
enter fsm or scm the top of putty screen will update the current state.

3.I saved some define at "../../Mycode/CLI/CLI.h"
The led pin connection is:
Primary: 	RED - PA6
	YELLOW - PA7
	GREEN - PA8
	BLUE -PA9
Secondary:	RED - PC9
		YELLOW - PC6
		GREEN - PC8
		BLUE - PC5
