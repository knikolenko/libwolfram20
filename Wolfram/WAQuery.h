/*
 *      WAQuery.h
 *
 *      Copyright 2011 Nikolenko Konstantin <knikolenko@yandex.ru>
 *
 */

#ifndef WAQUERY_H
#define WAQUERY_H

#include <string>
#include <sstream>
#include <vector>

using std::string;
using std::vector;

class WAQuery
{
public:
    WAQuery();
    virtual ~WAQuery();

    string  toString();

    string  getInput();
    void    setInput(string input);

    void    addFormat(string format);
    void    clearFormats();

    ////////////  Location-related properties  /////////////

    /*
     * NOT REALESED
     *
    string  getIP();
    void    setIP(string ip);

    double* getLatLong();
    void    setLatLong(string latlong);
    void    setLatitude(double latitude);
    void    setLongitude(double longitude);

    string  getLocation();
    void    setLocation(string loc);

    bool    isMetric();
    void    setMetric(bool metric);

    string  getCurrency();
    void    setCurrency(string currency);

    string  getCountryCode();
    void    setCountryCode(string code);

    bool    isAllowTranslation();
    void    setAllowTranslation(bool allow);
    */

    ////////////////  Pod selection  //////////////////

    void    addPodTitle(string podtitle);
    void    clearPodTitles();

    void    addPodIndex(int podindex);
    void    clearPodIndexes();

    void    addPodScanner(string podscanner);
    void    clearPodScanners();

    void    addIncludePodID(string podid);
    void    clearIncludePodIDs();

    void    addExcludePodID(string podid);
    void    clearExcludePodIDs();

    ///////////  Assumptions and podstates  ////////////

    /*
     * NOT REALESED
     *
    void    addAssumption(string assumption);
    void    clearAssumptions();

    //WAPodState[] getPodStates();
    // This doesn't really work for <statelist>-type states. The query will work, but if you modify an existing
    // query, you won't get the new state replacing the old state. Instead, you get chaining, so the old replacement happens
    // followed by the new replacement. Probably still works, but it's inefficient. (I'm not sure if the order is guaranteed,
    // so the old state might still be in effect.)
    void    addPodState(string podstate);
    // This one is for <statelist> types, but not intended to be called by users, since they don't know what the id is.
    void    addPodState(string podstate, long id);
    //void addPodState(WAPodState podstate);
    void    clearPodStates();

    //////////////////  From URL  ////////////////

    // Take values from an API-style URL.
    //void    fillFromURL(string url);
    */

private:

    // Template for concatenating item vector to string
    template <typename T> string  VectorToStr(const char * prefix, bool individual, vector<T>& t);

    string  input;

    string  ip;
    string  location;
    // Objects, not double, so that they can have null == unassigned
    double  latitude;
    double  longitude;

    bool    metric;
    string  currency;
    string  countryCode;

    vector<string>  formats;
    vector<string>  PodTitle;
    vector<int>     PodIndexes;
    vector<string>  PodScanners;
    vector<string>  IncludePodIDs;
    vector<string>  ExcludePodIDs;
};

/**
 * Template for converting any data to string
 *
 * @return  Converted string
 */
template <class T>
inline std::string to_string (const T& t)
{
    std::stringstream ss;
    ss << t;
    return ss.str();
}

/**
 * Find and replace a 's' to 'd' data in a string
 *
 * @param   text    Source string
 * @param   s       Substring to search
 * @param   d       Substring for replace
 * @return  Replaced string
 */
inline std::string replace(std::string text, std::string s, std::string d)
{
    for(unsigned index = 0; index = text.find(s, index), index != std::string::npos;)
    {
        text.replace(index, s.length(), d);
        index += d.length();
    }
    return text;
}

#endif // WAQUERY_H
