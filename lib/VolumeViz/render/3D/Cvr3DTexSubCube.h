#ifndef COIN_CVR3DTEXSUBCUBE_H
#define COIN_CVR3DTEXSUBCUBE_H

/**************************************************************************\
 *
 *  This file is part of the SIM Voleon visualization library.
 *  Copyright (C) 2003-2004 by Systems in Motion.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  ("GPL") version 2 as published by the Free Software Foundation.
 *  See the file LICENSE.GPL at the root directory of this source
 *  distribution for additional information about the GNU GPL.
 *
 *  For using SIM Voleon with software that can not be combined with
 *  the GNU GPL, and for taking advantage of the additional benefits
 *  of our support services, please contact Systems in Motion about
 *  acquiring a SIM Voleon Professional Edition License.
 *
 *  See <URL:http://www.coin3d.org/> for more information.
 *
 *  Systems in Motion, Teknobyen, Abels Gate 5, 7030 Trondheim, NORWAY.
 *  <URL:http://www.sim.no/>.
 *
\**************************************************************************/

#include <Inventor/SbVec3s.h>
#include <Inventor/SbVec3f.h>
#include <Inventor/SbVec3f.h>
#include <Inventor/SbMatrix.h>
#include <Inventor/lists/SbList.h>
#include <Inventor/misc/SoState.h>
#include <Inventor/system/gl.h>
#include <Inventor/C/glue/gl.h>
#include <Inventor/SbClip.h>
#include <Inventor/SbViewVolume.h>

#include <VolumeViz/misc/CvrCLUT.h>
#include <VolumeViz/render/common/CvrTextureObject.h>

struct subcube_slice {
  SbList <SbVec3f> texcoord; 
  SbList <SbVec3f> vertex;  
};

class Cvr3DTexSubCube {
public:
  Cvr3DTexSubCube(SoGLRenderAction * action,
                  const CvrTextureObject * texobj,
                  const SbVec3f & cubesize, 
                  const SbVec3s & texsize,
                  const SbBool compresstextures);
  ~Cvr3DTexSubCube();

  enum Interpolation { NEAREST, LINEAR };

  void render(const SoGLRenderAction * action, Interpolation interpolation);
  void renderBBox(const SoGLRenderAction * action, int counter); // Debug method

  SbBool isPaletted(void) const;
  void setPalette(const CvrCLUT * newclut);

  SbBool checkIntersectionSlice(SbVec3f const & cubeorigo, 
                                const SbViewVolume & viewvolume, 
                                float viewdistance, SbMatrix);
  SbBool checkIntersectionIndexedFaceSet(SbVec3f const & cubeorigo, 
                                         const SbVec3f * vertexlist,
                                         const int * indices,
                                         const unsigned int numindices,
                                         SbMatrix m);

  static void * subcube_clipperCB(const SbVec3f & v0, void * vdata0, 
                                  const SbVec3f & v1, void * vdata1,
                                  const SbVec3f & newvertex,
                                  void * userdata);

  float getDistanceFromCamera();
  void setDistanceFromCamera(float dist);

private:
   
  void activateTexture(Interpolation interpolation) const;
  void activateCLUT(const SoGLRenderAction * action); 
  void deactivateCLUT(const SoGLRenderAction * action); 
 
  SbBool clipPolygonAgainstCube(SbClip & cubeclipper, const SbVec3f & cubeorigo);

  const CvrTextureObject * textureobject;
  const CvrCLUT * clut;

  SbVec3s texdims;
  SbVec3s originaltexsize;
  SbVec3f dimensions;
  SbVec3f origo;
  SbBool ispaletted;

  float distancefromcamera;

  SbList <subcube_slice> volumeslices;
  SbList <SbVec3f *> texcoordlist;

};


#endif //COIN_CVR3DTEXSUBPAGE_H
