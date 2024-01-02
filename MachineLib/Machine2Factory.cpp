/**
 * @file Machine2Factory.cpp
 * @author djmik
 */

#include "pch.h"
#include "Machine.h"
#include "Machine2Factory.h"
#include "Body.h"
#include "Goal.h"
#include "Pulley.h"
#include "Hamster.h"
#include "Conveyor.h"
#include "Basket.h"
#include "Curtain.h"
#include "Banner.h"

/// Directory within resources that contains the images.
const std::wstring ImagesDirectory = L"/images";

/**
 * Creates a unique machine numbered: machine #1
 * @param resourcesDir Directory holding images for components created
 * @return machine pointer
 */
std::shared_ptr<Machine> Machine2Factory::Create(const std::wstring &resourcesDir)
{
    std::shared_ptr<Machine> machine = std::make_shared<Machine>();

    auto ceiling = std::make_shared<Body>();
    ceiling->SetInitialPosition(0,0);
    ceiling->Rectangle(40,300,180,20);
    ceiling->SetImage(resourcesDir+ImagesDirectory+L"/beam2.png");
    machine->AddComponent(ceiling);


    auto banner = std::make_shared<Banner>(resourcesDir + ImagesDirectory);
    banner->SetPosition(220, 275);
    banner->SetCountdown(1);
    machine->AddComponent(banner);

    //600x15
    auto floor = std::make_shared<Body>();
    floor->SetInitialPosition(0,0);
    floor->Rectangle(-300,0,600,15);
    floor->SetImage(resourcesDir+ImagesDirectory+L"/floor.png");
    machine->AddComponent(floor);
    //75x75
    auto ball = std::make_shared<Body>();
    ball->SetInitialPosition(-200, 200);
    ball->Circle(15);
    ball->SetImage(resourcesDir+ImagesDirectory+L"/basketball1.png");
    ball->SetDynamic();
    machine->AddComponent(ball);

    auto basket = std::make_shared<Basket>(resourcesDir + ImagesDirectory);
    basket->SetPosition(-200, 15);
    basket->SetDirection(b2Vec2(6,9));
    machine->AddComponent(basket);


    auto basket2 = std::make_shared<Basket>(resourcesDir + ImagesDirectory);
    basket2->SetPosition(-100, 15);
    basket2->SetDirection(b2Vec2(7,10));
    machine->AddComponent(basket2);

    auto basket3 = std::make_shared<Basket>(resourcesDir + ImagesDirectory);
    basket3->SetPosition(-15, 15);
    basket3->SetDirection(b2Vec2(6,9));
    machine->AddComponent(basket3);

    auto basket4 = std::make_shared<Basket>(resourcesDir + ImagesDirectory);
    basket4->SetPosition(85, 15);
    basket4->SetDirection(b2Vec2(7,10));
    machine->AddComponent(basket4);

    auto basket5 = std::make_shared<Basket>(resourcesDir + ImagesDirectory);
    basket5->SetPosition(210, 15);
    basket5->SetDirection(b2Vec2(4, 15.5));
    machine->AddComponent(basket5);

    auto hamster = std::make_shared<Hamster>(resourcesDir + ImagesDirectory);
    hamster->SetInitiallyRunning(false);
    hamster->SetPosition(-50, 130);
    hamster->SetSpeed(-0.5);
    machine->AddComponent(hamster);

    auto conveyor = std::make_shared<Conveyor>(resourcesDir + ImagesDirectory);
    conveyor->SetPosition(100, 225);
    machine->AddComponent(conveyor);

    auto pulley1 = std::make_shared<Pulley>(25);
    pulley1->SetImage(resourcesDir+ImagesDirectory+L"/pulley3.png");
    pulley1->SetPosition(hamster->GetShaftPosition().m_x, hamster->GetShaftPosition().m_y);
    machine->AddComponent(pulley1);

    hamster->GetSource()->Connect(hamster->GetSource(), pulley1->GetSink(), 1);

    // make pully 2 with R2

    auto pulley2 = std::make_shared<Pulley>(12);
    pulley2->SetImage(resourcesDir+ImagesDirectory+L"/pulley3.png");
    pulley2->SetPosition(conveyor->GetShaftPosition().m_x, conveyor->GetShaftPosition().m_y);
    machine->AddComponent(pulley2);

    pulley1->GetSource()->Connect(pulley1->GetSource(), pulley2->GetSink(), pulley1->GetRadius()/pulley2->GetRadius());
    pulley2->GetSource()->Connect(pulley2->GetSource(),conveyor->GetSink(), 1);
    pulley1->SetOtherPulley(pulley2);
    pulley2->SetOtherPulley(pulley1);

    auto hamster2 = std::make_shared<Hamster>(resourcesDir + ImagesDirectory);
    hamster2->SetInitiallyRunning(true);
    hamster2->SetPosition(40, 130);
    hamster2->SetSpeed(-1.15);
    machine->AddComponent(hamster2);

    auto conveyor2 = std::make_shared<Conveyor>(resourcesDir + ImagesDirectory);
    conveyor2->SetPosition(0, 210);
    machine->AddComponent(conveyor2);

    auto pulley3 = std::make_shared<Pulley>(25);
    pulley3->SetImage(resourcesDir+ImagesDirectory+L"/pulley3.png");
    pulley3->SetPosition(hamster2->GetShaftPosition().m_x, hamster2->GetShaftPosition().m_y);
    machine->AddComponent(pulley3);

    hamster2->GetSource()->Connect(hamster2->GetSource(), pulley3->GetSink(), 1);

    auto pulley4 = std::make_shared<Pulley>(8);
    pulley4->SetImage(resourcesDir+ImagesDirectory+L"/pulley3.png");
    pulley4->SetPosition(conveyor2->GetShaftPosition().m_x, conveyor2->GetShaftPosition().m_y);
    machine->AddComponent(pulley4);

    pulley3->GetSource()->Connect(pulley3->GetSource(), pulley4->GetSink(), pulley3->GetRadius()/pulley4->GetRadius());
    pulley4->GetSource()->Connect(pulley4->GetSource(),conveyor2->GetSink(), 1);
    pulley3->SetOtherPulley(pulley4);
    pulley4->SetOtherPulley(pulley3);

    auto leftWall = std::make_shared<Body>();
    leftWall->SetInitialPosition(0,0);
    leftWall->Rectangle(-300, 15, 40, 200);
    leftWall->SetImage(resourcesDir+ImagesDirectory+L"/domino-black.png");
    machine->AddComponent(leftWall);

    auto curtain = std::make_shared<Curtain>(resourcesDir + ImagesDirectory);
    curtain->SetPosition(0,0);
    machine->AddComponent(curtain);

    return machine;
}
