//+------------------------------------------------------------------+
//| CitadelEA.mq5                                                    |
//+------------------------------------------------------------------+
#property copyright "Your Name"
#property link      "Your Website"
#property version   "1.00"

#include <citadel_interface.mqh>

input int MagicNumber = 12345;  // Magic number for trade identification

// Global variables for signal storage
string current_signal = "";

int OnInit()
{
   if(!CitadelInit())
   {
      Print("Failed to initialize Citadel integration");
      return(INIT_FAILED);
   }
   return(INIT_SUCCEEDED);
}

void OnDeinit(const int reason)
{
   CitadelDeinit();
}

void OnTick()
{
   // Update the signal from Citadel at each tick
   current_signal = CitadelGetSignal();
   
   if(current_signal == "BUY")
   {
      if(PositionsTotal() == 0) // Check if there's no open position
      {
         MqlTradeRequest request = {};
         MqlTradeResult result = {};
         request.action = TRADE_ACTION_DEAL;
         request.symbol = Symbol();
         request.volume = 0.1;
         request.type = ORDER_TYPE_BUY;
         request.price = SymbolInfoDouble(Symbol(), SYMBOL_ASK);
         request.deviation = 3;
         request.magic = MagicNumber;
         request.comment = "Buy Order";
         if(!OrderSend(request, result))
            Print("OrderSend error ",GetLastError());
         else
            Print("Buy order opened : ",result.order);
      }
   }
   else if(current_signal == "SELL")
   {
      if(PositionsTotal() == 0) // Check if there's no