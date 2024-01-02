/**
 * @file Machine1Factory.cpp
 * @author djmik
 */

#include "pch.h"
#include "Machine.h"
#include "Machine1Factory.h"
#include "Body.h"
#include "Goal.h"
#include "Pulley.h"
#include "Hamster.h"
#include "Conveyor.h"
#include "Basket.h"
#include "DominoFactory.h"

/// Directory within resources that contains the images.
const std::wstring ImagesDirectory = L"/images";

/**
 * Creates a unique machine numbered: machine #1
 * @param resourcesDir Directory holding images for components created
 * @return machine pointer
 */
std::shared_ptr<Machine> Machine1Factory::Create(const std::wstring &resourcesDir)
{
    std::shared_ptr<Machine> machine = std::make_shared<Machine>();

    //600x15
    auto floor = std::make_shared<Body>();
    floor->SetInitialPosition(0,0);
    floor->Rectangle(-300,0,600,15);
    floor->SetImage(resourcesDir+ImagesDirectory+L"/floor.png");
    machine->AddComponent(floor);

    //75x75
    auto ball = std::make_shared<Body>();
    ball->SetInitialPosition(-200, 350);
    ball->Circle(12);
    ball->SetImage(resourcesDir+ImagesDirectory+L"/basketball1.png");
    ball->SetDynamic();
    machine->AddComponent(ball);

    auto ramp = std::make_shared<Body>();
    ramp->AddPoint(-210, 340);
    ramp->AddPoint(-210, 310);
    ramp->AddPoint(-140, 310);
    ramp->SetImage(resourcesDir+ImagesDirectory+L"/wedge.png");
    machine->AddComponent(ramp);

    auto beam = std::make_shared<Body>();
    beam->Rectangle(-210,290,375,20);
    beam->SetImage(resourcesDir+ImagesDirectory+L"/beam.png");
    machine->AddComponent(beam);

    auto goal = std::make_shared<Goal>(resourcesDir+ImagesDirectory);
    goal->SetPosition(270,15);
    machine->AddComponent(goal);

    auto beam2 = std::make_shared<Body>();
    beam2->Rectangle(-210,245,375,20);
    beam2->SetImage(resourcesDir+ImagesDirectory+L"/beam.png");
    machine->AddComponent(beam2);

    auto ball2 = std::make_shared<Body>();
    ball2->SetInitialPosition(-190, 280);
    ball2->Circle(12);
    ball2->SetImage(resourcesDir+ImagesDirectory+L"/basketball2.png");
    ball2->SetDynamic();
    machine->AddComponent(ball2);

    auto armHamster = std::make_shared<Hamster>(resourcesDir + ImagesDirectory);
    armHamster->SetPosition(-210, 180);
    armHamster->SetInitiallyRunning(true);
    armHamster->SetSpeed(1.0);
    machine->AddComponent(armHamster);

    auto arm = std::make_shared<Body>();
    arm->AddPoint(-7, 10);
    arm->AddPoint(7, 10);
    arm->AddPoint(7, -60);
    arm->AddPoint(-7, -60);
    arm->SetImage(resourcesDir + ImagesDirectory + L"/arm.png");
    arm->SetKinematic();
    arm->SetInitialPosition(armHamster->GetShaftPosition().m_x, armHamster->GetShaftPosition().m_y);
    machine->AddComponent(arm);
    armHamster->GetSource()->Connect(armHamster->GetSource(), arm->GetSink(), 1);

    auto leftConveyor = std::make_shared<Conveyor>(resourcesDir + ImagesDirectory);
    leftConveyor->SetPosition(-230,110);
    machine->AddComponent(leftConveyor);

    //75x75
    auto ball3 = std::make_shared<Body>();
    ball3->SetInitialPosition(-250, 140);
    ball3->Circle(12);
    ball3->SetImage(resourcesDir+ImagesDirectory+L"/ball1.png");
    ball3->SetDynamic();
    machine->AddComponent(ball3);

    auto smallBeam = std::make_shared<Body>();
    smallBeam->Rectangle(-165,110,140,14);
    smallBeam->SetImage(resourcesDir+ImagesDirectory+L"/beam.png");
    machine->AddComponent(smallBeam);

    auto hamster = std::make_shared<Hamster>(resourcesDir + ImagesDirectory);
    hamster->SetPosition(10,130);
    hamster->SetInitiallyRunning(false);
    hamster->SetSpeed(2.0);
    machine->AddComponent(hamster);

    auto topConveyor = std::make_shared<Conveyor>(resourcesDir + ImagesDirectory);
    topConveyor->SetPosition(120,200);
    machine->AddComponent(topConveyor);

    //75x75
    auto ball4 = std::make_shared<Body>();
    ball4->SetInitialPosition(90, 230);
    ball4->Circle(12);
    ball4->SetImage(resourcesDir+ImagesDirectory+L"/ball1.png");
    ball4->SetDynamic();
    machine->AddComponent(ball4);

    auto hamster2 = std::make_shared<Hamster>(resourcesDir + ImagesDirectory);
    hamster2->SetPosition(-40,15);
    hamster2->SetInitiallyRunning(false);
    hamster2->SetSpeed(0.8);
    machine->AddComponent(hamster2);

    auto hamster3 = std::make_shared<Hamster>(resourcesDir + ImagesDirectory);
    hamster3->SetPosition(240,15);
    hamster3->SetInitiallyRunning(false);
    hamster3->SetSpeed(-1.3);
    machine->AddComponent(hamster3);

    auto bottomConveyor = std::make_shared<Conveyor>(resourcesDir + ImagesDirectory);
    bottomConveyor->SetPosition(60,55);
    machine->AddComponent(bottomConveyor);

    //75x75
    auto ball5 = std::make_shared<Body>();
    ball5->SetInitialPosition(100, 80);
    ball5->Circle(12);
    ball5->SetImage(resourcesDir+ImagesDirectory+L"/ball1.png");
    ball5->SetDynamic();
    machine->AddComponent(ball5);

    auto pulley1 = std::make_shared<Pulley>(12);
    pulley1->SetImage(resourcesDir+ImagesDirectory+L"/pulley3.png");
    pulley1->SetPosition(hamster3->GetShaftPosition().m_x, hamster3->GetShaftPosition().m_y);
    hamster3->GetSource()->Connect(hamster3->GetSource(), pulley1->GetSink());
    machine->AddComponent(pulley1);

    auto pulley2 = std::make_shared<Pulley>(12);
    pulley2->SetImage(resourcesDir+ImagesDirectory+L"/pulley3.png");
    pulley2->SetPosition(bottomConveyor->GetShaftPosition().m_x, bottomConveyor->GetShaftPosition().m_y);
    machine->AddComponent(pulley2);
    pulley1->GetSource()->Connect(pulley1->GetSource(), pulley2->GetSink(), pulley1->GetRadius()/pulley2->GetRadius());
    pulley2->GetSource()->Connect(pulley2->GetSource(), bottomConveyor->GetSink(), 1);
    pulley1->SetOtherPulley(pulley2);
    pulley2->SetOtherPulley(pulley1);

    auto pulley3 = std::make_shared<Pulley>(12);
    pulley3->SetImage(resourcesDir+ImagesDirectory+L"/pulley3.png");
    pulley3->SetPosition(hamster2->GetShaftPosition().m_x, hamster2->GetShaftPosition().m_y);
    hamster2->GetSource()->Connect(hamster2->GetSource(), pulley3->GetSink());
    machine->AddComponent(pulley3);

    auto pulley4 = std::make_shared<Pulley>(12);
    pulley4->SetImage(resourcesDir+ImagesDirectory+L"/pulley3.png");
    pulley4->SetPosition(leftConveyor->GetShaftPosition().m_x, leftConveyor->GetShaftPosition().m_y);
    machine->AddComponent(pulley4);
    pulley3->GetSource()->Connect(pulley3->GetSource(), pulley4->GetSink(), pulley3->GetRadius()/pulley4->GetRadius());
    pulley4->GetSource()->Connect(pulley4->GetSource(), leftConveyor->GetSink(), 1);
    pulley3->SetOtherPulley(pulley4);
    pulley4->SetOtherPulley(pulley3);

    auto pulley5 = std::make_shared<Pulley>(12);
    pulley5->SetImage(resourcesDir+ImagesDirectory+L"/pulley3.png");
    pulley5->SetPosition(hamster->GetShaftPosition().m_x, hamster->GetShaftPosition().m_y);
    hamster->GetSource()->Connect(hamster->GetSource(), pulley5->GetSink());
    machine->AddComponent(pulley5);

    auto pulley6 = std::make_shared<Pulley>(8);
    pulley6->SetImage(resourcesDir+ImagesDirectory+L"/pulley3.png");
    pulley6->SetPosition(topConveyor->GetShaftPosition().m_x, topConveyor->GetShaftPosition().m_y);
    machine->AddComponent(pulley6);
    pulley5->GetSource()->Connect(pulley5->GetSource(), pulley6->GetSink(), pulley5->GetRadius()/pulley6->GetRadius());
    pulley6->GetSource()->Connect(pulley6->GetSource(), topConveyor->GetSink(), 1);
    pulley5->SetOtherPulley(pulley6);
    pulley6->SetOtherPulley(pulley5);


    // DOMINO'S ON THE BOTTOM FLOOR

    DominoFactory dominoFactory;

    auto domino = dominoFactory.Create(resourcesDir,0);
    domino->SetPosition(-100,15);
    machine->AddComponent(domino);

    auto domino2 = dominoFactory.Create(resourcesDir,1);
    domino2->SetPosition(-110,15);
    machine->AddComponent(domino2);

    auto domino3 = dominoFactory.Create(resourcesDir,2);
    domino3->SetPosition(-120,15);
    machine->AddComponent(domino3);

    auto domino4 = dominoFactory.Create(resourcesDir,3);
    domino4->SetPosition(-130,15);
    machine->AddComponent(domino4);

    // DOMINO'S ON UPPER PLATFORM

    auto domino5 = dominoFactory.Create(resourcesDir,0);
    domino5->SetPosition(-100,125);
    machine->AddComponent(domino5);

    auto domino6 = dominoFactory.Create(resourcesDir,1);
    domino6->SetPosition(-110,125);
    machine->AddComponent(domino6);

    auto domino7 = dominoFactory.Create(resourcesDir,2);
    domino7->SetPosition(-120,125);
    machine->AddComponent(domino7);

    auto domino8 = dominoFactory.Create(resourcesDir,0);
    domino8->SetPosition(-130,125);
    machine->AddComponent(domino8);

    auto domino9 = dominoFactory.Create(resourcesDir,1);
    domino9->SetPosition(-90,125);
    machine->AddComponent(domino9);

    auto domino10 = dominoFactory.Create(resourcesDir,2);
    domino10->SetPosition(-80,125);
    machine->AddComponent(domino10);

    auto domino11 = dominoFactory.Create(resourcesDir,3);
    domino11->SetPosition(-70,125);
    machine->AddComponent(domino11);

    auto domino12 = dominoFactory.Create(resourcesDir,0);
    domino12->SetPosition(-60,125);
    machine->AddComponent(domino12);

    auto domino13 = dominoFactory.Create(resourcesDir,1);
    domino13->SetPosition(-50,125);
    machine->AddComponent(domino13);

    return machine;
}
