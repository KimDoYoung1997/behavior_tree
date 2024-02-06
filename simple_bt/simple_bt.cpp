
#include "behaviortree_cpp/bt_factory.h"
#include "behaviortree_cpp/action_node.h"

#include <iostream>
#include <chrono>

using namespace std::chrono_literals;

//Node class
class ApproachObject : public BT::SyncActionNode
{
public:
    explicit ApproachObject(const std::string &name) 
    //Member Initialization list
    : BT::SyncActionNode(name,{})
    {

    }

    BT::NodeStatus tick() override 
    {
        std::cout <<"Approach Object: " << this->name() << std::endl;
        std::this_thread::sleep_for(5s);
        return BT::NodeStatus::SUCCESS;
    }

};



//function
BT::NodeStatus CheckBattery() // condition node. it just checks for something and then return immediately
{

    std::cout << "Battery OK" << std::endl;
    return BT::NodeStatus::SUCCESS;
}


//custom class method
class GripperInterface // what we need to to is make two methods. one for opening and the other one for closing
{
public:
    GripperInterface() // Constructor
    : _open(true)
    {

    }

    BT::NodeStatus open() //method
    {
        _open = true;
        std::cout << "Gripper open" << std::endl;
        return BT::NodeStatus::SUCCESS;
    }
    
    BT::NodeStatus close() //method
    {
        _open = false;
        std::cout << "Gripper close" << std::endl;
        return BT::NodeStatus::SUCCESS;
    }

private:
    bool _open;

};




int main()
{
    BT::BehaviorTreeFactory factory;
    factory.registerNodeType<ApproachObject>("ApproachObject");
    factory.registerSimpleCondition("CheckBattery", std::bind(CheckBattery));
    
    GripperInterface gripper;

    factory.registerSimpleAction(
        "OpenGripper",
        std::bind(&GripperInterface::open,&gripper));

    factory.registerSimpleAction(
        "CloseGripper",
        std::bind(&GripperInterface::close,&gripper)
    );

    // Create Tree
    auto tree = factory.createTreeFromFile("./../bt_tree.xml");


    // execcute the tree
    tree.tickWhileRunning(); // tree.tickRoot();


    return 0;
}