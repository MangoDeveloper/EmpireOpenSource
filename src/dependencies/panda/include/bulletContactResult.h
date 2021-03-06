// Filename: bulletContactResult.h
// Created by:  enn0x (08Mar10)
//
////////////////////////////////////////////////////////////////////
//
// PANDA 3D SOFTWARE
// Copyright (c) Carnegie Mellon University.  All rights reserved.
//
// All use of this software is subject to the terms of the revised BSD
// license.  You should have received a copy of this license along
// with this source code in a file named "LICENSE."
//
////////////////////////////////////////////////////////////////////

#ifndef __BULLET_CONTACT_RESULT_H__
#define __BULLET_CONTACT_RESULT_H__

#include "pandabase.h"

#include "bullet_includes.h"
#include "bulletManifoldPoint.h"

#include "pvector.h"

////////////////////////////////////////////////////////////////////
//       Class : BulletContact
// Description :
////////////////////////////////////////////////////////////////////
struct EXPCL_PANDABULLET BulletContact {

public:
  BulletContact();
  BulletContact(const BulletContact &other);

PUBLISHED:
  INLINE BulletManifoldPoint &get_manifold_point();
  INLINE PandaNode *get_node0() const;
  INLINE PandaNode *get_node1() const;
  INLINE int get_idx0() const;
  INLINE int get_idx1() const;
  INLINE int get_part_id0() const;
  INLINE int get_part_id1() const;

private:
  static btManifoldPoint _empty;

  BulletManifoldPoint _mp;

  PT(PandaNode) _node0;
  PT(PandaNode) _node1;

  int _part_id0;
  int _part_id1;
  int _idx0;
  int _idx1;

  friend struct BulletContactResult;
};

////////////////////////////////////////////////////////////////////
//       Class : BulletContactResult
// Description :
////////////////////////////////////////////////////////////////////
struct EXPCL_PANDABULLET BulletContactResult : public btCollisionWorld::ContactResultCallback {

PUBLISHED:
  INLINE int get_num_contacts() const;
  INLINE BulletContact &get_contact(int idx);
  MAKE_SEQ(get_contacts, get_num_contacts, get_contact);

public:
#if BT_BULLET_VERSION >= 281
  virtual bool needsCollision(btBroadphaseProxy *proxy0) const;

  virtual btScalar addSingleResult(btManifoldPoint &mp,
      const btCollisionObjectWrapper *wrap0, int part_id0, int idx0, 
      const btCollisionObjectWrapper *wrap1, int part_id1, int idx1); 
#else
  virtual btScalar addSingleResult(btManifoldPoint &mp,
      const btCollisionObject *obj0, int part_id0, int idx0,
      const btCollisionObject *obj1, int part_id1, int idx1);
#endif

protected:
  BulletContactResult();

#if BT_BULLET_VERSION >= 281
  void use_filter(btOverlapFilterCallback *cb, btBroadphaseProxy *proxy);
#endif

private:
  static BulletContact _empty;

  btAlignedObjectArray<BulletContact> _contacts;

#if BT_BULLET_VERSION >= 281
  bool _filter_set;
  btOverlapFilterCallback *_filter_cb;
  btBroadphaseProxy *_filter_proxy;
#endif

  friend class BulletWorld;
};

#include "bulletContactResult.I"

#endif // __BULLET_CONTACT_RESULT_H__
