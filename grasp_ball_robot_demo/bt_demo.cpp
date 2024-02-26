#include <behaviortree_cpp/basic_types.h>
#include <behaviortree_cpp/decorators/subtree_node.h>
#include <iostream>
#include <chrono>
#include <string>
#include <thread>
#include "behaviortree_cpp/bt_factory.h"
#include "behaviortree_cpp/action_node.h"

using namespace std::chrono_literals;

// find ball subtree
// Condition node 
BT::NodeStatus ballFound()
{
    std::cout<<"Ball not found"<< std::endl;
    return BT::NodeStatus::FAILURE;
}

// Action node with inheritance of SyncActionNode
class FindBall : public BT::SyncActionNode
{
public:
    explicit FindBall(const std::string &name) 
    //Member Initialization list
    : BT::SyncActionNode(name,{})
    {
        std::cout <<"FindBall class Constructor!" << std::endl;
        //std::this_thread::sleep_for(5s);
        
    }

    BT::NodeStatus tick() override 
    {
        std::this_thread::sleep_for(3s);
        std::cout <<"Ball Found! " << this->name() << std::endl;
        return BT::NodeStatus::SUCCESS;
    }

};






// approach ball subtree
// Condition node 
BT::NodeStatus ballClose()
{
    std::cout<<"Ball not close"<<std::endl;
    return BT::NodeStatus::FAILURE;
}

// Action node with inheritance of SyncActionNode
class ApproachBall : public BT::SyncActionNode
{
public:
    explicit ApproachBall(const std::string &name)
    :BT::SyncActionNode(name,{})
    {
        std::cout<<"ApproachBall class Constructor "<<std::endl;
    }
    BT::NodeStatus tick() override
    {
        std::this_thread::sleep_for(3s);
        std::cout <<"Ball Approached " << this->name() << std::endl;
        return BT::NodeStatus::SUCCESS;
    }

};


// grasp ball subtree
// Condition node 
BT::NodeStatus ballGrasped()
{
    std::cout <<"Ball not grasped " << std::endl;
    return BT::NodeStatus::FAILURE;
}

// Action node with inheritance of SyncActionNode
class GraspBall : public BT::SyncActionNode
{
public:
    explicit GraspBall(const std::string &name): BT::SyncActionNode(name,{})
    {
        std::cout <<"GraspBall class Constructor "<<std::endl;
    }
    BT::NodeStatus tick() override
    {
        std::this_thread::sleep_for(3s);
        std::cout <<"Ball grasped " << this->name() << std::endl;
        return BT::NodeStatus::SUCCESS;
    }


};

// approach bin subtree
// Condition node 
BT::NodeStatus binClose()
{
    std::cout<<"Bin not close"<<std::endl;
    return BT::NodeStatus::FAILURE;
}
// Action node with inheritance of SyncActionNode
class ApproachBin : public BT::SyncActionNode
{
public:
    ApproachBin(const std::string &name):BT::SyncActionNode(name,{})
    {
        std::cout<<"ApproachBin class Constructor"<<std::endl;
    }

    BT::NodeStatus tick() override
    {
        std::this_thread::sleep_for(3s);
        std::cout<<"Bin approached "<<this->name() <<std::endl;
        return BT::NodeStatus::SUCCESS;
    }

};


// place ball subtree
// Condition node 
BT::NodeStatus ballPlaced()
{
    std::cout<<"Ball not placed "<<std::endl;
    return BT::NodeStatus::FAILURE;
}
// Action node with inheritance of SyncActionNode
class PlaceBall: public BT::SyncActionNode
{
public:
    PlaceBall(const std::string &name): BT::SyncActionNode(name,{})
    {
        std::cout<<"PlaceBall class Constructor "<< std::endl;
    }

    BT::NodeStatus tick()
    {
        std::this_thread::sleep_for(3s);
        std::cout<<"Ball placed "<< this->name()<<std::endl;
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

    factory.registerSimpleCondition("BallFound", std::bind(ballFound));// Condition node 
    factory.registerNodeType<FindBall>("FindBall"); // Action node with inheritance of SyncActionNode

    factory.registerSimpleCondition("BallClose", std::bind(ballClose));// Condition node
    factory.registerNodeType<ApproachBall>("ApproachBall"); // Action node with inheritance of SyncActionNode

    factory.registerSimpleCondition("BallGrasped", std::bind(ballGrasped));// Condition node
    factory.registerNodeType<GraspBall>("GraspBall"); // Action node with inheritance of SyncActionNode

    factory.registerSimpleCondition("BinClose", std::bind(binClose));// Condition node
    factory.registerNodeType<ApproachBin>("ApproachBin"); // Action node with inheritance of SyncActionNode

    factory.registerSimpleCondition("BallPlaced", std::bind(ballPlaced));// Condition node
    factory.registerNodeType<PlaceBall>("PlaceBall"); // Action node with inheritance of SyncActionNode

    factory.registerNodeType<AskForHelp>("AskForHelp"); // Action node with inheritance of SyncActionNode

// Create Tree
    auto tree = factory.createTreeFromFile("./../bt_tree.xml");
// execute the tree
    tree.tickWhileRunning(); // tree.tickRoot();



    return 0;
}