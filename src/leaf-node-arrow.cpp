//
//  leaf-node-arrow.cpp
//  gepetto-viewer
//
//  Created by Pierre Fernbach in june 2015.
//  Copyright (c) 2015 LAAS-CNRS. All rights reserved.
//

#include <gepetto/viewer/leaf-node-arrow.h>

#include <osg/Version>

namespace gepetto {
namespace viewer {

/* Declaration of private function members */

void LeafNodeArrow::init() {
}

void LeafNodeArrow::resetGeodeContent() {
}

LeafNodeArrow::LeafNodeArrow(const std::string& name, const osgVector4& color,
                             float radius, float size)
    : NodeDrawable(name), color_(color) {
  radius_ = radius;
  size_ = size;

  init();
}

LeafNodeArrow::LeafNodeArrow(const LeafNodeArrow& other)
    : NodeDrawable(other.getID()) {
  init();
  // TODO
}

void LeafNodeArrow::initWeakPtr(LeafNodeArrowWeakPtr other_weak_ptr) {
  weak_ptr_ = other_weak_ptr;
}

/* End of declaration of private function members */

/* Declaration of protected function members */

LeafNodeArrowPtr_t LeafNodeArrow::create(const std::string& name,
                                         const osgVector4& color,
                                         float radiusCenter, float size) {
  LeafNodeArrowPtr_t shared_ptr(
      new LeafNodeArrow(name, color, radiusCenter, size));

  // Add reference to itself
  shared_ptr->initWeakPtr(shared_ptr);

  return shared_ptr;
}

LeafNodeArrowPtr_t LeafNodeArrow::create(const std::string& name,
                                         const osgVector4& color,
                                         float radiusCenter) {
  LeafNodeArrowPtr_t shared_ptr(
      new LeafNodeArrow(name, color, radiusCenter, 4 * radiusCenter));

  // Add reference to itself
  shared_ptr->initWeakPtr(shared_ptr);

  return shared_ptr;
}

LeafNodeArrowPtr_t LeafNodeArrow::createCopy(LeafNodeArrowPtr_t other) {
  LeafNodeArrowPtr_t shared_ptr(new LeafNodeArrow(*other));

  // Add reference to itself
  shared_ptr->initWeakPtr(shared_ptr);

  return shared_ptr;
}

/* End of declaration of protected function members */

/* Declaration of public function members */

LeafNodeArrowPtr_t LeafNodeArrow::clone(void) const {
  return LeafNodeArrow::createCopy(weak_ptr_.lock());
}

LeafNodeArrowPtr_t LeafNodeArrow::self(void) const { return weak_ptr_.lock(); }

void LeafNodeArrow::setRadius(const float& radius) {
  if (radius != getRadius()) {  // avoid useless resize
    radius_ = radius;
    resetGeodeContent();
  }
}

float LeafNodeArrow::getRadius() const { return radius_; }

void LeafNodeArrow::setSize(const float& size) {
  if (size != getSize()) {  // avoid useless resize
    size_ = size;
    resetGeodeContent();
  }
}

float LeafNodeArrow::getSize() const { return size_; }

void LeafNodeArrow::setColor(const osgVector4& color) {
  cylinder_drawable_->setColor(color);
  cone_drawable_->setColor(color);
#if OSG_VERSION_GREATER_OR_EQUAL(3, 5, 6)
  cylinder_drawable_->build();
  cone_drawable_->build();
#else
  cylinder_drawable_->dirtyDisplayList();
  cone_drawable_->dirtyDisplayList();
  cylinder_drawable_->dirtyBound();
  cone_drawable_->dirtyBound();
#endif
  color_ = color;
  setTransparentRenderingBin(color[3] <
                             Node::TransparencyRenderingBinThreshold);
  setDirty();
}

void LeafNodeArrow::resize(float radius, float length) {
  if (length != getSize() || radius != getRadius()) {  // avoid useless resize
    size_ = length;
    radius_ = radius;

    resetGeodeContent();
  }
}

LeafNodeArrow::~LeafNodeArrow() {
  /* Proper deletion of all tree scene */

  weak_ptr_.reset();
}

/* End of declaration of public function members */

} /* namespace viewer */
} /* namespace gepetto */
