/+ACo- Copyright Statement:
 +ACo-
 +ACo-/
+ACM-include +ACI-sensor+AF8-alg+AF8-interface.h+ACI-
+ACM-include +ACI-stdio.h+ACI-
+ACM-include +ACI-algo+AF8-adaptor/algo+AF8-adaptor.h+ACI-
+ACM-include +ACI-FreeRTOS.h+ACI-
+ACM-include +ACI-stdint.h+ACI-

+ACM-if defined(FOTA+AF8-UBIN+AF8-DECOUPLING)
+ACM-include +ACI-heart+AF8-rate+AF8-wrapper.h+ACI-
+ACM-include +ACI-ppg+AF8-control+AF8-wrapper.h+ACI-
+ACM-endif

// Function configuration
+ACM-if defined(MTK+AF8-SENSOR+AF8-BIO+AF8-USE+AF8-MT2511)
+ACM-include +ACI-vsm+AF8-driver.h+ACI-
+ACM-define OHRM+AF8-ON            // When enabled, turn on optical HR monitor (OHRM).
+ACM-define OHRM+AF8-DEBUG+AF8-STATUS  // When enabled, the debug information will be grouped in status. Notify frequency is 2.2Hz.
                           // When disabled, the debug information in adapter will not be included in status. Notify frequency is 1Hz.
+ACM-define OHRM+AF8-DEBUG+AF8-ADAPTER // When enabled, check system correctness.
+ACM-define OHRM+AF8-PPG+AF8-CTRL+AF8-ON   // When enabled, turned on PPG control function.
+ACM-define OHRM+AF8-MOTION+AF8-ON     // When disabled, set motion input to zero for test.
+ACM-define OHRM+AF8-DYNAMIC+AF8-FS+AF8-RATIO+AF8-ON  // When enabled, update fs ratio of acc/ppg (ohrm+AF8-fs+AF8-acc+AF8-div+AF8-ppg) based on g-sensor timestamp.
                                  // When disabled, set fs ratio of acc/ppg (ohrm+AF8-fs+AF8-acc+AF8-div+AF8-ppg) to default value.
+ACM-define OHRM+AF8-ADJUST+AF8-NOTIFIER
+ACM-endif //+ACM-if defined(MTK+AF8-SENSOR+AF8-BIO+AF8-USE+AF8-MT2511)

+ACM-if defined(OHRM+AF8-PPG+AF8-CTRL+AF8-ON)
+ACM-include +ACI-ppg+AF8-control.h+ACI-
+ACM-endif //+ACM-if defined(OHRM+AF8-PPG+AF8-CTRL+AF8-ON)

+ACM-if defined(OHRM+AF8-ON)
+ACM-include +ACI-ohrm.h+ACI-
// Only support 64, 128 Hz PPG.
+ACM-ifdef HR+AF8-PPG+AF8-64HZ
    +ACM-define FS+AF8-PPG+AF8-HZ 64
+ACM-else
    +ACM-define FS+AF8-PPG+AF8-HZ 128
+ACM-endif

// Only support 50, 62.5 (64), 100, 125 Hz ACC.
+ACM-ifndef FS+AF8-ACC+AF8-HZ
    +ACM-if (FS+AF8-PPG+AF8-HZ+AD0APQ-64)
        +ACM-define FS+AF8-ACC+AF8-HZ 62
    +ACM-else
        +ACM-define FS+AF8-ACC+AF8-HZ 125
    +ACM-endif
+ACM-endif
+ACM-define PPG+AF8-BITWIDTH 23 // Fix at 23-bit for MT2511 use.
+ACM-define ACC+AF8-BITWIDTH 32 // If g-sensor data is the unsigned data from ADC, please key in the bitwidth for conversion.
                        // If g-sensor data is already converted from unsigned to signed, fill in 32-bit.
+ACM-define ACC+AF8-UNIT+AF8-LSB+AF8-1G 9800 // The (sensitivity) representation of g-sensor LSB unit.
                             // Ex: For BMI160 set at 8g range, sensitivity8g +AD0- 4096LSB/g. Set ACC+AF8-UNIT+AF8-LSB+AF8-1G +AD0- 4096.
                             // Note: For BMA255 driver in SDK, the LSB unit has been transformed. Hence 1g-force +AD0- 9800LSB.
+ACM-if(FS+AF8-PPG+AF8-HZ+AD0APQ-125)
    +ACM-define REAL+AF8-PPG+AF8-SAMPLE+AF8-INTERVAL+AF8-100NANOSEC 80070 //round(10+AF4-7 / 124.8899475940924) 100nano-second
+ACM-elif(FS+AF8-PPG+AF8-HZ+AD0APQ-128)
    +ACM-define REAL+AF8-PPG+AF8-SAMPLE+AF8-INTERVAL+AF8-100NANOSEC 78125 //round(10+AF4-7 / 128.0) 100nano-second
+ACM-elif(FS+AF8-PPG+AF8-HZ+AD0APQ-64)
    +ACM-define REAL+AF8-PPG+AF8-SAMPLE+AF8-INTERVAL+AF8-100NANOSEC 78125 //2x upsampled from 64Hz to 128Hz.
+ACM-endif

// buffer control
+ACM-if (FS+AF8-ACC+AF8-HZ+AD0APQ-50 +AHwAfA- FS+AF8-ACC+AF8-HZ+AD0APQ-62 +AHwAfA- FS+AF8-ACC+AF8-HZ+AD0APQ-64)
    +ACM-define ACC+AF8-BUF+AF8-SIZE 2
+ACM-else
    +ACM-define ACC+AF8-BUF+AF8-SIZE 1
+ACM-endif
+ACM-define PPG+AF8-BUF+AF8-SIZE 4
+ACM-define OHRM+AF8-OUT+AF8-LENGTH 1
+ACM-define OHRM+AF8-PPG+AF8-CTRL+AF8-OUT+AF8-LENGTH 1

// OHRM config
uint32+AF8-t ohrm+AF8-adapter+AF8-timer+ADs-
uint32+AF8-t ohrm+AF8-adapter+AF8-ts+ADs-
int32+AF8-t ohrm+AF8-adapt+AF8-pre+AF8-ts+AF8-ppg+ADs-
int32+AF8-t ohrm+AF8-adapt+AF8-pre+AF8-ts+AF8-motion+ADs-
int32+AF8-t ohrm+AF8-adapt+AF8-cur+AF8-val+AF8-ppg+ADs-
int32+AF8-t ohrm+AF8-adapt+AF8-pre+AF8-val+AF8-ppg+ADs-
int32+AF8-t ohrm+AF8-adapt+AF8-pre+AF8-val+AF8-amb+ADs-
int32+AF8-t ohrm+AF8-adapt+AF8-pre+AF8-val+AF8-motion+ADs-
int32+AF8-t ohrm+AF8-adap+AF8-init+AF8-ppg+ADs-
int32+AF8-t ohrm+AF8-adap+AF8-init+AF8-motion+ADs-

int32+AF8-t ohrm+AF8-adapt+AF8-buf+AF8-ppg+AFs-PPG+AF8-BUF+AF8-SIZE+AF0AOw-
int32+AF8-t ohrm+AF8-adapt+AF8-buf+AF8-motion+AFs-ACC+AF8-BUF+AF8-SIZE+AF0AOw-
int32+AF8-t ohrm+AF8-adapt+AF8-buf+AF8-ts+AF8-ppg+AFs-PPG+AF8-BUF+AF8-SIZE+AF0AOw-
int32+AF8-t ohrm+AF8-adapt+AF8-buf+AF8-ts+AF8-motion+AFs-ACC+AF8-BUF+AF8-SIZE+AF0AOw-
int32+AF8-t ohrm+AF8-adapt+AF8-idx+AF8-ppg+ADs-
int32+AF8-t ohrm+AF8-adapt+AF8-idx+AF8-motion+ADs-

