#include <behaviortree_cpp/basic_types.h> // BT 기본 타입을 포함합니다.
#include <behaviortree_cpp/decorators/subtree_node.h> // 서브트리 노드 데코레이터를 포함합니다.
#include <behaviortree_cpp/exceptions.h> // BT 예외 클래스를 포함합니다.
#include <behaviortree_cpp/tree_node.h> // 트리 노드의 기본 클래스를 포함합니다.
#include <iostream> // 표준 입출력을 위한 헤더입니다.
#include <chrono> // 시간 관련 기능을 사용하기 위한 헤더입니다.
#include <string> // 문자열 처리를 위한 헤더입니다.
#include <thread> // 스레드 관련 기능을 사용하기 위한 헤더입니다.
#include "behaviortree_cpp/bt_factory.h" // BT 팩토리 클래스를 포함합니다.
#include "behaviortree_cpp/action_node.h" // 액션 노드의 기본 클래스를 포함합니다.
#include <vector> // port 타입으로 vector를 사용하기 위해

using namespace std::chrono_literals; // 시간 관련 리터럴 사용을 위한 네임스페이스입니다

// 공이 발견되었는지 확인하는 조건 함수입니다.
// Condition node 
BT::NodeStatus ballFound()
{
    std::cout<<"Ball not found"<< std::endl; // 공을 찾지 못한 경우 메시지 출력
    return BT::NodeStatus::FAILURE; // 공을 찾지 못했다는 상태를 반환합니다.
}

// Action node with inheritance of SyncActionNode
// 공을 찾는 행동을 정의하는 액션 노드 클래스입니다.
class FindBall : public BT::SyncActionNode
{
public:
    //The Constructor now needs to have a slightly different signature instead of just one argument
    explicit FindBall(const std::string &name, const BT::NodeConfiguration &config) 
    : BT::SyncActionNode(name,config) // 생성자에서 이름과 설정을 초기화합니다.
    {
        //std::cout <<"FindBall class Constructor!" << std::endl;
        //std::this_thread::sleep_for(5s);
    }

//  ==s=t=a=r=t=============== add output ports =====================
// 이 액션 노드에서 사용할 출력 포트를 정의합니다.
    // It is mandatory to define this STATIC method.
    //  BT 의 PortsList providedPorts() 함수를 전역에서 사용하기위해 static이 필요했음  
    static BT::PortsList providedPorts()
    {
    // This action has a single output port called "ball_location"
    // 공의 위치 정보를 담을 'ball_location' 출력 포트를 정의합니다.
        return {BT::OutputPort<std::vector<int>>("ball_location")}; // 여기선 int를 담은 vector를 output port로 사용하지만, 필요에 따라 데이터 타입을 바꿀 수 있다.
    }
// 이 액션 노드에서 사용할 출력 포트를 정의합니다.
//  ==e=n=d================= add output ports =======================

    BT::NodeStatus tick() override 
    {
        std::this_thread::sleep_for(3s);     // 공을 찾는데 걸리는 시간을 가정합니다.
        std::vector<int> ballLocation{1,2,3}; // vector 하나 생성하고 이를 node간에 send할 것임 (value로 사용되는듯?) // 가정된 공의 위치 정보입니다.
        BT::TreeNode::setOutput("ball_location", ballLocation); // output port : ball_location , key : location , value : ballLocation{1,2,3}  // 출력 포트(ball_location)에 위치 정보(ballLocation)를 설정합니다.
        std::cout <<"Ball Found! " << this->name() << std::endl; // 공을 찾았다는 메시지를 출력합니다.

        return BT::NodeStatus::SUCCESS; // 공을 성공적으로 찾았다는 상태를 반환합니다.
    }

};




// 공에 접근하는 조건을 확인하는 함수입니다.
// Condition node 
BT::NodeStatus ballClose(BT::TreeNode &self) // 새로운 argument 추가
{
// you need to create msg
//Input port : ball_location , key : location
// xml파일에서 읽어온 input port와 key를 가져온다.
    //BT::Optional<std::vector<int>> msg= self.getInput<std::vector<int>>("ball_location"); // 구버전 코드로 실행시 컴파일 에러 발생
    auto msg = self.getInput<std::vector<int>>("ball_location"); // 입력 포트(ball_location)에서 공의 위치 정보를 가져옵니다.
//  we also need to check if this message exists 
//  this is how we do it if message is done we will throw a runtime error saying missing required input message 
    if(!msg) // 위치 정보가 없으면 예외를 발생시킵니다.
    {
        throw BT::RuntimeError("missing required input[message]: ",msg.error());
    }
    
    for (const auto position_coordinate : msg.value())  // 위치 정보를 순회하며 출력합니다.
    {
        std::cout << position_coordinate <<" ";
    }

    std::cout<<"The location is far away"<<std::endl;   // 공이 멀리 있다는 메시지를 출력합니다.
    return BT::NodeStatus::FAILURE;                     // 공이 가까이 있지 않으므로 실패 상태를 반환합니다.
}

