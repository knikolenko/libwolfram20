/*
 *      WAImage.cpp
 *
 *      Copyright 2011 Nikolenko Konstantin <knikolenko@yandex.ru>
 *
 */

#include "WAImage.h"

WAImage::WAImage()
{
    //ctor
}

WAImage::~WAImage()
{
    //dtor
}

/**
 * Returning a 'src' attribute of image
 *
 * @return Address of image
 */
string
WAImage::getSrc()
{
    return string(src);
}

/**
 * Returning a 'alt' attribute of image
 *
 * @return Alternate text of image
 */
string
WAImage::getAlt()
{
    return string(alt);
}

/**
 * Returning a 'title' attribute of image
 *
 * @return Title of image
 */
string
WAImage::getTitle()
{
    return string(title);
}

/**
 * Returning a 'width' attribute of image
 *
 * @return Width of image
 */
size_t
WAImage::getWidth()
{
    return width;
}

/**
 * Returning a 'height' attribute of image
 *
 * @return Height of image
 */
size_t
WAImage::getHeight()
{
    return height;
}

/**
 * Parsing a input 'img' xml node
 *
 * @param   imgNode XML Node of image
 * @return  false, if error
 */
bool
WAImage::Parse(xml_node<>* imgNode)
{
    // Get attributes
    src     = imgNode->first_attribute("src")->value();
    alt     = imgNode->first_attribute("alt")->value();
    title   = imgNode->first_attribute("title")->value();
    width   = atoi(imgNode->first_attribute("width")->value());
    height  = atoi(imgNode->first_attribute("height")->value());
    return true;
}
