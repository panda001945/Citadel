//+------------------------------------------------------------------+
//| CitadelIndicator.mq4                                             |
//+------------------------------------------------------------------+
#property copyright "Your Name"
#property link      "Your Website"
#property version   "1.00"

#include <citadel_interface.mqh>

#property indicator_chart_window
#property indicator_buffers 1

//--- plot Signal
#property indicator_color1 clrRed,clrLime
#property indicator_width1 3

double SignalBuffer[];

// Initialization function
int init()
{
   //--- indicator buffers mapping
   SetIndexStyle(0, DRAW_ARROW, EMPTY, 0, 3); // Style for arrows
   SetIndexArrow(0, 233, clrRed); // Red arrow for Sell
   SetIndexArrow(1, 234, clrLime); // Green arrow for Buy
   SetIndexBuffer(0, SignalBuffer);
   
   // Initialize Citadel integration
   if(!CitadelInit())
   {
      Print("Failed to initialize Citadel integration for indicator");
      return(INIT_FAILED);
   }
   
   return(0);
}

// Deinitialization function
int deinit()
{
   CitadelDeinit();
   return(0);
}

// Main calculation function
int start()
{
   int counted_bars = IndicatorCounted(); // Number of bars already counted
   int limit;
   
   if(counted_bars == 0)
      limit = Bars - 1; // First run, calculate all bars
   else
      limit = Bars - counted_bars;

   for(int i = limit; i >= 0; i--)
   {
      string signal = CitadelGetSignal();
      
      // Reset the buffer
      SignalBuffer[i] = EMPTY_VALUE;
      
      if(signal == "BUY")
      {
         SignalBuffer[i] = Low[i] - 100 * Point; // Place buy signal below the low price
      }
      else if(signal == "SELL")
      {
         SignalBuffer[i] = High[i] + 100 * Point; // Place sell signal above the high price
      }
   }
   
   return(0);
}