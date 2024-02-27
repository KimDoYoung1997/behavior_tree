#include <behaviortree_cpp/basic_types.h>
#include <behaviortree_cpp/decorators/subtree_node.h>
#include <behaviortree_cpp/exceptions.h>
#include <behaviortree_cpp/tree_node.h>
#include <iostream>
#include <chrono>
#include <string>
#include <thread>
#include "behaviortree_cpp/bt_factory.h"
#include "behaviortree_cpp/action_node.h"
#include <vector> // port 타입으로 vector를 사용하기 위해

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
    //The Constructor now needs to have a slightly different signature instead of just one argument
    explicit FindBall(const std::string &name, const BT::NodeConfiguration &config) 
    //Member Initialization list
    : BT::SyncActionNode(name,config)
    {
        //std::cout <<"FindBall class Constructor!" << std::endl;
        //std::this_thread::sleep_for(5s);
        
    }
//  ===================== add output ports =====================
    // It is mandatory to define this STATIC method.
    //  BT 의 PortsList providedPorts() 함수를 전역에서 사용하기위해 static이 필요했음  
    static BT::PortsList providedPorts()
    {
    // This action has a single output port called "ball_location"
        return {BT::OutputPort<std::vector<int>>("ball_location")}; // 여기선 int를 담은 vector를 output port로 사용하지만, 필요에 따라 데이터 타입을 바꿀 수 있다.
    }

//  ===================== add output ports =====================

    BT::NodeStatus tick() override 
    {
        std::this_thread::sleep_for(3s);
        std::vector<int> ballLocation{1,2,3}; // vector 하나 생성하고 이를 node간에 send할 것임 (value로 사용되는듯?)
        BT::TreeNode::setOutput("ball_location", ballLocation); // output port : ball_location , key : location , value : ballLocation{1,2,3}
        std::cout <<"Ball Found! " << this->name() << std::endl;

        return BT::NodeStatus::SUCCESS;
    }

};






// approach ball subtree
// Condition node 
BT::NodeStatus ballClose(BT::TreeNode &self) // 새로운 argument 추가
{
// you need to create msg
//Input port : ball_location , key : location
// xml파일에서 읽어온 input port와 key를 가져온다.
    //BT::Optional<std::vector<int>> msg= self.getInput<std::vector<int>>("ball_location");
    auto msg = self.getInput<std::vector<int>>("ball_location");
//  we also need to check if this message exists 
//  this is how we do it if message is done we will throw a runtime error saying missing required input message 
    if(!msg)
    {
        throw BT::RuntimeError("missing required input[message]: ",msg.error());
    }
    
    for (const auto position_coordinate : msg.value())
    {
        std::cout << position_coordinate <<" ";
    }

    std::cout<<"The location is far away"<<std::endl;
    return BT::NodeStatus::FAILURE;
}

// Action node with inheritance of SyncActionNode
class ApproachBall : public BT::SyncActionNode
{
public:
//The Constructor now needs to have a slightly different signature instead of just one argument
    explicit ApproachBall(const std::string &name,const BT::NodeConfiguration &config)
    :BT::SyncActionNode(name,config)
    {
        //std::cout<<"ApproachBall class Constructor "<<std::endl;
    }

//  ===================== add output ports =====================

    static BT::PortsList providedPorts()
    {
        return {BT::InputPort<std::vector<int>>("ball_location")};
    }
//  ===================== add output ports =====================


// tick 함수 
// In our tick method, we will use our input Port like we did for FindBall
    BT::NodeStatus tick() override
    {
        
// you need to create msg
//Input port : ball_location , key : location
// xml파일에서 읽어온 input port와 key를 가져온다.
        // BT::Optional<std::vector<int>> msg= self.getInput<std::vector<int>>("ball_location");
        auto msg = getInput<std::vector<int>>("ball_location");
    
//  we also need to check if this message exists 
//  this is how we do it if message is done we will throw a runtime error saying missing required input message 
        if(!msg)
        {
            throw BT::RuntimeError("missing required input[message]: ",msg.error());
        }
        for (const auto position_coordinate : msg.value())
        {
            std::cout << position_coordinate <<" ";
        }
        
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
        //std::cout <<"GraspBall class Constructor "<<std::endl;
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
        //std::cout<<"ApproachBin class Constructor"<<std::endl;
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
        //std::cout<<"PlaceBall class Constructor "<< std::endl;
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
        //std::cout<<"AskForHelp class Constructor"<<std::endl;
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

    BT::PortsList say_something_ports = {BT::InputPort<std::vector<int>>("ball_location")};
    // factory.registerSimpleCondition("BallClose", std::bind(ballClose));// Condition node
    factory.registerSimpleCondition("BallClose", ballClose,say_something_ports);
    factory.registerNodeType<ApproachBall>("ApproachBall"); // Action node with inheritance of SyncActionNode

    factory.registerSimpleCondition("BallGrasped", std::bind(ballGrasped));// Condition node
    factory.registerNodeType<GraspBall>("GraspBall"); // Action node with inheritance of SyncActionNode

    factory.registerSimpleCondition("BinClose", std::bind(binClose));// Condition node
    factory.registerNodeType<ApproachBin>("ApproachBin"); // Action node with inheritance of SyncActionNode

    factory.registerSimpleCondition("BallPlaced", std::bind(ballPlaced));// Condition node
    factory.registerNodeType<PlaceBall>("PlaceBall"); // Action node with inheritance of SyncActionNode

    factory.registerNodeType<AskForHelp>("AskForHelp"); // Action node with inheritance of SyncActionNode

// Create Tree
    auto tree = factory.createTreeFromFile("./../bt_tree_ports.xml");
// execute the tree
    tree.tickWhileRunning(); // tree.tickRoot();



    return 0;
}