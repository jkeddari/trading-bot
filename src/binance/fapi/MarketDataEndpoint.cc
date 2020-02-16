#include "binance/fapi/MarketDataEndpoint.h"

#include <iostream>

namespace binance {

MarketDataEndpoint::MarketDataEndpoint(){
    json j;
    std::ifstream i("/workspaces/trading-bot/config/config.json");
    if(i){
        i >> j;
        uri=j["fapi"]["uri"];
        api_key=j["fapi"]["api_key"];
        api_secret=j["fapi"]["api_secret"];
        subapi=j["fapi"]["subapi"];
        http_client.configure(uri,api_key,api_secret,subapi);
    }
    else{
        std::cout << "Config file error\n";
        exit(1);
    }
}

json MarketDataEndpoint::ping(){
    auto response = http_client.get("ping");
    return json::parse(response.body());
}

json MarketDataEndpoint::time(){
    auto response = http_client.get("time");
    return json::parse(response.body());
}

json MarketDataEndpoint::exchangeInfo(){
    auto response = http_client.get("exchangeInfo");
    return json::parse(response.body());
}

json MarketDataEndpoint::orderbook(const std::string market, int limit){
    if(limit > 1000) limit = 1000;
    auto response = http_client.get( "depth?symbol="+market+"&limit="+std::to_string(limit));
    return json::parse(response.body());
}


json MarketDataEndpoint::trades(const std::string market, int limit){
    if(limit > 1000) limit = 1000;
    auto response = http_client.get( "trades?symbol="+market+"&limit="+std::to_string(limit));
    return json::parse(response.body());
}

json MarketDataEndpoint::historicalTrades(const std::string market, int limit, const long fromId){
    std::string id;
    if(fromId==-1) id="";
    else id=std::to_string(fromId);

    if(limit > 1000) limit=1000;

    std::string req="historicalTrades?symbol="+market+"&limit="+std::to_string(limit)+"&fromId="+id;
    
    auto response = http_client.get(req);

    return json::parse(response.body());
}


json MarketDataEndpoint::aggTrades(const std::string market, const long fromId, const long startTime, const long endTime, int limit){
    std::string id,start,end;
    if(fromId==-1) id=""; else id=std::to_string(fromId);
    if(startTime==-1) start=""; else start=std::to_string(startTime);
    if(endTime==-1) end=""; else end=std::to_string(endTime);
    if(limit > 1000) limit=1000;

    std::string req="aggTrades?symbol="+market+"&fromId="+id+"&startTime="+start+"&endTime="+end+"&limit="+std::to_string(limit);
    auto response = http_client.get(req);
    return json::parse(response.body());
}

json MarketDataEndpoint::klines(const std::string market, enum interval inter, const long startTime,const long endTime, int limit){
    std::string start,end,interval;
    if(startTime==-1) start=""; else start=std::to_string(startTime);
    if(endTime==-1) end=""; else end=std::to_string(endTime);
    if(limit > 1000) limit=1000;

    interval=interval_value[inter];
    std::string req="klines?symbol="+market+"&interval="+interval+"&startTime="+start+"&endTime="+end+"&limit="+std::to_string(limit);
    auto response = http_client.get(req);
    return json::parse(response.body());
}

json MarketDataEndpoint::premiumIndex(const std::string market){
    std::string req="premiumIndex?symbol="+market;
    auto response = http_client.get(req);
    return json::parse(response.body());
}

json MarketDataEndpoint::fundingRate(const std::string market,const long startTime,const long endTime,int limit){
    std::string start,end;
    if(startTime==-1) start=""; else start=std::to_string(startTime);
    if(endTime==-1) end=""; else end=std::to_string(endTime);
    if(limit > 1000) limit=1000;
    std::string req="klines?symbol="+market+"&startTime="+start+"&endTime="+end+"&limit="+std::to_string(limit);
    auto response = http_client.get(req);
    return json::parse(response.body());
}

json MarketDataEndpoint::ticker_oneday(const std::string market){
    std::string req="ticker/24hr?symbol="+market;
    auto response = http_client.get(req);
    return json::parse(response.body());
}

json MarketDataEndpoint::ticker_price(const std::string market){
    std::string req="ticker/price?symbol="+market;
    auto response = http_client.get(req);
    return json::parse(response.body());
}
json MarketDataEndpoint::ticker_book(const std::string market){
    std::string req="ticker/bookTicker?symbol="+market;
    auto response = http_client.get(req);
    return json::parse(response.body());
}

json MarketDataEndpoint::allForceOrders(const std::string market,const long startTime,const long endTime,int limit){
    std::string start,end;
    if(startTime==-1) start=""; else start=std::to_string(startTime);
    if(endTime==-1) end=""; else end=std::to_string(endTime);
    if(limit > 1000) limit=1000;
    std::string req="allForceOrders?symbol="+market+"&startTime="+start+"&endTime="+end+"&limit="+std::to_string(limit);
    auto response = http_client.get(req);
    return json::parse(response.body());
}

json MarketDataEndpoint::openInterest(const std::string market){
    std::string req="openInterest/bookTicker?symbol="+market;
    auto response = http_client.get(req);
    return json::parse(response.body());
}

json MarketDataEndpoint::leverageBracket(const std::string market){
    std::string req="leverageBracket/bookTicker?symbol="+market;
    auto response = http_client.get(req);
    return json::parse(response.body());
}


/*
json MarketDataEndpoint::list_futures(){
    auto response = http_client.get("futures");
    return json::parse(response.body());
}

json MarketDataEndpoint::list_markets()
{
    auto response = http_client.get("markets");
    return json::parse(response.body());
}



json MarketDataEndpoint::get_trades(const std::string market)
{
    auto response = http_client.get("markets/" + market + "/trades");
    return json::parse(response.body());
}

json MarketDataEndpoint::get_account_info()
{
    auto response = http_client.get("account");
    return json::parse(response.body());
}

json MarketDataEndpoint::get_open_orders()
{
    auto response = http_client.get("orders");
    return json::parse(response.body());
}

json MarketDataEndpoint::place_order(const std::string market,
                             const std::string side,
                             double price,
                             double size,
                             bool ioc,
                             bool post_only,
                             bool reduce_only)
{
    json payload = {{"market", market},
                    {"side", side},
                    {"price", price},
                    {"type", "limit"},
                    {"size", size},
                    {"ioc", ioc},
                    {"postOnly", post_only},
                    {"reduceOnly", reduce_only}};
    auto response = http_client.post("orders", payload.dump());
    return json::parse(response.body());
}

json MarketDataEndpoint::place_order(const std::string market,
                             const std::string side,
                             double size,
                             bool ioc,
                             bool post_only,
                             bool reduce_only)
{
    json payload = {{"market", market},
                    {"side", side},
                    {"price", NULL},
                    {"type", "market"},
                    {"size", size},
                    {"ioc", ioc},
                    {"postOnly", post_only},
                    {"reduceOnly", reduce_only}};
    auto response = http_client.post("orders", payload.dump());
    return json::parse(response.body());
}

json MarketDataEndpoint::cancel_order(const std::string order_id)
{
    auto response = http_client.delete_("orders/" + order_id);
    return json::parse(response.body());
}

json MarketDataEndpoint::get_fills()
{
    auto response = http_client.get("fills");
    return json::parse(response.body());
}

json MarketDataEndpoint::get_balances()
{
    auto response = http_client.get("wallet/balances");
    return json::parse(response.body());
}

json MarketDataEndpoint::get_deposit_address(const std::string ticker)
{
    auto response = http_client.get("wallet/deposit_address/" + ticker);
    return json::parse(response.body());
}
*/
}
