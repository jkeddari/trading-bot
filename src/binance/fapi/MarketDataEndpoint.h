#pragma once

#include "common/util/HTTP.h"
#include <common/external/json.hpp>
#include <string>
#include <fstream>

using json = nlohmann::json;

const std::string interval_value[]={"1m", "3m", "5m", "15m", "30m", "1h", "2h", "4h", "6h", "8h", "12h", "1d", "3d", "1w", "1M"};
enum interval {
  ONE_MINUTE, THREE_MINUTES, FIVE_MINUTES, FIVETEEN_MINUTES, THIRTY_MINUTES,
  ONE_HOUR, TWO_HOURS, FOUR_HOURS, SIX_HOURS, EIGHT_HOURS, TWELVE_HOURS,
  ONE_DAY, THREE_DAYS, ONE_WEEK, ONE_MONTH
};


namespace binance {

  class MarketDataEndpoint{
    private:
      util::HTTPSession http_client;
      std::string uri;
      std::string api_key;
      std::string api_secret;
      std::string subapi;

    public:
      MarketDataEndpoint();

      json ping();
      json time();
      json exchangeInfo();

      json orderbook(const std::string market, int depth = 100);
      json trades(const std::string market, int depth = 500);
      json historicalTrades(const std::string market, int limit=500, const long fromId=-1);
      json aggTrades(const std::string market, const long fromId=-1,const long startTime=-1,const long endTime=-1,int limit=500);
      json klines(const std::string market, enum interval inter, const long startTime=-1,const long endTime=-1, int limit=500);
      json premiumIndex(const std::string market="");
      json fundingRate(const std::string market,const long startTime=-1,const long endTime=-1,int limit=100);
      
      json ticker_oneday(const std::string market="");
      json ticker_price(const std::string market="");
      json ticker_book(const std::string market="");

      json allForceOrders(const std::string market="",const long startTime=-1,const long endTime=-1,int limit=100);
      json openInterest(const std::string market);
      json leverageBracket(const std::string market="");
  };

}
