//
//  Material.h
//  Dissert
//
//  Created by Olivier Legat on 14/05/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#ifndef MATERIAL_H_
#define MATERIAL_H_

#include <platform.h>
#include <Engine/Graphics/Texture/Texture.h>

class Material
extends Object
{
public:
    Material();
    ~Material();
    
    Texture* GetDiffuse() const {return diffuse;}
	void SetDiffuse(Texture* t) {if(diffuse!=NULL) delete diffuse; this->diffuse = t;}
    bool HasDiffuse() const {return diffuse != 0;}
    
    void DeleteTextures();
    
private:
    Texture* diffuse;
};

#endif
