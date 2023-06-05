//
//  group-node.cpp
//  gepetto-viewer
//
//  Created by Justin Carpentier, Mathieu Geisert in November 2014.
//  Copyright (c) 2014 LAAS-CNRS. All rights reserved.
//

#include <gepetto/viewer/group-node.h>

namespace gepetto {
namespace viewer {

/* Declaration of private function members */

GroupNode::GroupNode(const std::string& name)
    : Node(name), list_of_objects_() {}

GroupNode::GroupNode(const GroupNode& other) : Node(other), list_of_objects_() {
  size_t i;
  for (i = 0; i < other.getNumOfChildren(); i++) {
    addChild(other.getChild(i));
  }
}

void GroupNode::initWeakPtr(GroupNodeWeakPtr other_weak_ptr) {
  weak_ptr_ = other_weak_ptr;
}

/* End of declaration of private function members */

/* Declaration of protected function members */
GroupNodePtr_t GroupNode::create(const std::string& name) {
  GroupNodePtr_t shared_ptr(new GroupNode(name));

  // Add reference to itself
  shared_ptr->initWeakPtr(shared_ptr);

  return shared_ptr;
}

GroupNodePtr_t GroupNode::createCopy(GroupNodePtr_t other) {
  GroupNodePtr_t shared_ptr(new GroupNode(*other));

  // Add reference to itself
  shared_ptr->initWeakPtr(shared_ptr);

  return shared_ptr;
}

/* End of declaration of protected function members */

/* Declaration of public function members */

GroupNodePtr_t GroupNode::clone(void) const {
  return GroupNode::createCopy(weak_ptr_.lock());
}

GroupNodePtr_t GroupNode::self(void) const { return weak_ptr_.lock(); }

bool GroupNode::addChild(NodeWeakPtr child_ptr) {
  list_of_objects_.push_back(child_ptr);
  this->asQueue()->addChild(child_ptr.lock()->asGroup());
  setDirty();
  return true;
}

// bool operator==(NodeWeakPtr w1, const NodeWeakPtr w2) {
//   return w1 == const_cast<NodeWeakPtr>(w2);
// }

bool GroupNode::removeChild(NodeWeakPtr child_ptr) {
  NodePtr_t child(child_ptr.lock());
  Nodes_t::iterator it = list_of_objects_.begin();
  for (;it != list_of_objects_.end(); ++it) {
    if (it->lock() == child) break;
  }
  if (it != list_of_objects_.end()) list_of_objects_.erase(it);
  bool removed = this->asQueue()->removeChild(
      this->asQueue()->getChildIndex(child_ptr.lock()->asGroup()));
  if (removed) setDirty();
  return removed;
}

bool GroupNode::hasChild(NodeWeakPtr child_ptr) const {
  NodePtr_t child(child_ptr.lock());
  for (Nodes_t::const_iterator it = list_of_objects_.begin();
       it != list_of_objects_.end(); ++it) {
    if (it->lock() == child) return true;
  }
  return false;
}

void GroupNode::removeAllChildren() {
  list_of_objects_.clear();
  this->asQueue()->removeChild(0, this->asQueue()->getNumChildren());
  setDirty();
}

void GroupNode::setLightingMode(const LightingMode& lighting_state) {
  Node::setLightingMode(lighting_state);
  Nodes_t::iterator iter_list_of_objects;
  for (iter_list_of_objects = list_of_objects_.begin();
       iter_list_of_objects != list_of_objects_.end(); iter_list_of_objects++) {
    iter_list_of_objects->lock()->setLightingMode(lighting_state);
  }
}

void GroupNode::setWireFrameMode(const WireFrameMode& wireframe_state) {
  Node::setWireFrameMode(wireframe_state);

  Nodes_t::iterator iter_list_of_objects;
  for (iter_list_of_objects = list_of_objects_.begin();
       iter_list_of_objects != list_of_objects_.end(); iter_list_of_objects++) {
    iter_list_of_objects->lock()->setWireFrameMode(wireframe_state);
  }
}

void GroupNode::setAlpha(const float& alpha) {
  alpha_ = alpha;
  Nodes_t::iterator iter_list_of_objects;
  for (iter_list_of_objects = list_of_objects_.begin();
       iter_list_of_objects != list_of_objects_.end(); iter_list_of_objects++) {
    iter_list_of_objects->lock()->setAlpha(alpha);
  }
}

void GroupNode::setColor(const osgVector4& color) {
  Nodes_t::iterator iter_list_of_objects;
  for (iter_list_of_objects = list_of_objects_.begin();
       iter_list_of_objects != list_of_objects_.end(); iter_list_of_objects++) {
    iter_list_of_objects->lock()->setColor(color);
  }
}

void GroupNode::traverse(NodeVisitor& visitor) {
  Nodes_t::iterator iter_list_of_objects;
  for (iter_list_of_objects = list_of_objects_.begin();
       iter_list_of_objects != list_of_objects_.end(); iter_list_of_objects++) {
    iter_list_of_objects->lock()->accept(visitor);
  }
}

osg::ref_ptr<osg::Node> GroupNode::getOsgNode() const {
  return this->asQueue();
}

GroupNode::~GroupNode() { removeAllChildren(); }

/* End of declaration of public function members */

} /* namespace viewer */
} /* namespace gepetto */
