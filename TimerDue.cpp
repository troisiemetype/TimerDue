
#include "TimerDue.h"

TimerDue* TimerDue::_timers[] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};

TimerDue::TimerDue(uint8_t counter){
	if(counter > 8) return;
	_timers[counter] = this;

	_counterIndex = counter;

	uint8_t tc = counter / 3;
	uint8_t ch = counter % 3;

	_pTc = TC0 + (tc * 0x4000U);
	_channel = ch;

	pmc_set_writeprotect(false);
	pmc_enable_periph_clk(ID_TC0 + _counterIndex);

}

TimerDue::TimerDue(Tc* counter, uint32_t channel){
	uint8_t tc = 0;
	if(counter == TC0){
		tc = 0;
	} else if(counter == TC1){
		tc = 1;
	} else if(counter == TC2){
		tc = 2;
	} else {
		return;
	}

	TimerDue(3 * tc + channel);
}

TimerDue::~TimerDue(){
	stop();
	_timers[_counterIndex] = NULL;
}

void TimerDue::initMilliseconds(uint32_t milliseconds){
	initCPUCycles(milliseconds*(F_CPU / 1000));
}

void TimerDue::initMicroseconds(uint32_t microseconds){
	initCPUCycles(microseconds*(F_CPU / 1000000));
}

void TimerDue::initFrequency(uint32_t freq){
	initCPUCycles((F_CPU / freq));
}


void TimerDue::initCPUCycles(uint32_t cpuCycles){
/*	for(uint8_t i = 0; i < 3; ++i){
		SerialUSB.print("index ");
		SerialUSB.print(i);
		SerialUSB.print('\t');
		SerialUSB.println((uint32_t)_timers[i]);
	}
*/

//	SerialUSB.print("TC0: ");
//	SerialUSB.println((uint32_t)TC0);

	stop();

	// Configure interrupt
	NVIC_DisableIRQ((IRQn)(TC0_IRQn + _counterIndex));
	NVIC_ClearPendingIRQ((IRQn)(TC0_IRQn + _counterIndex));
	NVIC_SetPriority((IRQn)(TC0_IRQn + _counterIndex), 0);
	NVIC_EnableIRQ((IRQn)(TC0_IRQn + _counterIndex));

	// Configure timer.
	// Pointer to a TC instance
	// Channel number
	// Operating mode
	TC_Configure(_pTc, _channel, TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | TC_CMR_TCCLKS_TIMER_CLOCK1);

	// Compute the value for RC (which is used for a counter reset on compare match)
	uint32_t rc = cpuCycles / 2;
	TC_SetRC(_pTc, _channel, rc);
	
	// Set the sample rate again, so we know the exact value for requency calculations
//	cpuCycles = (F_CPU / 2) / rc;

	// No pre-made functions supplied by Atmel for interrupt enable, so we have to do it by hand.
	// There are several way to achieve this. We could directly access registers, i.e.
	// REG_TC0_IER0 |= TC_IER_CPCS; // See instance_tc0.h
	// Or we can use struct defined in component_tc.h, that groups all registers for a channel.
	// This has the advantage of working with relatives offsets regarding TC and channel used.

	// Disabling all interrupts on this channel of TC0
	_pTc->TC_CHANNEL[_channel].TC_IDR = ~0;
	// Enabling RC compare match interrupt
	_pTc->TC_CHANNEL[_channel].TC_IER |= TC_IER_CPCS;
}


void TimerDue::start(void){
	TC_Start(_pTc, _channel);
}


void TimerDue::stop(void){
	TC_Stop(_pTc, _channel);
}


void TimerDue::resume(void){

}


void TimerDue::restart(void){

}

void TimerDue::attach(void (*function)(void)){
	_updateFunc = function;
}

void TimerDue::detach(void){
	_updateFunc = NULL;

}

void TimerDue::update(void){
	if(_updateFunc == NULL) return;
	_updateFunc();
}

void TC0_Handler(){
	TimerDue* instance = TimerDue::_timers[0];
	// We have a RC compare value, so we update our stuff.
	if(TC_GetStatus(instance->_pTc, instance->_channel) & TC_SR_CPCS){
		instance->update();
	}
}

void TC1_Handler(){
	TimerDue* instance = TimerDue::_timers[1];
	// We have a RC compare value, so we update our stuff.
	if(TC_GetStatus(instance->_pTc, instance->_channel) & TC_SR_CPCS){
		instance->update();
	}
}

void TC2_Handler(){
	TimerDue* instance = TimerDue::_timers[2];
	// We have a RC compare value, so we update our stuff.
	if(TC_GetStatus(instance->_pTc, instance->_channel) & TC_SR_CPCS){
		instance->update();
	}
}

void TC3_Handler(){
	TimerDue* instance = TimerDue::_timers[3];
	// We have a RC compare value, so we update our stuff.
	if(TC_GetStatus(instance->_pTc, instance->_channel) & TC_SR_CPCS){
		instance->update();
	}
}

void TC4_Handler(){
	TimerDue* instance = TimerDue::_timers[4];
	// We have a RC compare value, so we update our stuff.
	if(TC_GetStatus(instance->_pTc, instance->_channel) & TC_SR_CPCS){
		instance->update();
	}
}

void TC5_Handler(){
	TimerDue* instance = TimerDue::_timers[5];
	// We have a RC compare value, so we update our stuff.
	if(TC_GetStatus(instance->_pTc, instance->_channel) & TC_SR_CPCS){
		instance->update();
	}
}

void TC6_Handler(){
	TimerDue* instance = TimerDue::_timers[6];
	// We have a RC compare value, so we update our stuff.
	if(TC_GetStatus(instance->_pTc, instance->_channel) & TC_SR_CPCS){
		instance->update();
	}
}

void TC7_Handler(){
	TimerDue* instance = TimerDue::_timers[7];
	// We have a RC compare value, so we update our stuff.
	if(TC_GetStatus(instance->_pTc, instance->_channel) & TC_SR_CPCS){
		instance->update();
	}
}

void TC8_Handler(){
	TimerDue* instance = TimerDue::_timers[8];
	// We have a RC compare value, so we update our stuff.
	if(TC_GetStatus(instance->_pTc, instance->_channel) & TC_SR_CPCS){
		instance->update();
	}
}

