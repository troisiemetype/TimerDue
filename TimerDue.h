#ifndef TIMER_DUE_H
#define TIMER_DUE_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#if !defined(__SAM3X8E__)
#error This class is intended to run on an ARM processor based Arduino Due board.
#endif

class TimerDue{
	friend void TC0_Handler();
	friend void TC1_Handler();
	friend void TC2_Handler();
	friend void TC3_Handler();
	friend void TC4_Handler();
	friend void TC5_Handler();
	friend void TC6_Handler();
	friend void TC7_Handler();
	friend void TC8_Handler();

public:
	TimerDue(uint8_t counter);
	TimerDue(Tc* counter, uint32_t channel);
	~TimerDue();

	void initMicroseconds(uint32_t microseconds);
	void initMilliseconds(uint32_t milliseconds);
	void initCPUCycles(uint32_t cpuCycles);
	void initFrequency(uint32_t freq);

	void start(void);

	void stop(void);

	void resume(void);

	void restart(void);

	void attach(void (*)(void));
	void detach(void);

	void update(void);


protected:

	static TimerDue* _timers[9];
	uint8_t _counterIndex;

	Tc *_pTc;
	uint32_t _channel;

	void (*_updateFunc)(void);

private:

};

#endif