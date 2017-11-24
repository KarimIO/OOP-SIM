All:
	@echo Compiling SIM...
	@g++ main.cpp sim_instructions.cpp system.cpp utils.cpp -o sim
	@echo SIM Compiled