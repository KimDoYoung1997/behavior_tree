// Includes the Behavior Tree header files for creating and managing behavior trees.
#include "behaviortree_cpp/bt_factory.h"
#include "behaviortree_cpp/action_node.h"

// Includes for standard input/output and chrono literals for timing
#include <iostream>
#include <chrono>

// Using directives for simplifying syntax
using namespace std::chrono_literals;

// Custom action node class derived from SyncActionNode for approaching an object.
class ApproachObject : public BT::SyncActionNode
{
public:
    // Constructor with initialization list to initialize the SyncActionNode base class.
    explicit ApproachObject(const std::string &name) 
    : BT::SyncActionNode(name,{})
    {

    }
    
    // You must override the virtual function tick()
    // Overrides the tick function to perform the approach action.
    BT::NodeStatus tick() override 
    {
        // Print the action name to the console.
        std::cout <<"Approach Object: " << this->name() << std::endl; //Approach Object: approach_object
        // Simulate action duration using sleep.
        std::this_thread::sleep_for(5s);
        // Return success once the action is complete.
        return BT::NodeStatus::SUCCESS;
    }

};

// Function acting as a condition node to check the battery status.
BT::NodeStatus CheckBattery()
{
    // Print battery status to the console.
    std::cout << "Battery OK" << std::endl;
    // Always returns success for this example.
    return BT::NodeStatus::SUCCESS;
}

// Custom class for controlling a gripper.
class GripperInterface
{
public:
    // Constructor initializes the gripper as open.
    GripperInterface()
    : _open(true)
    {

    }

    // Method to open the gripper.
    BT::NodeStatus open()
    {
        _open = true;
        std::cout << "Gripper open" << std::endl;
        return BT::NodeStatus::SUCCESS;
    }
    
    // Method to close the gripper.
    BT::NodeStatus close()
    {
        _open = false;
        std::cout << "Gripper close" << std::endl;
        return BT::NodeStatus::SUCCESS;
    }

private:
    // Private member to track gripper state.
    bool _open;

};

int main()
{
    // Create a BehaviorTreeFactory instance for registering and creating nodes.
    BT::BehaviorTreeFactory factory;
    // Register the custom ApproachObject node type.
    factory.registerNodeType<ApproachObject>("ApproachObject");
    // Register the CheckBattery function as a simple condition.
    factory.registerSimpleCondition("CheckBattery", std::bind(CheckBattery));
    
    // Create an instance of GripperInterface.
    GripperInterface gripper;

    // Register custom methods of GripperInterface as simple actions.
    factory.registerSimpleAction(
        "OpenGripper",
        std::bind(&GripperInterface::open,&gripper));

    factory.registerSimpleAction(
        "CloseGripper",
        std::bind(&GripperInterface::close,&gripper)
    );

    // Create the behavior tree from an XML file.
    auto tree = factory.createTreeFromFile("./../bt_tree.xml");

    // Execute the tree in a loop until it signals completion.
    //tree.tickWhileRunning(); // This is an alternative to manually ticking the root.
    tree.tickOnce();
    return 0;
}