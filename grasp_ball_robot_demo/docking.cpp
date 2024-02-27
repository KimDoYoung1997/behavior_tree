#include <behaviortree_cpp/basic_types.h>
#include <behaviortree_cpp/decorators/subtree_node.h>
#include <iostream>
#include <chrono>
#include <string>
#include <thread>
#include "behaviortree_cpp/bt_factory.h"
#include "behaviortree_cpp/action_node.h"

using namespace std::chrono_literals;

// find Docking point subtree
// Condition node 
BT::NodeStatus docking_point_Found()
{
    std::cout<<"docking point not found"<< std::endl;
    return BT::NodeStatus::FAILURE;
}

// Action node with inheritance of SyncActionNode
class FindDockingPoint : public BT::SyncActionNode
{
public:
    explicit FindDockingPoint(const std::string &name) 
    //Member Initialization list
    : BT::SyncActionNode(name,{})
    {
        std::cout <<"FindDockingPoint class Constructor!" << std::endl;
        //std::this_thread::sleep_for(5s);
        
    }

    BT::NodeStatus tick() override 
    {
        std::this_thread::sleep_for(3s);
        std::cout <<"Docking Point Found! " << this->name() << std::endl;
        return BT::NodeStatus::SUCCESS;
    }

};






// approach Docking Point subtree
// Condition node 
BT::NodeStatus docking_point_Close()
{
    std::cout<<"docking point not close"<<std::endl;
    return BT::NodeStatus::FAILURE;
}

// Action node with inheritance of SyncActionNode
class ApproachDockingPoint : public BT::SyncActionNode
{
public:
    explicit ApproachDockingPoint(const std::string &name)
    :BT::SyncActionNode(name,{})
    {
        std::cout<<"ApproachDockingPoint class Constructor "<<std::endl;
    }
    BT::NodeStatus tick() override
    {
        std::this_thread::sleep_for(3s);
        std::cout <<"Docking Point Approached " << this->name() << std::endl;
        return BT::NodeStatus::SUCCESS;
    }

};


// docking check subtree
// Condition node 
BT::NodeStatus docking_Finished()
{
    std::cout <<"docking finished " << std::endl;
    return BT::NodeStatus::FAILURE;
}

// Action node with inheritance of SyncActionNode
class LiftUp : public BT::SyncActionNode
{
public:
    explicit LiftUp(const std::string &name): BT::SyncActionNode(name,{})
    {
        std::cout <<"LiftUp class Constructor "<<std::endl;
    }
    BT::NodeStatus tick() override
    {
        std::this_thread::sleep_for(3s);
        std::cout <<"Lift Up " << this->name() << std::endl;
        return BT::NodeStatus::SUCCESS;
    }


};

// approach bin subtree
// Condition node 
BT::NodeStatus lift_Finished()
{
    std::cout<<"lift finished"<<std::endl;
    return BT::NodeStatus::FAILURE;
}
// Action node with inheritance of SyncActionNode
class CommandRMF : public BT::SyncActionNode
{
public:
    CommandRMF(const std::string &name):BT::SyncActionNode(name,{})
    {
        std::cout<<"CommandRMF class Constructor"<<std::endl;
    }

    BT::NodeStatus tick() override
    {
        std::this_thread::sleep_for(3s);
        std::cout<<"RMF mode activated "<<this->name() <<std::endl;
        return BT::NodeStatus::SUCCESS;
    }

};


// place ball subtree
// Condition node 
BT::NodeStatus rmf_mode_Finished()
{
    std::cout<<"rmf mode not placed "<<std::endl;
    return BT::NodeStatus::FAILURE;
}
// Action node with inheritance of SyncActionNode
class LiftDown: public BT::SyncActionNode
{
public:
    LiftDown(const std::string &name): BT::SyncActionNode(name,{})
    {
        std::cout<<"LiftDown class Constructor "<< std::endl;
    }

    BT::NodeStatus tick()
    {
        std::this_thread::sleep_for(3s);
        std::cout<<"Lift Down "<< this->name()<<std::endl;
        return BT::NodeStatus::SUCCESS;
    }
};

//  ask for help subtree
// Action node with inheritance of SyncActionNode
class AskForHelp : public BT::SyncActionNode
{
public:
    AskForHelp(const std::string &name): BT::SyncActionNode(name,{})
    {
        std::cout<<"AskForHelp class Constructor"<<std::endl;
    }

    BT::NodeStatus tick()
    {
        std::cout<<"Ask for help. Waiting for 10 seconds here "<< this->name()<<std::endl;

        std::this_thread::sleep_for(10s);
        return BT::NodeStatus::SUCCESS;
    }
};

int main()
{
    BT::BehaviorTreeFactory factory;

    factory.registerSimpleCondition("DockingPointFound", std::bind(docking_point_Found));// Condition node 
    factory.registerNodeType<FindDockingPoint>("FindDockingPoint"); // Action node with inheritance of SyncActionNode

    factory.registerSimpleCondition("DockingPointClose", std::bind(docking_point_Close));// Condition node
    factory.registerNodeType<ApproachDockingPoint>("ApproachDockingPoint"); // Action node with inheritance of SyncActionNode

    factory.registerSimpleCondition("DockingFinished", std::bind(docking_Finished));// Condition node
    factory.registerNodeType<LiftUp>("LiftUp"); // Action node with inheritance of SyncActionNode

    factory.registerSimpleCondition("LiftFinished", std::bind(lift_Finished));// Condition node
    factory.registerNodeType<CommandRMF>("CommandRMF"); // Action node with inheritance of SyncActionNode

    factory.registerSimpleCondition("RmfModeFinished", std::bind(rmf_mode_Finished));// Condition node
    factory.registerNodeType<LiftDown>("LiftDown"); // Action node with inheritance of SyncActionNode

    factory.registerNodeType<AskForHelp>("AskForHelp"); // Action node with inheritance of SyncActionNode

// Create Tree
    auto tree = factory.createTreeFromFile("./../dock_tree.xml");
// execute the tree
    tree.tickWhileRunning(); // tree.tickRoot();



    return 0;
}