+ACM-if defined(OHRM+AF8-ADJUST+AF8-NOTIFIER)
int32+AF8-t ohrm+AF8-control+AF8-flag+ADs-
+ACM-endif

// Calc. FS+AF8-MOTION/FS+AF8-PPG (T+AF8-PPG/T+AF8-MOTION)
+ACM-if(FS+AF8-PPG+AF8-HZ +AD0APQ- 64)
    +ACM-define MOTION+AF8-RATIO+AF8-LEFT+AF8-SHIFT 0 //bacause of 2x upsampled, otherwise 1.
+ACM-else
    +ACM-define MOTION+AF8-RATIO+AF8-LEFT+AF8-SHIFT 0
+ACM-endif

+ACM-if (FS+AF8-ACC+AF8-HZ+AD0APQ-50 +AHwAfA- FS+AF8-ACC+AF8-HZ+AD0APQ-100) // ODR (75, 100, 125/128) /128 +ACo-4096
    +ACM-define MOTION+AF8-PPG+AF8-RATIO+AF8-UPPER+AF8-BOUND (4000 +ADwAPA- MOTION+AF8-RATIO+AF8-LEFT+AF8-SHIFT)
    +ACM-define MOTION+AF8-PPG+AF8-RATIO+AF8-LOWER+AF8-BOUND (2400 +ADwAPA- MOTION+AF8-RATIO+AF8-LEFT+AF8-SHIFT)
    +ACM-define MOTION+AF8-PPG+AF8-RATIO+AF8-DEFAULT     (3200 +ADwAPA- MOTION+AF8-RATIO+AF8-LEFT+AF8-SHIFT)
+ACM-else // ODR (100, 125/128, 150) /128 +ACo-4096
    +ACM-define MOTION+AF8-PPG+AF8-RATIO+AF8-UPPER+AF8-BOUND (4800 +ADwAPA- MOTION+AF8-RATIO+AF8-LEFT+AF8-SHIFT)
    +ACM-define MOTION+AF8-PPG+AF8-RATIO+AF8-LOWER+AF8-BOUND (3200 +ADwAPA- MOTION+AF8-RATIO+AF8-LEFT+AF8-SHIFT)
    +ACM-define MOTION+AF8-PPG+AF8-RATIO+AF8-DEFAULT     (4000 +ADwAPA- MOTION+AF8-RATIO+AF8-LEFT+AF8-SHIFT)
+ACM-endif

+ACM-define MOTION+AF8-PPG+AF8-RATIO+AF8-DECIMAL+AF8-POINT+AF8-BITS 12
+ACM-define MOTION+AF8-PPG+AF8-RATIO+AF8-FORGET+AF8-LENGTH (FS+AF8-ACC+AF8-HZ +ACo- 1800)
uint32+AF8-t ohrm+AF8-fs+AF8-acc+AF8-div+AF8-ppg +AD0- MOTION+AF8-PPG+AF8-RATIO+AF8-DEFAULT+ADs- // fs+AF8-acc / fs+AF8-ppg: 12-bit decimal representation +AD0APQA+- 0x1000 means 1.0
uint32+AF8-t motion+AF8-total+AF8-sample+AF8-interval +AD0- 0+ADs- //ms
uint32+AF8-t motion+AF8-accumulated+AF8-count +AD0- 0+ADs-

void ms+AF8-fps+AF8-statistic+AF8-update(uint32+AF8-t ts+AF8-prevous, uint32+AF8-t ts+AF8-current, int32+AF8-t count)+ADs-
uint32+AF8-t update+AF8-motion+AF8-ppg+AF8-sample+AF8-time+AF8-ratio(void)+ADs-
// End --Calc. FS+AF8-MOTION/FS+AF8-PPG --

// debug info
+ACM-if defined(OHRM+AF8-DEBUG+AF8-ADAPTER)
+ACM-define OHRM+AF8-DBG+AF8-ERR+AF8-TS+AF8-MAX 5
+ACM-define OHRM+AF8-DBG+AF8-NEG+AF8-TS+AF8-MAX 1
int32+AF8-t dbg+AF8-ohrm+AF8-switch +AD0- 0+ADs-
int32+AF8-t dbg+AF8-cnt+AF8-err+AF8-ts+AF8-ppg +AD0- 0+ADs-
int32+AF8-t dbg+AF8-cnt+AF8-neg+AF8-ts+AF8-ppg +AD0- 0+ADs-
int32+AF8-t dbg+AF8-cnt+AF8-err+AF8-ts+AF8-acc +AD0- 0+ADs-
int32+AF8-t dbg+AF8-cnt+AF8-neg+AF8-ts+AF8-acc +AD0- 0+ADs-
int32+AF8-t dbg+AF8-cnt+AF8-ppg+AF8-ip +AD0- 0+ADs-
int32+AF8-t dbg+AF8-cnt+AF8-acc+AF8-ip +AD0- 0+ADs-
int32+AF8-t dbg+AF8-cnt+AF8-5sec +AD0- 0+ADs-
+ACM-endif //+ACM-if defined(OHRM+AF8-DEBUG+AF8-ADAPTER)

uint8+AF8-t watch+AF8-off+AF8-detection+AF8-enable +AD0- 1+ADs- // default set 1: enable
// End 
+ACM-endif //+ACM-if defined(OHRM+AF8-ON)

/+ACo- syslog +ACo-/
+ACM-define LOGI(fmt,arg...)   LOG+AF8-I(sensor, +ACIAWw-HeartRateM+AF0-: +ACI-fmt,+ACMAIw-arg)
+ACM-define LOGE(fmt,arg...)   LOG+AF8-E(sensor, +ACIAWw-HeartRateM+AF0-: +ACI-fmt,+ACMAIw-arg)
/+ACo- printf+ACo-/
//+ACM-define LOGE(fmt, args...)    printf(+ACIAWw-HeartRateM+AF0- ERR: +ACI-fmt, +ACMAIw-args)
//+ACM-define LOGD(fmt, args...)    printf(+ACIAWw-HeartRateM+AF0- DBG: +ACI-fmt, +ACMAIw-args)

+ACM-if (FS+AF8-ACC+AF8-HZ+AD0APQ-50)
    +ACM-define HEART+AF8-RATE+AF8-MONITOR+AF8-ACC+AF8-DELAY 20
    +ACM-define HEART+AF8-RATE+AF8-MONITOR+AF8-ACC+AF8-POLLING+AF8-TIME 400
+ACM-elif (FS+AF8-ACC+AF8-HZ+AD0APQ-62 +AHwAfA- FS+AF8-ACC+AF8-HZ+AD0APQ-64)
    +ACM-define HEART+AF8-RATE+AF8-MONITOR+AF8-ACC+AF8-DELAY 16
    +ACM-define HEART+AF8-RATE+AF8-MONITOR+AF8-ACC+AF8-POLLING+AF8-TIME 400
+ACM-elif (FS+AF8-ACC+AF8-HZ+AD0APQ-100)
    +ACM-define HEART+AF8-RATE+AF8-MONITOR+AF8-ACC+AF8-DELAY 10
    +ACM-define HEART+AF8-RATE+AF8-MONITOR+AF8-ACC+AF8-POLLING+AF8-TIME 200
