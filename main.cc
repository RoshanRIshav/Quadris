#include "board.h"
#include "level.h"
#include "block.h"
#include "subject.h"
#include "textDisplay.h"
#include "graphicDisplay.h"
#include "commandInterpreter.h"
#include "helper.h"
#include "exception.h"
#include "centerblock.h"
#include "window.h"
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdexcept>
using namespace std;

int main(int argc, char* argv[]) {
    //setup
    int seed = 1;
    int rows = 18;
    int cols = 11;
    int winSize = 500;

    shared_ptr<TextDisplay> td(new TextDisplay(rows, cols));
    shared_ptr<Board> board(new Board(rows, cols, td,0));
    commandInterpreter ci = commandInterpreter();

    //check whether there was a hint on last command
    bool hint = false;
    shared_ptr<Block> hintb;
    shared_ptr<istream> instream(&cin, [](void *){});
    shared_ptr<istream> stream = instream;

    string filename = "sequence.txt";
    int startLevel = 0;

    //extra feature: read/record a player's personal best
    int personalBest = 0;
    bool personalRecord = false;
    string player;
    string playerFile = player + ".record";
    int currentBest = 0;

    int i = 1; //indices of argv, used for the following while loop
    while (i<argc) {
        string s = argv[i];
        if (s == "-text") {
            board->noGraphics();
            ++i;
        }
        else if (s == "-seed") {
            if (i < argc - 1) {
                stringstream s(argv[i + 1]);
                ++i;
                int temp;
                if (s >> temp) seed = temp;
            }
            ++i;
        }
        else if (s == "-scriptfile") {
            if (i < argc - 1) {
                filename = argv[i + 1];
                ++i;
            }
            ++i;
        }
        else if (s == "-startlevel") {
            if (i < argc - 1) {
                stringstream s(argv[i + 1]);
                int temp;
                ++i;
                if (s >> temp) {
                    startLevel = temp;
                }
            }
            ++i;
        }
        //extra feature: rename a command name
        else if (s == "-rename"){
            if (i < argc - 2) {
                string orig = argv[i+1];
                string newname = argv[i+2];
                ci.rename(orig,newname);
                i+=2;
            }
            ++i;
        }
        //extra feature: read/record a player's personal best
        else if (s == "-myname"){
            if (i < argc - 1) {
                personalRecord = true;
                player = argv[i+1];
                playerFile = player + ".record";
                ifstream ifstr(playerFile);
                ifstr>>personalBest;
                board->setHighScore(personalBest);
                board->setPlayerName(player);
                ++i;
            }
            ++i;
        }
        else { ++i; }
    }
    Level level = Level(startLevel, board, filename);
    board->setLevel(startLevel);
    board->setObserver(td);
    board->attach(td);
    if (board->ifGraphic()) {
        shared_ptr<GraphicsDisplay> gd(new GraphicsDisplay(rows, cols, winSize));
        board->setObserver(gd);
        board->attach(gd);
    }
    srand(seed);
    shared_ptr<Block> curblock = level.generateBlock();
    shared_ptr<Block> nextblock = level.generateBlock();
    curblock->draw();

    board->setNext(nextblock);

    cout << (*board);

    //reading commands
    string s;
    int blocksdropped = 0;

    try {
        while (((*stream) >> s)||
                ((stream != instream)&&(stream = instream)&&((*stream)>>s))) {
            commandType command = ci.parseInput(s);
            int multiplier = ci.getMultiplier(s);

            if (hint == true){ //clear hint block if hint was last command
                hintb->clear();
                hint = false;
            }

            if (board->isOver() && (command != commandType::restart)) continue;
            if (command == commandType::restart) {
                board->clear();
                board->resetScore();
                board->setOver(false);
                board->setLevel(0);
                blocksdropped = 0;
                level = Level(0,board,filename);
                curblock = level.generateBlock();
                nextblock = level.generateBlock();
                curblock->draw();
                board->setNext(nextblock);
                cout << (*board);
            }
            else if ((command == commandType::left) || (command == commandType::right)
                    || (command == commandType::down) || (command == commandType::clockwise)
                    || (command == commandType::counterclockwise)) {
                curblock->clear();
                for(int i=0;i<multiplier;++i){
                    blockMove(curblock, command);
                }
                if(level.isHeavy()) blockMove(curblock, commandType::down);	
                curblock->draw();
                cout << (*board);
            }
            else if (command == commandType::drop) {
                for (int i = 0; i < multiplier; ++i) {
                    curblock->clear();
                    curblock->drop();		
                    board->dropBlock(curblock);
                    curblock->draw();
                    cout<<(*board); //displays the board right after the block is dropped
                    bool ifClear = board->clearRow(level.getLevel());
                    //clear and update scores
                    //ifClear records if any row has been cleared
                    if (ifClear) blocksdropped = 0;
                    if (board->isOver(nextblock)) {	//if the game is over
                        blocksdropped = 0;
                        board->setOver(true);
                        cout << (*board);
                        break;
                    }
                    else {				//if the game is still on
                        if (level.hasblockPenalty()) {
                            //if we're in a level where penalty blocks are generated
                            if (blocksdropped == 4) {
                                curblock = level.generateCenterBlock();
                                curblock->drop();
                                board->dropBlock(curblock);
                                curblock->draw();
                                cout << (*board);
                                board->clearRow(level.getLevel());
                                blocksdropped = 0;
                            }
                            else { ++blocksdropped; }
                        }
                        curblock = nextblock;
                        nextblock = level.generateBlock();
                        board->setNext(nextblock);
                        curblock->draw();
                        cout << (*board); //displays with rows cleared(if any), new block and new next
                    }
                }

                //extra feature
                if (personalRecord) {
                    currentBest = board->getHighScore();
                    if(currentBest > personalBest) {
                        personalBest = currentBest;
                        ofstream ostr(playerFile);
                        ostr<<personalBest<<endl;
                    }
                }
            }
            else if (command == commandType::levelup) {
                for (int i = 0; i < multiplier; ++i) {
                    level.levelUp();
                }
                board->setLevel(level.getLevel());
                cout << (*board);
            }
            else if (command == commandType::leveldown) {
                for (int i = 0; i < multiplier; ++i) {
                    level.levelDown();
                }
                board->setLevel(level.getLevel());
                blocksdropped = 0;
                cout << (*board);
            }
            else if (command == commandType::norandom) {
                string filename;
                (*stream) >> filename;
                ifstream istr(filename);
                if (istr.is_open()) {
                    if (level.isHeavy()) {
                        level.setNoRand(filename);
                    }
                cout<<"File successfully read"<<endl;
                }
                else {cout<<"Invalid Filename"<<endl;}
                istr.close();
            }
            else if (command == commandType::random) {
                if (level.isHeavy()) level.setRand();
            }
            else if ((command == commandType::I) || (command == commandType::J) ||
                    (command == commandType::L) || (command == commandType::O) ||
                    (command == commandType::S) || (command == commandType::Z) ||
                    (command == commandType::T)) {
                try{curblock->clear();
                    curblock = replace(command, level, board);
                    curblock->draw();
                    cout << (*board);
                } catch(exception) {}
            }
            else if (command == commandType::sequence) {
                string filename;
                (*stream) >> filename;
                ifstream istr(filename);
                if (istr.is_open()) {
                stream = make_shared<ifstream>(filename);
                cout<<"File successfully read"<<endl;
                }
                else {cout<<"Invalid Filename"<<endl;}
                istr.close();
            }

            else if (command == commandType::hint) {
                hintb = curblock->findBestPos(curblock);
                hintb->draw();
                curblock->draw();
                cout << (*board);
                hint = true;
            }
            else { //command == commandType::invalid
                continue;
            }
        }
    }
    catch (ios::failure) {} //any I/O failure quits
}