// 공에 접근하는 행동을 정의하는 액션 노드 클래스입니다.
// Action node with inheritance of SyncActionNode
// FindBall 노드(BT::SyncActionNode 상속)에서 Output 포트를 설정한것과 반대로 ApproachBall 노드에서는 Input 포트를 설정해야한다.
// ballClose 노드(BT::SyncActionNode를 상속하지 않음)에서 Input 포트를 설정한것과 유사하게 ApproachBall 노드에서는 Input 포트를 설정해야한다.
class ApproachBall : public BT::SyncActionNode
{
public:
//The Constructor now needs to have a slightly different signature instead of just one argument
    explicit ApproachBall(const std::string &name,const BT::NodeConfiguration &config) // 생성자에서 이름과 설정을 초기화합니다.
    :BT::SyncActionNode(name,config) 
    {
        //std::cout<<"ApproachBall class Constructor "<<std::endl;
    }

//  ==s=t=a=r=t=============== add Input ports =====================
// 이 액션 노드에서 사용할 입력 포트를 정의합니다.


    static BT::PortsList providedPorts()
    {
        // FindBall 노드(BT::SyncActionNode 상속)에서 Output 포트를 BT::OutputPort 처럼 설정한것과 반대로 ApproachBall 노드에서는 Input 포트를 BT::InputPort 으로 설정하는 것을 볼 수 있습니다.
        return {BT::InputPort<std::vector<int>>("ball_location")}; // Input 포트(ball_location)에 위치 정보(ballLocation)를 설정합니다.
    }
    
// 이 액션 노드에서 사용할 입력 포트를 정의합니다.
//  ==e=n=d================ add Input ports ========================


// tick 함수 
// In our tick method, we will use our input Port like we did for FindBall
    BT::NodeStatus tick() override
    {

// you need to create msg
//Input port : ball_location , key : location
// xml파일에서 읽어온 input port와 key를 가져온다.
        // BT::Optional<std::vector<int>> msg= self.getInput<std::vector<int>>("ball_location"); // 강의에는 이렇게 msg를 만들라고 하는데, 이대로 따라하면 컴파일 에러가 생김. 구버전 bt 코드인것 같다.
        // 72번째 줄과 비교해보자. BT::SyncActionNode를 상속하지 않는 ballClose 노드에서는 msg를 선언하려면 self 가 필요했는데, BT::SyncActionNode를 상속하는 ApproachBall 노드는 self를 쓰지 않는다.
        auto msg = getInput<std::vector<int>>("ball_location"); //72번째 줄의 다음 코드와 비교하자. auto msg = self.getInput<std::vector<int>>("ball_location");

    
//  we also need to check if this message exists 
//  if message is none we will throw a runtime error saying missing required input message 
        if(!msg) // 위치 정보가 없으면 예외를 발생시킵니다.
        {
            throw BT::RuntimeError("missing required input[message]: ",msg.error());
        }
        for (const auto position_coordinate : msg.value()) // 위치 정보를 순회하며 출력합니다.
        {
            std::cout << position_coordinate <<" ";
        }
        
        std::this_thread::sleep_for(3s); // 공에 접근하는 과정을 가정합니다.
        std::cout <<"Ball Approached " << this->name() << std::endl; // 공에 접근했다는 메시지를 출력합니다.
        return BT::NodeStatus::SUCCESS; // 공에 성공적으로 접근했다는 상태를 반환합니다.
    }

};


// <--------------- 이후 코드는 BlackBoard 에 대한 추가 반영사항이 없음 --------------->

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
    factory.registerNodeType<FindBall>("FindBall"); // Action node with inheritance of SyncActionNode and has an output port with key {location}

    // BT::SyncActionNode 를 상속하지 않는 BallClose 노드는 InputPort를 노드 내에서 add하는 부분이 없었다. 따라서 이 부분에서 추가로 add해줘야 한다.
    BT::PortsList say_something_ports = {BT::InputPort<std::vector<int>>("ball_location")};
    // 기존 코드 주석 factory.registerSimpleCondition("BallClose", std::bind(ballClose));// BlackBoard 개념 도입전 사용하던 코드. 지금은 주석처리 해야만 한다.
    factory.registerSimpleCondition("BallClose", ballClose,say_something_ports); // BlackBoard 개념 도입후 바뀐 코드. // Condition node and has an input port with key {location}
    factory.registerNodeType<ApproachBall>("ApproachBall"); // Action node with inheritance of SyncActionNode and has an input port with key {location}

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