+ACM-else // 125/128
    +ACM-define HEART+AF8-RATE+AF8-MONITOR+AF8-ACC+AF8-DELAY 8
    +ACM-define HEART+AF8-RATE+AF8-MONITOR+AF8-ACC+AF8-POLLING+AF8-TIME 200
+ACM-endif

+ACM-if (FS+AF8-PPG+AF8-HZ +AD0APQ- 64)
    +ACM-define HEART+AF8-RATE+AF8-MONITOR+AF8-PPG1+AF8-DELAY 16
    +ACM-define HEART+AF8-RATE+AF8-MONITOR+AF8-PPG1+AF8-DELAY+AF8-MARGIN 48
    +ACM-define HEART+AF8-RATE+AF8-MONITOR+AF8-PPG1+AF8-POLLING+AF8-TIME 400
+ACM-else
    +ACM-define HEART+AF8-RATE+AF8-MONITOR+AF8-PPG1+AF8-DELAY 8
    +ACM-define HEART+AF8-RATE+AF8-MONITOR+AF8-PPG1+AF8-DELAY+AF8-MARGIN 24
    +ACM-define HEART+AF8-RATE+AF8-MONITOR+AF8-PPG1+AF8-POLLING+AF8-TIME 200 // align ACC irq: 25 samples
+ACM-endif

static sensor+AF8-input+AF8-list+AF8-t input+AF8-heart+AF8-rate+AF8-monitor+AF8-comp+AF8-acc+ADs-
static sensor+AF8-input+AF8-list+AF8-t input+AF8-heart+AF8-rate+AF8-monitor+AF8-comp+AF8-bio+ADs-

static int32+AF8-t get+AF8-heart+AF8-rate+AF8-monitor+AF8-result(sensor+AF8-data+AF8-t +ACo-const output)
+AHs-
+ACM-if defined(OHRM+AF8-ON)
    int32+AF8-t ohrm+AF8-status+ADs-
    int32+AF8-t ppg+AF8-control+AF8-status+ADs-
    int32+AF8-t hr+AF8-out+AF8-status+ADs-
    bus+AF8-data+AF8-t ppg+AF8-reg+AF8-info+ADs-
    uint32+AF8-t ohrm+AF8-reg+AF8-tx+ADs-
    uint32+AF8-t ohrm+AF8-reg+AF8-rx+ADs-
+ACM-endif //+ACM-if defined(OHRM+AF8-ON)

    sensor+AF8-data+AF8-unit+AF8-t +ACo-hrm+AF8-data +AD0- NULL+ADs-
    if(output +AD0APQ- NULL +AHwAfA- output-+AD4-data +AD0APQ- NULL) +AHs-
        return -1+ADs-
    +AH0- else +AHs-
         hrm+AF8-data +AD0- output-+AD4-data+ADs-
    +AH0-
    hrm+AF8-data-+AD4-sensor+AF8-type +AD0- SENSOR+AF8-TYPE+AF8-HEART+AF8-RATE+AF8-MONITOR+ADs-

+ACM-if defined(OHRM+AF8-ON)
    hrm+AF8-data-+AD4-time+AF8-stamp +AD0- ohrm+AF8-adapter+AF8-ts+ADs-
    hrm+AF8-data-+AD4-heart+AF8-rate+AF8-t.bpm +AD0- ohrm+AF8-get+AF8-bpm()+AD4APg-16+ADs-

    ohrm+AF8-status +AD0- ohrm+AF8-get+AF8-confidence+AF8-level() +ACY- 0x000000FF+ADs-
    ppg+AF8-control+AF8-status +AD0- ppg+AF8-control+AF8-get+AF8-status(0)+ADs-
    hr+AF8-out+AF8-status +AD0- ohrm+AF8-status+ADs-

    if(watch+AF8-off+AF8-detection+AF8-enable +AD0APQ- 1) +AHs- 
       if(ppg+AF8-control+AF8-status +AD0APQ- -1) +AHs-
          hr+AF8-out+AF8-status +AD0- 0xFF+ADs-
       +AH0- else if(ppg+AF8-control+AF8-status +AD0APQ- 0) +AHs-
          hr+AF8-out+AF8-status +AD0- 0+ADs-
       +AH0- else if(ppg+AF8-control+AF8-status+AD0APQ-1) +AHs-
          hr+AF8-out+AF8-status +AD0- 1+ADs-
       +AH0-
    +AH0-

