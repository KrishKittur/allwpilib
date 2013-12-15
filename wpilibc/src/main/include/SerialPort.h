/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.							  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#ifndef __SerialPort_h__
#define __SerialPort_h__

#include "ErrorBase.h"
#include "HAL/HAL.h"

/**
 * Driver for the RS-232 serial port on the cRIO.
 * 
 * The current implementation uses the VISA formatted I/O mode.  This means that
 *   all traffic goes through the fomatted buffers.  This allows the intermingled
 *   use of Printf(), Scanf(), and the raw buffer accessors Read() and Write().
 * 
 * More information can be found in the NI-VISA User Manual here:
 *   http://www.ni.com/pdf/manuals/370423a.pdf
 * and the NI-VISA Programmer's Reference Manual here:
 *   http://www.ni.com/pdf/manuals/370132c.pdf
 */
class SerialPort : public ErrorBase
{
public:
	typedef enum {kParity_None=0, kParity_Odd=1, kParity_Even=2, kParity_Mark=3, kParity_Space=4} Parity;
	typedef enum {kStopBits_One=10, kStopBits_OnePointFive=15, kStopBits_Two=20} StopBits;
	typedef enum {kFlowControl_None=0, kFlowControl_XonXoff=1, kFlowControl_RtsCts=2, kFlowControl_DtrDsr=4} FlowControl;
	typedef enum {kFlushOnAccess=1, kFlushWhenFull=2} WriteBufferMode;

	SerialPort(uint32_t baudRate, uint8_t dataBits = 8, Parity parity = kParity_None, StopBits stopBits = kStopBits_One);
	~SerialPort();
	void SetFlowControl(FlowControl flowControl);
	void EnableTermination(char terminator = '\n');
	void DisableTermination();
	int32_t GetBytesReceived();
	void Printf(const char *writeFmt, ...);
	void Scanf(const char *readFmt, ...);
	uint32_t Read(char *buffer, int32_t count);
	uint32_t Write(const char *buffer, int32_t count);
	void SetTimeout(float timeout);
	void SetReadBufferSize(uint32_t size);
	void SetWriteBufferSize(uint32_t size);
	void SetWriteBufferMode(WriteBufferMode mode);
	void Flush();
	void Reset();

	/*
	 * Do not call me!
	 */
	//void _internalHandler(uint32_t port, uint32_t eventType, uint32_t event);
private:
	uint32_t m_resourceManagerHandle;
	uint32_t m_portHandle;
	bool m_consoleModeEnabled;
	DISALLOW_COPY_AND_ASSIGN(SerialPort);
};

#endif
