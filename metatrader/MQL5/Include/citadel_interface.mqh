//+------------------------------------------------------------------+
//| citadel_interface.mqh                                            |
//+------------------------------------------------------------------+
#property copyright "Your Name"
#property link      "Your Website"
#property version   "1.00"

#import "citadel_api.dll"
   bool CitadelInit();
   void CitadelDeinit();
   string CitadelGetSignal();
#import

// Placeholder for any additional function definitions or macros