//
//  SceneSpace.h
//  Dissert
//
//  Created by Olivier Legat on 09/04/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#ifndef SCENE_SPACE_H_
#define SCENE_SPACE_H_

#include <platform.h>

class Camera;
class Mesh;
class SceneObject;
class SceneDynamic;
class MazeBVH;
class MazeBVHNode;
class MazeColliderAABB;

class SceneSpace
extends Object
{
public:
    SceneSpace();
    ~SceneSpace();
    
    Camera* GetActiveCamera() const {return this->activeCamera;}
    void SetActiveCamera(Camera* cam) {this->activeCamera = cam;}
    
    SceneObject* AddSceneObject();
    SceneObject* AddSceneObject(String name);
    SceneObject* AddSceneObject(String name, Mesh* mesh);
    SceneDynamic* AddSceneDynamic(Vector3 startPos, Vector3 volume);
    
    SceneObject*  GetSceneObject (int Id) const {return (SceneObject*) objects[Id];}
    SceneDynamic* GetSceneDynamic(int Id) const {return (SceneDynamic*)dynamics[Id];}
    int GetObjectCount()  const {return (int) this->objects.size(); }
    int GetDynamicCount() const {return (int) this->dynamics.size();}
    
    SceneObject* MakeGrid();
    
    void Update();
    
private:
    Camera* activeCamera;
    
    Array<SceneObject*> objects;
    Array<SceneDynamic*> dynamics;
    
    /**
     * Do collision dect. tests and collision response.
     */
    void checkCollisions(SceneDynamic* dyn);
    
    /**
     *
     */
    void checkCollisions(SceneDynamic* dyn, MazeBVH* bvh);
    
    /**
     *
     */
    void checkCollisions(SceneDynamic* dyn, MazeBVHNode* node);
    
    /**
     * @param dyn A dynamic object.
     * @param aabb A static collider in the scene.
     * @return overlap values on the x, y, z axes.
     */
    Vector3 calcOverlap(const SceneDynamic* dyn, const MazeColliderAABB* aabb) const;
    
    /**
     * @param dyn A dynamic object.
     * @param aabb A static collider in the scene.
     * @return true if dyn collides with aabb (overlaps on atleast 1 axis)
     */
    bool isColliding(const SceneDynamic* dyn, const MazeColliderAABB* aabb) const;
    
    /**
     * Does the collision response for 2 colliding objects. dyn and aabb must be colliding.
     * Moves dyn based on overlap with aabb.
     * @param dyn A dynamic object which is colliding with aabb
     * @param aabb A static collider which is colliding with dyn.
     */
    void doCollisionResponse(SceneDynamic* dyn, const MazeColliderAABB* aabb);
};

#endif
