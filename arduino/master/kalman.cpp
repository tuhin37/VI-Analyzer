#include <arduino.h>
#include "kalman.h"

void kalman::setGain(float gain) {	
	kalVarVolt = gain;
}


void kalman::setAccuracy(float accuracy) {
	kalVarProcess = accuracy;
}


void kalman::catchUp(int val) {
	float tmp;
	for(uint8_t i=0; i<100; i++) {
		tmp = output(val);
	}	
}


// Get filter output
float kalman::output(int val) {
	kalPc = kalP + kalVarProcess;
	kalG = kalPc/(kalPc + kalVarVolt);
	kalP = (1-kalG)*kalPc;
	kalXp = kalXe;
	kalZp = kalXp;
	kalXe = kalG*(val-kalZp)+kalXp; 
	return(kalXe);
}

