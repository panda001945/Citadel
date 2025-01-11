//+------------------------------------------------------------------+
//| CitadelIndicator.mq5                                             |
//+------------------------------------------------------------------+
#property copyright "Your Name"
#property link      "Your Website"
#property version   "1.00"

#include <citadel_interface.mqh>

#property indicator_chart_window
#property indicator_buffers 1
#property indicator_plots   1

//--- plot Signal
#property indicator_label1  "Signal"
#property indicator_type1   DRAW_ARROW
#property indicator_color1  clrRed,clrLime
#property indicator_style1  STYLE_SOLID
#property indicator_width1  1

// Indicator buffer for signals
double SignalBuffer[];

// Initialization function
int OnInit()
{
   //--- indicator buffers mapping
   SetIndexBuffer(0, SignalBuffer, INDICATOR_DATA);
   PlotIndexSetInteger(0, PLOT_ARROW, 233); // Red arrow for Sell
   PlotIndexSetInteger(1, PLOT_ARROW, 234); // Green arrow for Buy
   
   // Initialize Citadel integration
   if(!CitadelInit())
   {
      Print("Failed to initialize Citadel integration for indicator");
      return(INIT_FAILED);
   }
   
   return(INIT_SUCCEEDED);
}

void OnDeinit(const int reason)
{
   CitadelDeinit();
}

int OnCalculate(const int rates_total,
                const int prev_calculated,
                const datetime &time[],
                const double &open[],
                const double &high[],
                const double &low[],
                const double &close[],
                const long &tick_volume[],
                const long &volume[],
                const int &spread[])
{
   // Determine which bars to calculate
   int start = 0;
   if(prev_calculated > 0) 
      start = prev_calculated - 1; // Continue from the last calculated bar

   // Loop through the bars
   for(int i = start; i < rates_total; i++)
   {
      // Reset the signal for this bar
      SignalBuffer[i] = EMPTY_VALUE;
      
      // Fetch the signal from Citadel for the current bar
      string signal = CitadelGetSignal();
      
      if(signal == "BUY")
      {
         SignalBuffer[i] = low[i] - 10 * _Point; // Place the buy signal arrow just below the low
      }
      else if(signal == "SELL")
      {
         SignalBuffer[i] = high[i] + 10 * _Point; // Place the sell signal arrow just above the high
      }
   }
   
   return(rates_total);
}