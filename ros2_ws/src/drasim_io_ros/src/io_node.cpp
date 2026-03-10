#include "drasim_io_ros/io_node.hpp"
#include <drasim_core/memory_image.hpp>
#include <drasim_core/io_mapping.hpp>
#include <chrono>
#include <string>
#include <thread>
using namespace std::chrono_literals;
namespace drasim_io_ros {
IONode::IONode(const rclcpp::NodeOptions&o):rclcpp::Node("drasim_io_node",o){
  this->declare_parameter<int>("publish_rate_hz",50);
  int hz=this->get_parameter("publish_rate_hz").as_int();
  io_pub_=this->create_publisher<drasim_interfaces::msg::DigitalIO>("/drasim/io_state",rclcpp::QoS(10));
  set_do_srv_=this->create_service<drasim_interfaces::srv::SetDO>("/drasim/set_do",[this](auto q,auto r){handle_set_do(q,r);});
  get_di_srv_=this->create_service<drasim_interfaces::srv::GetDI>("/drasim/get_di",[this](auto q,auto r){handle_get_di(q,r);});
  timer_=this->create_wall_timer(std::chrono::milliseconds(1000/hz),[this]{publish_io_state();});}
void IONode::publish_io_state(){
  auto&mem=drasim_core::MemoryImage::instance();
  drasim_interfaces::msg::DigitalIO msg;msg.stamp=this->now();
  for(std::size_t i=0;i<drasim_core::MemoryImage::DI_COUNT;++i)msg.di_state[i]=mem.get_di(i+1);
  for(std::size_t i=0;i<drasim_core::MemoryImage::DO_COUNT;++i)msg.do_state[i]=mem.get_do(i+1);
  io_pub_->publish(msg);}
void IONode::handle_set_do(std::shared_ptr<drasim_interfaces::srv::SetDO::Request>req,std::shared_ptr<drasim_interfaces::srv::SetDO::Response>res){
  std::size_t pin=drasim_core::IOMapping::instance().resolve_do(req->pin_index);
  if(!pin){res->success=false;res->message="Unknown DO: "+req->pin_index;return;}
  bool s=(req->status=="ON");drasim_core::MemoryImage::instance().set_do(pin,s);
  if(req->delay_time>0.0){double d=req->delay_time;std::size_t p=pin;
    std::thread([p,d,s]{std::this_thread::sleep_for(std::chrono::duration<double>(d));drasim_core::MemoryImage::instance().set_do(p,!s);}).detach();}
  res->success=true;res->message="OK";}
void IONode::handle_get_di(std::shared_ptr<drasim_interfaces::srv::GetDI::Request>req,std::shared_ptr<drasim_interfaces::srv::GetDI::Response>res){
  std::size_t sp=drasim_core::IOMapping::instance().resolve_di(req->pin_index);
  if(!sp){res->success=false;res->message="Unknown DI: "+req->pin_index;return;}
  int32_t len=(req->length<=0)?1:req->length;
  if(len==1){bool v=drasim_core::MemoryImage::instance().get_di(sp);res->status=v?"ON":"OFF";res->status_num=v?1:0;}
  else{uint32_t mask=drasim_core::MemoryImage::instance().get_di_block(sp,(std::size_t)len);res->status="MULTI";res->status_num=(int32_t)mask;}
  res->success=true;res->message="OK";}
}//ns
