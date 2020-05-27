//
//  RandomElement.cpp
//  Dissert
//
//  Created by Olivier Legat on 25/05/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#include "Random.h"
#include "RandomElement.h"

RandomElementI::RandomElementI() {
    min = 0;
    max = 0;
    generator = NULL;
}
RandomElementF::RandomElementF() {
    min = 0.0f;
    max = 0.0f;
    generator = NULL;
}


RandomElementI::RandomElementI(int min, int max) {
    this->min = min;
    this->max = max;
    generator = NULL;
}
RandomElementF::RandomElementF(float min, float max) {
    this->min = min;
    this->max = max;
    generator = NULL;
}


RandomElementI::RandomElementI(int min, int max, RandomI* generator) {
    this->min = min;
    this->max = max;
    this->generator = generator;
}
RandomElementF::RandomElementF(float min, float max, RandomF* generator) {
    this->min = min;
    this->max = max;
    this->generator = generator;
}


int   RandomElementI::nextInt()   { return generator->nextInt  (min, max); }
float RandomElementF::nextFloat() { return generator->nextFloat(min, max); }
