/**
 * @file Basket.h
 * @author djmik
 *
 * header file for basket component
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_BASKET_H
#define CANADIANEXPERIENCE_MACHINELIB_BASKET_H

#include <b2_world_callbacks.h>
#include "Component.h"
#include "Polygon.h"
#include "PhysicsPolygon.h"

/**
 * Basket component class
 *
 * When an object is placed inside of the basket, a timer will start
 * after the timer finishes, the object will be launched in a predetermined direction
 */
class Basket : public Component, public  b2ContactListener
{
private:
    /// Time remaining before item is launched
    double mTimer = 0;

    /// Is Basket in countdown mode
    bool mIsCounting = false;

    /// Basket Launch Direction
    b2Vec2 mDirection = b2Vec2(0, 5);

    /// polygon displaying basket image
    cse335::Polygon mBasketImage;

    /// left wall of basket
    cse335::PhysicsPolygon mLeftWall;

    /// right wall of basket
    cse335::PhysicsPolygon mRightWall;

    /// bottom launching platform of basket
    cse335::PhysicsPolygon mLauncher;


public:
    Basket(const std::wstring& imagesDir);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    void Update(double elapsed) override;

    void SetMachine(Machine * machine) override;

    void SetPosition(int x, int y) override;

    void Reset() override;

    void BeginContact(b2Contact* contact) override;


    /**
     * Change basked launch vector
     * @param vec new launch vector
     */
    void SetDirection(b2Vec2 vec) {mDirection = vec; }

};

#endif //CANADIANEXPERIENCE_MACHINELIB_BASKET_H
