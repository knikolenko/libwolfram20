/*
 *      WAEngine.cpp
 *
 *      Copyright 2011 Nikolenko Konstantin <knikolenko@yandex.ru>
 *
 */

#include "WAEngine.h"

/**
 * Constructor with default config
 */
WAEngine::WAEngine()
{
    error = false;
    this->server = "api.wolframalpha.com";
    this->path   = "/v2/query";
}

/**
 * Constructor with another config
 *
 * @param appid     AppID, for using WolframAlpha
 * @param server    Address of WolframAlpha server
 * @param path      Path to script on server
 */
WAEngine::WAEngine(string appid, string server, string path)
{
    error = false;
    this->appID  = appid;
    this->server = server;
    this->path   = path;
}

WAEngine::~WAEngine()
{
    if (Pods != NULL)
    {
        for (size_t i = 0; i < countPods; i++)
            Pods[i].~WAPod();
    }
    free(data);
}

/**
 * Returns a setted AppID
 *
 * @return AppID
 */
string
WAEngine::getAppID()
{
    return this->appID;
}

/**
 * Set another AppID
 *
 * @param appid Another AppID
 */
void
WAEngine::setAppID(string appid)
{
    this->appID = appid;
}

/**
 * Returns a URL for HTTP request, using a internal WAQuery object
 *
 * @return URL
 */
string
WAEngine::getURL()
{
    return "http://" + server + path + "?" + "appid=" + appID + this->query.toString();
}

/**
 * Returns a URL for HTTP request, using a external WAQuery object
 *
 * @return URL
 */
string
WAEngine::getURL(WAQuery query)
{
    return "http://" + server + path + "?" + "appid=" + appID + query.toString();
}

/**
 * Parsing a array of char 'data'
 *
 * @return false, if a error
 */
bool
WAEngine::Parse()
{
    if ((data == NULL) || (length == 0))
    {
        return false;
    }
    xml_document<> root;
    root.parse<0>(data);
    xml_node<>* query = root.first_node("queryresult");

    //Get attributes queryresult
    dataTypes = string(query->first_attribute("datatypes")->value());
    version   = string(query->first_attribute("version")->value());

    if (string(query->first_attribute("error")->value()) == "true")
    {
        this->error = true;
    }

    // Read Pods
    countPods = atoi(query->first_attribute("numpods")->value());
    Pods = new WAPod[countPods];

    xml_node<>* node = query->first_node("pod");
    for(size_t i = 0; i < countPods; i++)
    {
        Pods[i].Parse(node);
        node = node->next_sibling("pod");
    }

    return true;
}

/**
 * Parsing data from a text-file
 *
 * @param filename  Name of file for parsing
 * @return false, if a error
 */
bool
WAEngine::Parse(string filename)
{
    ifstream file;
    file.open(filename.c_str(), ios::in);
    if (file.fail())
    {
        return false;
    }
    // Get length of file
    file.seekg(0, ios_base::end);
    length = file.tellg();
    file.seekg(0, ios_base::beg);

    // Read file
    data = (char*)malloc(length);
    file.read(data, length);

    file.close();

    // Parse data from file
    Parse();

    return true;
}

/**
 * Parsing data from a external array of char
 *
 * @param   inputData  Pointer to array of data
 * @return  false, if a error
 */
bool
WAEngine::Parse(char * inputData)
{
    data = inputData;
    return Parse();
}

/**
 * Returns a count of blocks "pod"
 *
 * @return  count of block
 */
int
WAEngine::getCountPods()
{
    return countPods;
}

/**
 * Returns a array of Pod
 *
 * @return  pointer to array of Pod
 */
WAPod*
WAEngine::getPods()
{
    return this->Pods;
}