+ACM-if defined(OHRM+AF8-DEBUG+AF8-STATUS)
    switch(dbg+AF8-ohrm+AF8-switch)+AHs-
    case 1: // PPG1 config status
        // 2'b01  3'b ambdac+AF8-ppg  3'b ambdac+AF8-amb  2'b0  3'b tia2  3'b tia1  8'b led   8'b confidence
        hrm+AF8-data-+AD4-heart+AF8-rate+AF8-t.status +AD0- 0x40000000+ADs-
        hrm+AF8-data-+AD4-heart+AF8-rate+AF8-t.status +AD0- hr+AF8-out+AF8-status+ADs-

        ppg+AF8-reg+AF8-info.reg  +AD0- 0x2C+ADs-
        ppg+AF8-reg+AF8-info.addr +AD0- 0x33+ADs-
        ppg+AF8-reg+AF8-info.data+AF8-buf +AD0- (uint8+AF8-t +ACo-)+ACY-ohrm+AF8-reg+AF8-tx+ADs-
        ppg+AF8-reg+AF8-info.length +AD0- sizeof(ohrm+AF8-reg+AF8-tx)+ADs-
        vsm+AF8-driver+AF8-read+AF8-register(+ACY-ppg+AF8-reg+AF8-info)+ADs-

        ppg+AF8-reg+AF8-info.reg  +AD0- 0x18+ADs-
        ppg+AF8-reg+AF8-info.addr +AD0- 0x33+ADs-
        ppg+AF8-reg+AF8-info.data+AF8-buf +AD0- (uint8+AF8-t +ACo-)+ACY-ohrm+AF8-reg+AF8-rx+ADs-
        ppg+AF8-reg+AF8-info.length +AD0- sizeof(ohrm+AF8-reg+AF8-rx)+ADs-
        vsm+AF8-driver+AF8-read+AF8-register(+ACY-ppg+AF8-reg+AF8-info)+ADs-

        hrm+AF8-data-+AD4-heart+AF8-rate+AF8-t.status +AD0- (ohrm+AF8-reg+AF8-tx +ACY- 0x000000FF)+ADwAPA-8+ADs-//LED1
        hrm+AF8-data-+AD4-heart+AF8-rate+AF8-t.status +AD0- (ohrm+AF8-reg+AF8-rx +ACY- 0x00000007)+ADwAPA-16+ADs-//tia1
        hrm+AF8-data-+AD4-heart+AF8-rate+AF8-t.status +AD0- ((ohrm+AF8-reg+AF8-rx +ACY- 0x00000038)+AD4APg-3)+ADwAPA-19+ADs-//tia2
        hrm+AF8-data-+AD4-heart+AF8-rate+AF8-t.status +AD0- ((ohrm+AF8-reg+AF8-rx +ACY- 0x0E000000)+AD4APg-25)+ADwAPA-24+ADs-//ambdac+AF8-amb
        hrm+AF8-data-+AD4-heart+AF8-rate+AF8-t.status +AD0- ((ohrm+AF8-reg+AF8-rx +ACY- 0x01C00000)+AD4APg-22)+ADwAPA-27+ADs-//ambdac+AF8-ppg
        break+ADs-
    case 2: //SW status from adapter
        // 2'b10  6'b SW flag  3'b0  13'b fs+AF8-ratio  8'b confidence
        hrm+AF8-data-+AD4-heart+AF8-rate+AF8-t.status +AD0- 0x80000000+ADs-
        hrm+AF8-data-+AD4-heart+AF8-rate+AF8-t.status +AD0- hr+AF8-out+AF8-status+ADs-
        hrm+AF8-data-+AD4-heart+AF8-rate+AF8-t.status +AD0- (ohrm+AF8-fs+AF8-acc+AF8-div+AF8-ppg +ACY- 0x00001FFF) +ADwAPA- 8+ADs-
        +ACM-if defined(OHRM+AF8-DEBUG+AF8-ADAPTER)
        +ACM-if (FS+AF8-ACC+AF8-HZ+AD0APQ-100)
            hrm+AF8-data-+AD4-heart+AF8-rate+AF8-t.status +AD0- ((((dbg+AF8-cnt+AF8-acc+AF8-ip+ADwAPA-2)+dbgAXw-cnt+AF8-acc+AF8-ip)+AD4-((dbg+AF8-cnt+AF8-ppg+AF8-ip+ADwAPA-2)-dbg+AF8-cnt+AF8-ppg+AF8-ip))?1:0)+ADwAPA-24+ADs-
            hrm+AF8-data-+AD4-heart+AF8-rate+AF8-t.status +AD0- (((dbg+AF8-cnt+AF8-ppg+AF8-ip+ADwAPA-2)+AD4-((dbg+AF8-cnt+AF8-acc+AF8-ip+ADwAPA-4)-dbg+AF8-cnt+AF8-acc+AF8-ip))?1:0)+ADwAPA-25+ADs-
        +ACM-elif (FS+AF8-ACC+AF8-HZ+AD0APQ-125 +AHwAfA- FS+AF8-ACC+AF8-HZ+AD0APQ-128)
            hrm+AF8-data-+AD4-heart+AF8-rate+AF8-t.status +AD0- ((dbg+AF8-cnt+AF8-acc+AF8-ip+AD4-(dbg+AF8-cnt+AF8-ppg+AF8-ip-(dbg+AF8-cnt+AF8-ppg+AF8-ip+AD4APg-2)))?1:0)+ADwAPA-24+ADs-
            hrm+AF8-data-+AD4-heart+AF8-rate+AF8-t.status +AD0- ((dbg+AF8-cnt+AF8-ppg+AF8-ip+AD4-((dbg+AF8-cnt+AF8-acc+AF8-ip+ADwAPA-1)+dbgAXw-cnt+AF8-acc+AF8-ip))?1:0)+ADwAPA-25+ADs-
        +ACM-endif
        hrm+AF8-data-+AD4-heart+AF8-rate+AF8-t.status +AD0- ((dbg+AF8-cnt+AF8-neg+AF8-ts+AF8-acc+AD4-OHRM+AF8-DBG+AF8-NEG+AF8-TS+AF8-MAX)?1:0)+ADwAPA-26+ADs-
        hrm+AF8-data-+AD4-heart+AF8-rate+AF8-t.status +AD0- ((dbg+AF8-cnt+AF8-neg+AF8-ts+AF8-ppg+AD4-OHRM+AF8-DBG+AF8-NEG+AF8-TS+AF8-MAX)?1:0)+ADwAPA-27+ADs-
        hrm+AF8-data-+AD4-heart+AF8-rate+AF8-t.status +AD0- ((dbg+AF8-cnt+AF8-err+AF8-ts+AF8-acc+AD4-OHRM+AF8-DBG+AF8-ERR+AF8-TS+AF8-MAX)?1:0)+ADwAPA-28+ADs-
        hrm+AF8-data-+AD4-heart+AF8-rate+AF8-t.status +AD0- ((dbg+AF8-cnt+AF8-err+AF8-ts+AF8-ppg+AD4-OHRM+AF8-DBG+AF8-ERR+AF8-TS+AF8-MAX)?1:0)+ADwAPA-29+ADs-
        break+ADs-
        +ACM-endif //+ACM-if defined(OHRM+AF8-DEBUG+AF8-ADAPTER)
    case 3: // called at initial stage
        //2'b11  6'b0  8b ohrm ver  8b ppg control ver  8'b
        hrm+AF8-data-+AD4-heart+AF8-rate+AF8-t.status +AD0- 0xC0000000+ADs-
        hrm+AF8-data-+AD4-heart+AF8-rate+AF8-t.status +AD0- 0+ADs-
        hrm+AF8-data-+AD4-heart+AF8-rate+AF8-t.status +AD0- (ohrm+AF8-get+AF8-version() +ACY- 0x000000FF)+ADwAPA-16+ADs-
        hrm+AF8-data-+AD4-heart+AF8-rate+AF8-t.status +AD0- (ppg+AF8-control+AF8-get+AF8-version() +ACY- 0x000000FF)+ADwAPA-8+ADs-
        break+ADs-
    default: //ohrm lib status
        hrm+AF8-data-+AD4-heart+AF8-rate+AF8-t.status +AD0- hr+AF8-out+AF8-status+ADs-
        hrm+AF8-data-+AD4-heart+AF8-rate+AF8-t.status +AD0- ohrm+AF8-get+AF8-confidence+AF8-level() +ACY- 0x3FFFFF00+ADs-
    +AH0-
+ACM-else
    hrm+AF8-data-+AD4-heart+AF8-rate+AF8-t.status +AD0- hr+AF8-out+AF8-status+ADs-
    hrm+AF8-data-+AD4-heart+AF8-rate+AF8-t.status +AD0- ohrm+AF8-get+AF8-confidence+AF8-level() +ACY- 0x3FFFFF00+ADs-
+ACM-endif //+ACM-if defined(OHRM+AF8-DEBUG+AF8-STATUS)

+ACM-else
    hrm+AF8-data-+AD4-time+AF8-stamp +AD0- 0+ADs-
    hrm+AF8-data-+AD4-heart+AF8-rate+AF8-t.bpm +AD0- 80+ADs-
+ACM-endif //+ACM-if defined(OHRM+AF8-ON)

    return 1+ADs-
+AH0-

static int32+AF8-t heart+AF8-rate+AF8-monitor+AF8-process+AF8-data(const sensor+AF8-data+AF8-t +ACo-input+AF8-list, void +ACo-reserve)
+AHs-
+ACM-if defined(OHRM+AF8-ON)
    int32+AF8-t var+ADs-
    int32+AF8-t count +AD0- input+AF8-list-+AD4-data+AF8-exist+AF8-count+ADs-
    sensor+AF8-data+AF8-unit+AF8-t +ACo-data+AF8-start +AD0- input+AF8-list-+AD4-data+ADs-
    uint32+AF8-t input+AF8-sensor+AF8-type +AD0- input+AF8-list-+AD4-data-+AD4-sensor+AF8-type+ADs-
    uint32+AF8-t input+AF8-time+AF8-stamp +AD0- input+AF8-list-+AD4-data-+AD4-time+AF8-stamp+ADs-

    //OHRM lib
    ohrm+AF8-data+AF8-t param+AF8-ppg1+ADs-
    ohrm+AF8-data+AF8-t param+AF8-motion+ADs-
    int32+AF8-t ohrm+AF8-out+AFs-OHRM+AF8-OUT+AF8-LENGTH+AF0AOw-

    //ppg control
+ACM-if defined(OHRM+AF8-PPG+AF8-CTRL+AF8-ON)
    ppg+AF8-control+AF8-t ppg1+AF8-ctrl+AF8-input+ADs-
    int32+AF8-t ppg+AF8-control+AF8-output+AFs-OHRM+AF8-PPG+AF8-CTRL+AF8-OUT+AF8-LENGTH+AF0AOw-
