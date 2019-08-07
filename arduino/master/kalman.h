class kalman{
	public: 

	// e.g. 0.25 (Gain control convergence step, bigger the gain faster convergence)
	void setGain(float gain);

	// e.g. 0.00001 (smaller the number more the accuracy and slower the system convergence)
	void setAccuracy(float accuracy);

	// makes the filter already converged to the given value 
	void catchUp(int val);

	// Get filter output
	float output(int val);

	// Filter taps
	private: 
	float kalVarVolt = 0.25; // filter gain
	float kalVarProcess = 0.00001; // accuracy (smaller the number more the accuracy and slower the system response)
	float kalPc = 0.0;
	float kalG = 0.0;
	float kalP = 1.0;
	float kalXp = 0.0;
	float kalZp = 0.0;
	float kalXe = 0.0;	 	
};


/********************* Example ********************
#include "kalman.h"
kalman voltageFilter;

void setup() {
    // put your setup code here, to run once:
	Serial.begin(9600);
	voltageFilter.catchUp(557);
}



void loop() {
    // put your main code here, to run repeatedly:
	uint16_t adc, fil;
	adc = analogRead(A0);
	fil = voltageFilter.output(adc);
	Serial.print("RAW:  ");
	Serial.print(adc);
	Serial.print(" ");
	Serial.print("Filtered:  ");
	Serial.println(fil);
}
*/
