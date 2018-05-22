#include "level.h"
#include "exception.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include "iblock.h"
#include "jblock.h"
#include "lblock.h"
#include "oblock.h"
#include "sblock.h"
#include "zblock.h"
#include "tblock.h"
#include "centerblock.h" 
using namespace std;

Level::Level(size_t level, shared_ptr<Board> theBoard, string fileName): level{level}, theBoard{theBoard}, fileName{fileName}{
    setProbability(); //initialize probabilities
    if (level == 0){
        random = false;
        setFile();
    }

    if (level >= 0 && level <= 3){ //set blockPenalty
        blockPenalty = false;
    } else if (level  == 4){
        blockPenalty = true;
    }

    if (level >= 0 && level < 3){ //set heavy
        heavy = false;
    } else if (level >= 3 && level <= 4){
        heavy = true;
    }
}

void Level::setFile(){
    char s;
    sequence.clear();
    ifstream file{fileName};

    while(file >> s){
        sequence.emplace_back(s);
    }
    cur = 0;
}

unique_ptr<Block> Level::generateCenterBlock(){
    unique_ptr<Block> b = make_unique<Centerblock>(theBoard, heavy, level);
    return b;
}

unique_ptr<Block> Level::generateBlock(){
    unique_ptr<Block> b;

    if (random == false){ //use file
        if (cur >= sequence.size()) cur = 0;
        char s = sequence.at(cur);
        if (s == 'I'){
            b = make_unique<Iblock>(theBoard, heavy, level);
        } else if (s == 'J'){  
            b = make_unique<Jblock>(theBoard, heavy, level);
        } else if (s == 'L'){ 
            b = make_unique<Lblock>(theBoard, heavy, level);
        } else if (s == 'O'){ 
            b = make_unique<Oblock>(theBoard, heavy, level);
        } else if (s == 'S'){ 
            b = make_unique<Sblock>(theBoard, heavy, level);
        } else if (s == 'Z'){ 
            b = make_unique<Zblock>(theBoard, heavy, level);
        } else if (s == 'T'){ 
            b = make_unique<Tblock>(theBoard, heavy, level);
        }
        ++cur;
        return b;

    } else { //use probabilities
        double i = getRand();

        if (i < probability.at(0)){
            b = make_unique<Iblock>(theBoard, heavy, level);
        } else if (i < probability.at(1)){
            b = make_unique<Jblock>(theBoard, heavy, level);
        } else if (i < probability.at(2)){
            b = make_unique<Lblock>(theBoard, heavy, level);
        } else if (i < probability.at(3)){
            b = make_unique<Oblock>(theBoard, heavy, level);
        } else if (i < probability.at(4)){
            b = make_unique<Sblock>(theBoard, heavy, level);
        } else if (i < probability.at(5)){
            b = make_unique<Zblock>(theBoard, heavy, level);
        } else {
            b = make_unique<Tblock>(theBoard, heavy, level);
        }
        return b;
    }
}

void Level::setProbability(){
    if (level == 1){
        probability = {1.0/6.0, 2.0/6.0, 3.0/6.0, 4.0/6.0, 9.0/12.0, 10.0/12.0, 1.0}; //in order of ijloszt
    } else if (level == 2){
        probability = {1.0/7.0, 2.0/7.0, 3.0/7.0, 4.0/7.0, 5.0/7.0, 6.0/7.0, 1.0};
    } else if (level == 3 || level == 4){
        probability = {1.0/9.0, 2.0/9.0, 3.0/9.0, 4.0/9.0, 6.0/9.0, 8.0/9.0, 1.0};
    }
}

void Level::levelUp(){
    if (level + 1 <= 4){
        ++level;
        if (level >= 3){
            heavy = true;
            if(level>=4) {
                blockPenalty=true;
            }
        }
    }
    if (level >= 1 && level <= 4) random = true;
    setProbability();
}

void Level::levelDown(){
    if (level >= 1){
        --level;
        if (level < 4){
            blockPenalty=false;
            if(level<3) {
                heavy = false;
            }
        }
    }
    if (level == 0) {
        random = false;
        setFile();       
    }
   
    setProbability();
}

size_t Level::getLevel() const{
    return level;
}

bool Level::isHeavy() const{
    return heavy;
}

bool Level::hasblockPenalty() const{
    return blockPenalty;
}

double Level::getRand(){
    return (double)rand()/RAND_MAX;
}

void Level::setNoRand(string fileName){
    if (level == 3 || level == 4){
        this->fileName = fileName;
        random = false;
        setFile();  
    }
}

void Level::setRand(){
    if (level == 3 || level == 4){
        random = true;
    }
}