+ACM-if defined(OHRM+AF8-ADJUST+AF8-NOTIFIER)
    int32+AF8-t control+AF8-flag +AD0- 0+ADs-
+ACM-endif //+ACM-if defined(OHRM+AF8-ADJUST+AF8-NOTIFIER)
+ACM-endif //+ACM-if defined(OHRM+AF8-PPG+AF8-CTRL+AF8-ON)

    if(input+AF8-sensor+AF8-type +AD0APQ- SENSOR+AF8-TYPE+AF8-ACCELEROMETER)+AHs-
        while (count +ACEAPQ- 0) +AHs-
            input+AF8-time+AF8-stamp +AD0- (data+AF8-start)-+AD4-time+AF8-stamp+ADs-
            // combine motion signal, be aware of overflow for bitwidth +ACEAPQ- 32
            var +AD0- (data+AF8-start)-+AD4-accelerometer+AF8-t.x  (data+AF8-start)-+AD4-accelerometer+AF8-t.y  (data+AF8-start)-+AD4-accelerometer+AF8-t.z+ADs-

            if(ohrm+AF8-adap+AF8-init+AF8-motion +AD0APQ- 0)+AHs-
                ohrm+AF8-adap+AF8-init+AF8-motion +AD0- 1+ADs-
+ACM-if (FS+AF8-ACC+AF8-HZ +AD0APQ- 50 +AHwAfA- FS+AF8-ACC+AF8-HZ +AD0APQ- 62 +AHwAfA- FS+AF8-ACC+AF8-HZ+AD0APQ-64)
            +AH0- else +AHs-
+ACM-if defined(OHRM+AF8-MOTION+AF8-ON)
                ohrm+AF8-adapt+AF8-buf+AF8-motion+AFs-ohrm+AF8-adapt+AF8-idx+AF8-motion+AF0- +AD0- (ohrm+AF8-adapt+AF8-pre+AF8-val+AF8-motion  var  1) +AD4APg- 1+ADs-
+ACM-else
                ohrm+AF8-adapt+AF8-buf+AF8-motion+AFs-ohrm+AF8-adapt+AF8-idx+AF8-motion+AF0- +AD0- 0+ADs-
+ACM-endif //+ACM-if defined(OHRM+AF8-MOTION+AF8-ON)
                ohrm+AF8-adapt+AF8-idx+AF8-motion+ADs-
+ACM-endif //+ACM-if (FS+AF8-ACC+AF8-HZ +AD0APQ- 50 +AHwAfA- FS+AF8-ACC+AF8-HZ +AD0APQ- 62 +AHwAfA- FS+AF8-ACC+AF8-HZ+AD0APQ-64)
            +AH0-

+ACM-if defined(OHRM+AF8-MOTION+AF8-ON)
            ohrm+AF8-adapt+AF8-buf+AF8-motion+AFs-ohrm+AF8-adapt+AF8-idx+AF8-motion+AF0- +AD0- var+ADs-
+ACM-else
            ohrm+AF8-adapt+AF8-buf+AF8-motion+AFs-ohrm+AF8-adapt+AF8-idx+AF8-motion+AF0- +AD0- 0+ADs-
+ACM-endif
            ohrm+AF8-adapt+AF8-pre+AF8-val+AF8-motion +AD0- var+ADs-
            ohrm+AF8-adapt+AF8-idx+AF8-motion+ADs-

            //check time stamp
            ms+AF8-fps+AF8-statistic+AF8-update(ohrm+AF8-adapt+AF8-pre+AF8-ts+AF8-motion, input+AF8-time+AF8-stamp, ohrm+AF8-adapt+AF8-idx+AF8-motion)+ADs-
+ACM-if defined(OHRM+AF8-DEBUG+AF8-ADAPTER)
            dbg+AF8-cnt+AF8-acc+AF8-ip+ADs-
            if(input+AF8-time+AF8-stamp +ADw- ohrm+AF8-adapt+AF8-pre+AF8-ts+AF8-motion)+AHs-
                dbg+AF8-cnt+AF8-neg+AF8-ts+AF8-acc+ADs-
            +AH0-else if((input+AF8-time+AF8-stamp - ohrm+AF8-adapt+AF8-pre+AF8-ts+AF8-motion) +AD4- (HEART+AF8-RATE+AF8-MONITOR+AF8-ACC+AF8-DELAY+ADwAPA-1))+AHs-
                dbg+AF8-cnt+AF8-err+AF8-ts+AF8-acc+ADs-
            +AH0-
+ACM-endif //+ACM-if defined(OHRM+AF8-DEBUG+AF8-ADAPTER)
            ohrm+AF8-adapt+AF8-pre+AF8-ts+AF8-motion +AD0- input+AF8-time+AF8-stamp+ADs-

            // Call OHRM: acc (motion) part
            if(ohrm+AF8-adapt+AF8-idx+AF8-motion +AD4APQ- 1)+AHs-
                param+AF8-motion.data +AD0- ohrm+AF8-adapt+AF8-buf+AF8-motion+ADs-
+ACM-if (FS+AF8-ACC+AF8-HZ +AD0APQ- 50 +AHwAfA- FS+AF8-ACC+AF8-HZ +AD0APQ- 100)
                param+AF8-motion.data+AF8-fs +AD0- 100+ADs-
+ACM-else
                param+AF8-motion.data+AF8-fs +AD0- 125+ADs-
+ACM-endif
                param+AF8-motion.data+AF8-length +AD0- ohrm+AF8-adapt+AF8-idx+AF8-motion+ADs-
                param+AF8-motion.data+AF8-bit+AF8-width +AD0- ACC+AF8-BITWIDTH+ADs-
                param+AF8-motion.data+AF8-config +AD0- 0+ADs-
                param+AF8-motion.data+AF8-source +AD0- 0+ADs- // motion
+ACM-if defined(OHRM+AF8-DYNAMIC+AF8-FS+AF8-RATIO+AF8-ON)
                ohrm+AF8-process(+ACY-param+AF8-motion, ohrm+AF8-fs+AF8-acc+AF8-div+AF8-ppg, ohrm+AF8-out)+ADs-
+ACM-else
                ohrm+AF8-process(+ACY-param+AF8-motion, MOTION+AF8-PPG+AF8-RATIO+AF8-DEFAULT, ohrm+AF8-out)+ADs-
+ACM-endif
                ohrm+AF8-adapt+AF8-idx+AF8-motion +AD0- 0+ADs-
            +AH0-
            data+AF8-start+ADs-
            count--+ADs-
        +AH0-
    +AH0- else if(input+AF8-sensor+AF8-type +AD0APQ- SENSOR+AF8-TYPE+AF8-BIOSENSOR+AF8-PPG1)+AHs-
        //store input data
        while (count +ACEAPQ- 0) +AHs-
            input+AF8-time+AF8-stamp +AD0- (data+AF8-start)-+AD4-time+AF8-stamp+ADs-
            var +AD0- (data+AF8-start)-+AD4-bio+AF8-data.data+ADs-
            if(var +AD4APQ- (1 +ADwAPA- (PPG+AF8-BITWIDTH-1))) +AHs-
                var -+AD0- (1 +ADwAPA- PPG+AF8-BITWIDTH)+ADs-
            +AH0-

+ACM-if defined(OHRM+AF8-DEBUG+AF8-ADAPTER)
            if(dbg+AF8-cnt+AF8-ppg+AF8-ip +AD4- (1+ADwAPA-28))+AHs-
                dbg+AF8-cnt+AF8-ppg+AF8-ip +AD0- 0+ADs-
                dbg+AF8-cnt+AF8-acc+AF8-ip +AD0- 0+ADs-
            +AH0-
            dbg+AF8-cnt+AF8-ppg+AF8-ip+ADs-
