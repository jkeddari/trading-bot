#include "binance/fapi/MarketDataEndpoint.h"

#include <iostream>

int main()
{
    binance::MarketDataEndpoint client;

    auto futs = client.ping();
    std::cout << futs << "\n";

    //auto time = client.time();
    //std::cout << time << "\n";

    //auto info = client.exchange_information();
    //std::cout << info << "\n";

    //auto ob = client.get_orderbook("BTCUSDT", 100);
    //std::cout << ob << "\n\n";

    //auto tl = client.recent_trade_list("BTCUSDT");
    //std::cout << tl << "\n\n";

    //auto oldtrade = client.historicalTrades("BTCUSDT");
    //std::cout << oldtrade << "\n\n";

    //auto price = client.premiumIndex("BTCUSDT");
    //std::cout << price << "\n\n";
    /*
    auto ticker = client.ticker_oneday();
    std::cout << ticker << "\n\n";

    auto ticker_p = client.ticker_price("BTCUSDT");
    std::cout << ticker_p << "\n\n";

    auto ticker_b = client.ticker_book("BTCUSDT");
    std::cout << ticker_b << "\n\n";
    */

}

