/*
 *      WAPod.h
 *
 *      Copyright 2011 Nikolenko Konstantin <knikolenko@yandex.ru>
 *
 */

#ifndef WAPOD_H
#define WAPOD_H

#include <string>

#include <rapidxml_utils.hpp>

#include "WASubpod.h"
#include "WAPodState.h"

using std::string;
using namespace rapidxml;

class WAPod
{
public:
    WAPod();
    virtual ~WAPod();

    string  getTitle();

    bool    isError();
    string  getScanner();
    int     getPosition();
    string  getID();

    size_t  getCountSubpods();
    WASubpod* getSubpods();

    size_t  getCountStates();
    WAPodState* getStates();

    bool    Parse(xml_node<>* pod);

private:
    bool    error;

    // Attributes of 'pod' node
    char*   title;
    char*   scanner;
    char*   id;
    int     position;

    size_t  countSubPods;   // Count of children node 'subpod'
    WASubpod* SubPods;

    size_t  countStates;    // Count of children node 'states'
    WAPodState* States;

};

#endif // WAPOD_H