+ACM-endif //+ACM-if defined(OHRM+AF8-DEBUG+AF8-ADAPTER)

            if((ohrm+AF8-adapt+AF8-idx+AF8-ppg +ACY- 0x00000001) +AD0APQ- 0)+AHs-
+ACM-if defined(OHRM+AF8-DEBUG+AF8-ADAPTER)
                if(input+AF8-time+AF8-stamp +ADw- ohrm+AF8-adapt+AF8-pre+AF8-ts+AF8-ppg)+AHs-
                    dbg+AF8-cnt+AF8-neg+AF8-ts+AF8-ppg+ADs-
                +AH0-else if((input+AF8-time+AF8-stamp - ohrm+AF8-adapt+AF8-pre+AF8-ts+AF8-ppg) +AD4- HEART+AF8-RATE+AF8-MONITOR+AF8-PPG1+AF8-DELAY+AF8-MARGIN)+AHs-
                    dbg+AF8-cnt+AF8-err+AF8-ts+AF8-ppg+ADs-
                +AH0-
                ohrm+AF8-adapt+AF8-pre+AF8-ts+AF8-ppg +AD0- input+AF8-time+AF8-stamp+ADs-
+ACM-endif //+ACM-if defined(OHRM+AF8-DEBUG+AF8-ADAPTER)
                ohrm+AF8-adapt+AF8-pre+AF8-val+AF8-ppg +AD0- ohrm+AF8-adapt+AF8-cur+AF8-val+AF8-ppg+ADs-
                ohrm+AF8-adapt+AF8-cur+AF8-val+AF8-ppg +AD0- var+ADs-
            +AH0-

+ACM-if (FS+AF8-PPG+AF8-HZ +AD0APQ- 64)
            if((ohrm+AF8-adapt+AF8-idx+AF8-ppg +ACY- 0x00000001) +AD0APQ- 1) +AHs-
                if(ohrm+AF8-adap+AF8-init+AF8-ppg +AD0APQ- 0) +AHs-
                    ohrm+AF8-adap+AF8-init+AF8-ppg +AD0- 1+ADs-
                    ohrm+AF8-adapter+AF8-ts +AD0- input+AF8-time+AF8-stamp+ADs-
                +AH0- else +AHs-
                    ohrm+AF8-adapt+AF8-idx+AF8-ppg--+ADs-
                    ohrm+AF8-adapt+AF8-buf+AF8-ppg+AFs-ohrm+AF8-adapt+AF8-idx+AF8-ppg+AF0- +AD0- (ohrm+AF8-adapt+AF8-pre+AF8-val+AF8-ppg  ohrm+AF8-adapt+AF8-cur+AF8-val+AF8-ppg  1) +AD4APg- 1+ADs-
                    ohrm+AF8-adapt+AF8-idx+AF8-ppg+ADs-
                    ohrm+AF8-adapt+AF8-buf+AF8-ppg+AFs-ohrm+AF8-adapt+AF8-idx+AF8-ppg+AF0- +AD0- (ohrm+AF8-adapt+AF8-pre+AF8-val+AF8-amb  var  1) +AD4APg- 1+ADs-
                    ohrm+AF8-adapt+AF8-idx+AF8-ppg+ADs-
                    ohrm+AF8-adapt+AF8-buf+AF8-ppg+AFs-ohrm+AF8-adapt+AF8-idx+AF8-ppg+AF0- +AD0- ohrm+AF8-adapt+AF8-cur+AF8-val+AF8-ppg+ADs-
                    ohrm+AF8-adapt+AF8-idx+AF8-ppg+ADs-
                +AH0-
                ohrm+AF8-adapt+AF8-pre+AF8-val+AF8-amb +AD0- var+ADs-
            +AH0-
+ACM-endif //+ACM-if (FS+AF8-PPG+AF8-HZ +AD0APQ- 64)

            ohrm+AF8-adapt+AF8-buf+AF8-ppg+AFs-ohrm+AF8-adapt+AF8-idx+AF8-ppg+AF0- +AD0- var+ADs-
            ohrm+AF8-adapt+AF8-idx+AF8-ppg+ADs-
            ohrm+AF8-adapter+AF8-timer+ADs-

            if(ohrm+AF8-adapt+AF8-idx+AF8-ppg +AD4APQ- (PPG+AF8-BUF+AF8-SIZE))+AHs-
                // Call PPG Control
+ACM-if defined(OHRM+AF8-PPG+AF8-CTRL+AF8-ON)
                ppg1+AF8-ctrl+AF8-input.input +AD0- ohrm+AF8-adapt+AF8-buf+AF8-ppg+ADs-
                ppg1+AF8-ctrl+AF8-input.input+AF8-fs +AD0- 128+ADs-
                ppg1+AF8-ctrl+AF8-input.input+AF8-length +AD0- ohrm+AF8-adapt+AF8-idx+AF8-ppg+ADs-
                ppg1+AF8-ctrl+AF8-input.input+AF8-bit+AF8-width +AD0- 32+ADs-
                ppg1+AF8-ctrl+AF8-input.input+AF8-config +AD0- 1+ADs-
                ppg1+AF8-ctrl+AF8-input.input+AF8-source +AD0- 1+ADs-
+ACM-if defined(OHRM+AF8-ADJUST+AF8-NOTIFIER)
                control+AF8-flag +AD0- ppg+AF8-control+AF8-process(+ACY-ppg1+AF8-ctrl+AF8-input, PPG+AF8-CONTROL+AF8-MODE+AF8-DUAL1, ppg+AF8-control+AF8-output)+ADs-
+ACM-else
                ppg+AF8-control+AF8-process(+ACY-ppg1+AF8-ctrl+AF8-input, PPG+AF8-CONTROL+AF8-MODE+AF8-DUAL1, ppg+AF8-control+AF8-output)+ADs-
+ACM-endif //+ACM-if defined(OHRM+AF8-ADJUST+AF8-NOTIFIER)
+ACM-endif //+ACM-if defined(OHRM+AF8-PPG+AF8-CTRL+AF8-ON)
                // Call OHRM: PPG part
                ohrm+AF8-fs+AF8-acc+AF8-div+AF8-ppg +AD0- update+AF8-motion+AF8-ppg+AF8-sample+AF8-time+AF8-ratio()+ADs-
                param+AF8-ppg1.data +AD0- ohrm+AF8-adapt+AF8-buf+AF8-ppg+ADs-
                param+AF8-ppg1.data+AF8-fs +AD0- 128+ADs-
                param+AF8-ppg1.data+AF8-length +AD0- ohrm+AF8-adapt+AF8-idx+AF8-ppg+ADs-
                param+AF8-ppg1.data+AF8-bit+AF8-width +AD0- 32+ADs-
                param+AF8-ppg1.data+AF8-config +AD0- 2+ADs-
+ACM-if defined(OHRM+AF8-ADJUST+AF8-NOTIFIER)
                if(ohrm+AF8-control+AF8-flag +AD0APQ- 1) +AHs-
                    param+AF8-ppg1.data+AF8-source +AD0- 3+ADs- // ppg with setting changed
                +AH0- else +AHs-
                    param+AF8-ppg1.data+AF8-source +AD0- 1+ADs- // ppg
                +AH0-
+ACM-else
                param+AF8-ppg1.data+AF8-source +AD0- 1+ADs-
