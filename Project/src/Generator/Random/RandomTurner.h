//
//  RandomTurner.h
//  Dissert
//
//  Created by Olivier Legat on 25/05/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#ifndef DISSERT_RANDOM_TURNER_H_
#define DISSERT_RANDOM_TURNER_H_

#include <platform.h>
#include "Random.h"
#include "DiggerDependant.h"

class Digger;
class MazeCell;

class RandomTurner 
extends Object 
implements RandomI
implements DiggerDependant
{
public:
    
    /**
     * Creates a Random turner with initially no digger.
     * Calling a nextInt() before setting the digger will result
     * in an error.
     * @param randomi Generator used to create ints.
     * @param randomf Generator used to create a random float between 0 to 1.
     * @param leftProb Value used to determine the probability of turning left.
     *        0 < leftThres < 1
     * @param rightProb Value used to determine the probability of turning right.
     *        0 < rightThres < 1
     */
    RandomTurner(RandomI* randomi, RandomF* randomf, float leftProb, float rightProb);
    
    /**
     * Creates a Random turner with initially no digger.
     * @param randomi Generator used to create ints.
     * @param randomf Generator used to create a random float between 0 to 1.
     * @param leftProb Value used to determine the probability of turning left.
     *        0 < leftThres < 1
     * @param rightProb Value used to determine the probability of turning right.
     *        0 < rightThres < 1
     * @param digger Digger used to analyse possible directions.
     */
    RandomTurner(RandomI* randomi, RandomF* random, float leftProb, float rightProb, Digger* digger);
    
    void SetLeftThreshold(float t) {this->leftProb = t;}
    float GetLeftThreshold() {return this->leftProb;}
    
    void SetRightThreshold(float t) {this->rightProb = t;}
    float GetRightThreshold() {return this->rightProb;}
    
    /**
     * Get random direction.
     *
     * If the digger cannot turn:
     *   - Carries on straight:
     *
     * If the digger cannot carry on straight:
     *   - Turns left or right.
     *
     * If the digger can turn or carry on straigth:
     *   - Generates a random float f [0, 1]. 
     *   - If f <= turnThres then the digger will turn (left or right with 50:50 chance).
     *   - If f >  turnThres then the digger will carry on straight.
     */
    virtual int nextInt();
    virtual int nextInt(int max);
    virtual int nextInt(int min, int max);
    
private:
    RandomI* randomi;
    RandomF* randomf;
    
    float rightProb;
    float leftProb;
    
    void GetStraightLeftRight(MazeCell** straight, MazeCell** left, MazeCell** right);
};

#endif
