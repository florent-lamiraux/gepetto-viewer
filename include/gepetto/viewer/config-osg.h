//
//  config-osg.h
//  gepetto-viewer
//
//  Created by Justin Carpentier on 06/02/2014.
//  Modified by Mathieu Geisert in November 2014.
//  Copyright (c) 2014 LAAS-CNRS. All rights reserved.
//

#ifndef DynAndGraph_config_h
#define DynAndGraph_config_h

#include <gepetto/viewer/fwd.h>
#include <gepetto/viewer/macros.h>

#include <QMetaType>
//#include <osg/AlphaFunc>
//#include <osg/AutoTransform>
//#include <osg/BlendFunc>
#include <vsg/app/Camera.h>
//#include <osg/ClearNode>
//#include <osg/Depth>
//#include <osg/Geode>
#include <vsg/nodes/Geometry.h>
#include <vsg/vk/Context.h>
//#include <osg/GraphicsContext>
//#include <osg/Group>
#include <vsg/nodes/Group.h>
//#include <osg/Light>
//#include <osg/LightSource>
#include <vsg/nodes/Light.h>
//#include <osg/LineWidth>
#include <vsg/commands/SetLineWidth.h>
//#include <osg/Material>
#include <vsg/state/material.h>
//#include <osg/MatrixTransform>
#include <vsg/nodes/MatrixTransform.h>
//#include <osg/Node>
#include <vsg/nodes/Node.h>
//#include <osg/PolygonMode>
//#include <osg/PositionAttitudeTransform>
//#include <osg/Shape>
//#include <osg/ShapeDrawable>
//#include <osg/State>
#include <vsg/vk/State.h>
//#include <osg/StateSet>
//#include <osg/Switch>
#include <vsg/nodes/Switch.h>
//#include <osg/Viewport>
#include <vsg/state/ViewportState.h>
//#include <osgViewer/Viewer>
#include <vsg/app/Viewer.h>
//#include <osgViewer/ViewerBase>

namespace vsg {

DEF_CLASS_SMART_PTR(Geode)

// DEF_OSG_CLASS_REF_PTR(Sphere)
// DEF_OSG_CLASS_REF_PTR(Box)
// DEF_OSG_CLASS_REF_PTR(Cone)
// DEF_OSG_CLASS_REF_PTR(Cylinder)
// DEF_OSG_CLASS_REF_PTR(Capsule)
//DEF_OSG_CLASS_REF_PTR(ShapeDrawable)
DEF_OSG_CLASS_REF_PTR(Geometry)
DEF_OSG_CLASS_REF_PTR(SetLineWidth)

//DEF_OSG_CLASS_REF_PTR(Geode)
//DEF_OSG_CLASS_REF_PTR(PositionAttitudeTransform)
//DEF_OSG_CLASS_REF_PTR(AutoTransform)
DEF_OSG_CLASS_REF_PTR(MatrixTransform)
DEF_OSG_CLASS_REF_PTR(Light)
//DEF_OSG_CLASS_REF_PTR(LightSource)

DEF_OSG_CLASS_REF_PTR(Node)
DEF_OSG_CLASS_REF_PTR(Group)
DEF_OSG_CLASS_REF_PTR(Switch)
//DEF_OSG_CLASS_REF_PTR(ClearNode)

//DEF_OSG_CLASS_REF_PTR(Depth)

//DEF_OSG_CLASS_REF_PTR(AlphaFunc)
//DEF_OSG_CLASS_REF_PTR(BlendFunc)

DEF_OSG_CLASS_REF_PTR(State)
DEF_OSG_CLASS_REF_PTR(StateGroup)

//DEF_OSG_CLASS_REF_PTR(Material)

DEF_OSG_CLASS_REF_PTR(Camera)
//DEF_OSG_CLASS_REF_PTR(Viewport)
//DEF_OSG_CLASS_REF_PTR(GraphicsContext)

DEF_OSG_CLASS_REF_PTR(vec3Array)
DEF_OSG_CLASS_REF_PTR(vec4Array)

//DEF_OSG_CLASS_REF_PTR(PolygonMode)

//typedef ::vsg::ref_ptr<GraphicsContext::Traits> TraitsRefPtr;

DEF_OSG_CLASS_REF_PTR(Viewer)

} /* namespace vsg */

typedef ::vsg::t_vec2<gepetto::viewer::value_type> osgVector2;
typedef ::vsg::t_vec3<gepetto::viewer::value_type> osgVector3;
typedef ::vsg::t_vec4<gepetto::viewer::value_type> osgVector4;

typedef ::vsg::t_quat<gepetto::viewer::value_type> osgQuat;

namespace gepetto {
namespace viewer {

enum VisibilityMode { VISIBILITY_OFF = 0, VISIBILITY_ON = 1, ALWAYS_ON_TOP };

enum LightingMode { LIGHT_INFLUENCE_OFF = 0, LIGHT_INFLUENCE_ON = 1 };

enum WireFrameMode { FILL = 0, WIREFRAME, FILL_AND_WIREFRAME };

enum FaceMode { FACE = 0, EDGE, FACE_AND_EDGE };

struct Configuration {
  osgVector3 position;
  osgQuat quat;
  Configuration() {}
  /// \param XYZW when false, the 4 last parameters are a quaternion (w,x,y,z)
  ///             otherwise, a quaternion (x,y,z,w)
  explicit Configuration(const float* a, bool XYZW)
      : position(a[0], a[1], a[2]),
        quat(a[(XYZW ? 3 : 4)], a[(XYZW ? 4 : 5)], a[(XYZW ? 5 : 6)],
             a[(XYZW ? 6 : 3)]) {}
  Configuration(const osgVector3& p, const osgQuat& q) : position(p), quat(q) {}

  bool operator==(const Configuration& other) const {
    return position == other.position && quat == other.quat;
  }

  bool operator!=(const Configuration& other) const {
    return position != other.position || quat != other.quat;
  }

};

} /* namespace viewer */
} /* namespace gepetto */

Q_DECLARE_METATYPE(osgVector2)
Q_DECLARE_METATYPE(osgVector3)
Q_DECLARE_METATYPE(osgVector4)
Q_DECLARE_METATYPE(gepetto::viewer::Configuration)

#endif
