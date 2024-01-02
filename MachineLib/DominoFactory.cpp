/**
 * @file DominoFactory.cpp
 * @author djmik
 */

#include "pch.h"
#include "DominoFactory.h"
#include "Body.h"

/// Directory within resources that contains the images.
const std::wstring ImagesDirectory = L"/images";

/// Directory within resources that contains the images.
const std::wstring red = L"/domino-red.png";

/// Directory within resources that contains the images.
const std::wstring green = L"/domino-green.png";

/// Directory within resources that contains the images.
const std::wstring blue = L"/domino-blue.png";

/// Directory within resources that contains the images.
const std::wstring black = L"/domino-black.png";

/**
 * Create a domino with a specified color
 * 0/default = green
 * 1 = red
 * 2 = blue
 * 3 = black
 * @param resourcesDir image resource directory
 * @param color color of domino
 * @return domino body component
 */
std::shared_ptr<Body> DominoFactory::Create(const std::wstring &resourcesDir, int color)
{

    auto domino = std::make_shared<Body>();
    domino->Rectangle(0,0,5,20);
    switch(color) {
        case (0):
            domino->SetImage(resourcesDir+ImagesDirectory+green);
            break;
        case (1):
            domino->SetImage(resourcesDir+ImagesDirectory+red);
            break;
        case (2):
            domino->SetImage(resourcesDir+ImagesDirectory+blue);
            break;
        case (3):
            domino->SetImage(resourcesDir+ImagesDirectory+black);
            break;
        default:
            domino->SetImage(resourcesDir+ImagesDirectory+green);
            break;

    }

    domino->SetDynamic();
    return domino;
}