+ACM-endif //+ACM-if defined(OHRM+AF8-ADJUST+AF8-NOTIFIER)

+ACM-if defined(OHRM+AF8-DYNAMIC+AF8-FS+AF8-RATIO+AF8-ON)
                ohrm+AF8-process(+ACY-param+AF8-ppg1, ohrm+AF8-fs+AF8-acc+AF8-div+AF8-ppg, ohrm+AF8-out)+ADs-
+ACM-else
                ohrm+AF8-process(+ACY-param+AF8-ppg1, MOTION+AF8-PPG+AF8-RATIO+AF8-DEFAULT, ohrm+AF8-out)+ADs-
+ACM-endif
                ohrm+AF8-adapt+AF8-idx+AF8-ppg +AD0- 0+ADs-

+ACM-if defined(OHRM+AF8-ADJUST+AF8-NOTIFIER)
                if(control+AF8-flag +AD0APQ- 1) +AHs-
                    ohrm+AF8-control+AF8-flag +AD0- 1+ADs-
                +AH0- else +AHs-
                    ohrm+AF8-control+AF8-flag +AD0- 0+ADs-
                +AH0-
+ACM-endif //+ACM-if defined(OHRM+AF8-ADJUST+AF8-NOTIFIER)
            +AH0-

            if(ohrm+AF8-adapter+AF8-timer +AD4APQ- (FS+AF8-PPG+AF8-HZ+ADwAPA-1))+AHs-
                ohrm+AF8-adapter+AF8-ts +AD0- (data+AF8-start)-+AD4-time+AF8-stamp+ADs-
                ohrm+AF8-adapter+AF8-timer -+AD0- (FS+AF8-PPG+AF8-HZ+ADwAPA-1)+ADs-
                dbg+AF8-cnt+AF8-5sec+ADs-
                // notify sensor manager
                dbg+AF8-ohrm+AF8-switch +AD0- 0+ADs-
                sensor+AF8-fusion+AF8-algorithm+AF8-notify(SENSOR+AF8-TYPE+AF8-HEART+AF8-RATE+AF8-MONITOR)+ADs-
+ACM-if defined(OHRM+AF8-DEBUG+AF8-STATUS)
                dbg+AF8-ohrm+AF8-switch +AD0- 1+ADs-
                sensor+AF8-fusion+AF8-algorithm+AF8-notify(SENSOR+AF8-TYPE+AF8-HEART+AF8-RATE+AF8-MONITOR)+ADs-
+ACM-endif //+ACM-if defined(OHRM+AF8-DEBUG+AF8-STATUS)
            +AH0-

            if(dbg+AF8-cnt+AF8-5sec+AD0APQ-5)+AHs-
                dbg+AF8-cnt+AF8-5sec +AD0- 0+ADs-
+ACM-if defined(OHRM+AF8-DEBUG+AF8-STATUS)
                dbg+AF8-ohrm+AF8-switch +AD0- 2+ADs-
                sensor+AF8-fusion+AF8-algorithm+AF8-notify(SENSOR+AF8-TYPE+AF8-HEART+AF8-RATE+AF8-MONITOR)+ADs-
+ACM-endif //+ACM-if defined(OHRM+AF8-DEBUG+AF8-STATUS)
            +AH0-

            data+AF8-start+ADs-
            count--+ADs-
        +AH0-
    +AH0-
    else+AHs-
    // error handling
    +AH0-
+ACM-endif //+ACM-if defined(OHRM+AF8-ON)

    return 1+ADs-
+AH0-

static int32+AF8-t heart+AF8-rate+AF8-monitor+AF8-operate(int32+AF8-t command, void +ACo-buffer+AF8-out, int32+AF8-t size+AF8-out, +AFw-
                                 void +ACo-buffer+AF8-in, int32+AF8-t size+AF8-in)
+AHs-
    return 0+ADs-
+AH0-

const sensor+AF8-descriptor+AF8-t heart+AF8-rate+AF8-monitor+AF8-desp +AD0- +AHs-
    SENSOR+AF8-TYPE+AF8-HEART+AF8-RATE+AF8-MONITOR, //output+AF8-type
    1, /+ACo- version +ACo-/
    SENSOR+AF8-REPORT+AF8-MODE+AF8-ON+AF8-CHANGE, /+ACo- report+AF8-mode +ACo-/
    +ACY-input+AF8-heart+AF8-rate+AF8-monitor+AF8-comp+AF8-acc, /+ACo- sensor+AF8-input+AF8-list+AF8-t +ACo-/
    heart+AF8-rate+AF8-monitor+AF8-operate,
    get+AF8-heart+AF8-rate+AF8-monitor+AF8-result,
    heart+AF8-rate+AF8-monitor+AF8-process+AF8-data,
    0 /+ACo- accumulate +ACo-/
+AH0AOw-

int heart+AF8-rate+AF8-monitor+AF8-register(void)
+AHs-
    int ret+ADs- /+ACo-return: fail+AD0--1, pass+AD4APQ-0, which means the count of current register algorithm +ACo-/

    input+AF8-heart+AF8-rate+AF8-monitor+AF8-comp+AF8-acc.input+AF8-type +AD0- SENSOR+AF8-TYPE+AF8-ACCELEROMETER+ADs-
    input+AF8-heart+AF8-rate+AF8-monitor+AF8-comp+AF8-acc.sampling+AF8-delay +AD0- HEART+AF8-RATE+AF8-MONITOR+AF8-ACC+AF8-DELAY+ADs- // ms
    input+AF8-heart+AF8-rate+AF8-monitor+AF8-comp+AF8-acc.timeout +AD0- HEART+AF8-RATE+AF8-MONITOR+AF8-ACC+AF8-POLLING+AF8-TIME+ADs- // ms

    input+AF8-heart+AF8-rate+AF8-monitor+AF8-comp+AF8-bio.input+AF8-type +AD0- SENSOR+AF8-TYPE+AF8-BIOSENSOR+AF8-PPG1+ADs-
    input+AF8-heart+AF8-rate+AF8-monitor+AF8-comp+AF8-bio.sampling+AF8-delay +AD0- HEART+AF8-RATE+AF8-MONITOR+AF8-PPG1+AF8-DELAY+ADs- // ms
    input+AF8-heart+AF8-rate+AF8-monitor+AF8-comp+AF8-bio.timeout +AD0- HEART+AF8-RATE+AF8-MONITOR+AF8-PPG1+AF8-POLLING+AF8-TIME+ADs- // ms

    input+AF8-heart+AF8-rate+AF8-monitor+AF8-comp+AF8-acc.next+AF8-input +AD0- +ACY-input+AF8-heart+AF8-rate+AF8-monitor+AF8-comp+AF8-bio+ADs- // build as a signal linked list
    input+AF8-heart+AF8-rate+AF8-monitor+AF8-comp+AF8-bio.next+AF8-input +AD0- NULL+ADs-

    ret +AD0- sensor+AF8-fusion+AF8-algorithm+AF8-register+AF8-type(+ACY-heart+AF8-rate+AF8-monitor+AF8-desp)+ADs-
    if (ret +ADw- 0) +AHs-
        LOGE(+ACI-fail to register heart rate monitor +AFw-r+AFw-n+ACI-)+ADs-
    +AH0-
    ret +AD0- sensor+AF8-fusion+AF8-algorithm+AF8-register+AF8-data+AF8-buffer(SENSOR+AF8-TYPE+AF8-HEART+AF8-RATE+AF8-MONITOR, 1)+ADs-
    if (ret +ADw- 0) +AHs-
        LOGE(+ACI-fail to register buffer +AFw-r+AFw-n+ACI-)+ADs-
    +AH0-
    return ret+ADs-
