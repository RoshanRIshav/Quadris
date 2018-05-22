#ifndef LEVEL_H
#define LEVEL_H
#include <memory>
#include <vector>
#include <cstdlib> 
class Block;
class Board;
class Centerblock;

class Level {
    bool heavy;
    size_t level;
    std::shared_ptr<Board>theBoard;
    std::string fileName;
    size_t cur = 0;
    bool blockPenalty;
    bool random = true;
    std::vector<double> probability;
    std::vector<char> sequence;
    void setFile(); //helper to set the file to sequence    
    void setProbability(); //helper to set probability

    public:
    Level(size_t level, std::shared_ptr<Board> theBoard, std::string fileName = "sequence.txt");
    std::unique_ptr<Block> generateBlock();
    std::unique_ptr<Block> generateCenterBlock();
    void levelUp(); 
    void levelDown();
    size_t getLevel() const;
    double getRand();//returns a value from 0 to 1.0
    void setRand();
    void setNoRand(std::string fileName);
    bool isHeavy() const;
    bool hasblockPenalty() const;
};
#endif