+AH0-

int heart+AF8-rate+AF8-monitor+AF8-init(void)
+AHs-
    // Call PPG control lib init
+ACM-if defined(OHRM+AF8-PPG+AF8-CTRL+AF8-ON)
    ppg+AF8-control+AF8-get+AF8-version+AF8-string()+ADs- //PPG+AF8-CONTROL+AF8-v1.0.0.xx
    ppg+AF8-control+AF8-init()+ADs-
    ppg+AF8-control+AF8-set+AF8-app(PPG+AF8-CONTROL+AF8-APP+AF8-OHRM)+ADs-
+ACM-endif //+ACM-if defined(OHRM+AF8-PPG+AF8-CTRL+AF8-ON)

    // Call HR lib init
+ACM-if defined(OHRM+AF8-ON)
    ohrm+AF8-get+AF8-version+AF8-string()+ADs- //OHRM+AF8-v1.0.0.xx
    ohrm+AF8-init(ACC+AF8-UNIT+AF8-LSB+AF8-1G)+ADs-
    ohrm+AF8-adapter+AF8-timer +AD0- 0+ADs-
    ohrm+AF8-adapter+AF8-ts +AD0- 0+ADs-
    ohrm+AF8-adap+AF8-init+AF8-ppg +AD0- 0+ADs-
    ohrm+AF8-adap+AF8-init+AF8-motion +AD0- 0+ADs-
    ohrm+AF8-adapt+AF8-idx+AF8-ppg +AD0- 0+ADs-
    ohrm+AF8-adapt+AF8-idx+AF8-motion +AD0- 0+ADs-
    ohrm+AF8-adapt+AF8-cur+AF8-val+AF8-ppg +AD0- 0+ADs-
    ohrm+AF8-adapt+AF8-pre+AF8-val+AF8-ppg +AD0- 0+ADs-
    ohrm+AF8-adapt+AF8-pre+AF8-val+AF8-amb +AD0- 0+ADs-
    ohrm+AF8-adapt+AF8-pre+AF8-val+AF8-motion +AD0- 0+ADs-
    ohrm+AF8-adapt+AF8-pre+AF8-ts+AF8-motion +AD0- 0+ADs-

+ACM-if defined(OHRM+AF8-ADJUST+AF8-NOTIFIER)
    ohrm+AF8-control+AF8-flag +AD0- 0+ADs-
+ACM-endif //+ACM-if defined(OHRM+AF8-ADJUST+AF8-NOTIFIER)
+ACM-endif //+ACM-if defined(OHRM+AF8-ON)

    return 1+ADs-
+AH0-

+ACM-if defined(OHRM+AF8-ON)
// ACC/PPG fs+AF8-ratio calculation
void ms+AF8-fps+AF8-statistic+AF8-update(uint32+AF8-t ts+AF8-prevous, uint32+AF8-t ts+AF8-current, int32+AF8-t count)
+AHs-
    int32+AF8-t diff+ADs-
    if(ts+AF8-prevous +ACEAPQ- 0 +ACYAJg- count +AD4- 0) +AHs-
        diff +AD0- ((int32+AF8-t)(ts+AF8-current)) - ((int32+AF8-t)(ts+AF8-prevous))+ADs-
        if(diff +AD4- -1000 +ACYAJg- diff +ADw- 1000) +AHs-
            if((diff +AD4- 0)
                +AHwAfA- (diff +ADw- 0 +ACYAJg- motion+AF8-total+AF8-sample+AF8-interval +AD4- diff)) +AHs-
                motion+AF8-total+AF8-sample+AF8-interval +AD0- diff+ADs-
                motion+AF8-accumulated+AF8-count +AD0- count+ADs-
            +AH0-
        +AH0-
        // clean accumlated values over a certain time
        if (motion+AF8-accumulated+AF8-count +AD4- MOTION+AF8-PPG+AF8-RATIO+AF8-FORGET+AF8-LENGTH) +AHs-
            motion+AF8-accumulated+AF8-count +AD0- motion+AF8-accumulated+AF8-count +AD4APg- 1+ADs-
            motion+AF8-total+AF8-sample+AF8-interval +AD0- motion+AF8-total+AF8-sample+AF8-interval +AD4APg- 1+ADs-
        +AH0-
    +AH0-
+AH0-

uint32+AF8-t update+AF8-motion+AF8-ppg+AF8-sample+AF8-time+AF8-ratio(void)
+AHs-
    // Default fps, need to get info from sensor driver if changed
    uint64+AF8-t real+AF8-ppg+AF8-sample+AF8-time+ADs-
    uint64+AF8-t interval+AF8-100ns+ADs-
    uint64+AF8-t motion+AF8-ppg+AF8-freq+AF8-ratio+AF8-64 +AD0- MOTION+AF8-PPG+AF8-RATIO+AF8-DEFAULT+ADs-
    uint32+AF8-t motion+AF8-ppg+AF8-freq+AF8-ratio +AD0- MOTION+AF8-PPG+AF8-RATIO+AF8-DEFAULT+ADs-

    interval+AF8-100ns +AD0- ((uint64+AF8-t)motion+AF8-total+AF8-sample+AF8-interval) +ACo- (uint64+AF8-t)(10000)+ADs-
    real+AF8-ppg+AF8-sample+AF8-time +AD0- ((uint64+AF8-t)REAL+AF8-PPG+AF8-SAMPLE+AF8-INTERVAL+AF8-100NANOSEC) +ACo- ((uint64+AF8-t)motion+AF8-accumulated+AF8-count)+ADs-
    motion+AF8-ppg+AF8-freq+AF8-ratio+AF8-64 +AD0- ( (real+AF8-ppg+AF8-sample+AF8-time +ADwAPA- MOTION+AF8-PPG+AF8-RATIO+AF8-DECIMAL+AF8-POINT+AF8-BITS) / interval+AF8-100ns)+ADs-
    motion+AF8-ppg+AF8-freq+AF8-ratio +AD0- (uint32+AF8-t)(motion+AF8-ppg+AF8-freq+AF8-ratio+AF8-64 +ACY- 0xFFFFFFFF)+ADs-

    // Set boundary
    if(motion+AF8-ppg+AF8-freq+AF8-ratio +AD4- MOTION+AF8-PPG+AF8-RATIO+AF8-UPPER+AF8-BOUND) +AHs-
        motion+AF8-ppg+AF8-freq+AF8-ratio +AD0- MOTION+AF8-PPG+AF8-RATIO+AF8-UPPER+AF8-BOUND+ADs-
    +AH0- else if(motion+AF8-ppg+AF8-freq+AF8-ratio +ADw- MOTION+AF8-PPG+AF8-RATIO+AF8-LOWER+AF8-BOUND) +AHs-
        motion+AF8-ppg+AF8-freq+AF8-ratio +AD0- MOTION+AF8-PPG+AF8-RATIO+AF8-LOWER+AF8-BOUND+ADs-
    +AH0- else if(motion+AF8-ppg+AF8-freq+AF8-ratio +ADwAPQ- 0) +AHs-
    +AH0-
    return motion+AF8-ppg+AF8-freq+AF8-ratio+ADs-
+AH0-

void heart+AF8-rate+AF8-monitor+AF8-enable+AF8-watch+AF8-off+AF8-detection(uint8+AF8-t is+AF8-enable)
+AHs-
	watch+AF8-off+AF8-detection+AF8-enable +AD0- is+AF8-enable+ADs-
+AH0-
+ACM-endif //+ACM-if defined(OHRM+AF8-ON)

