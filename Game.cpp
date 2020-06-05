#include "Game.h"

Game::Game()
{
    // Constructor
}

Game::~Game()
{
    // Deconstructor
}

void Game::newGame()
{
    // CONSTRUCTOR OBJECTS FOR GAME
    players = new Player();
    cout << "Starting a New Game" << endl << endl;
    players->createPlayers();

    boxLid = new BoxLid();
    factory = new Factory();
    centreFactory = new CentreFactory();    

    while(!players->players[0]->getWall()->rowFilled() || !players->players[1]->getWall()->rowFilled())
    {
        aRound();
    }

    // ADDING BONUS POINTS AFTER GAME COMPLETION
    for(int i = 0; i < 2; i++)
    {
        players->players[i]->addPoints(players->players[i]->getWall()->horizontalBonusPoints());
        players->players[i]->addPoints(players->players[i]->getWall()->verticalBonusPoints());
        players->players[i]->addPoints(players->players[i]->getWall()->sameColourbonusPoints());
    }

    cout << "=== GAME OVER ===" << endl << endl;

    // DISPLAYING WINNER
    cout << players->isWinning(players->players[0], players->players[1]) << endl << endl;

    deleteGame();
}

void Game::playerTurn(Player* player)
{
    // PRINT PLAYER TURN NAME
    cout << "TURN FOR PLAYER: " << print_as_color<ansi_color_code::bright_green>(player->getName()) << endl;

    // DISPLAY FACTORIES
    cout << "Factories:" << endl;
    centreFactory->displayCentreFactory();
    factory->displayFactories();
    cout << endl;

    // DISPLAY MOSAIC
    int otherPlayer = (playerIterator + 1) % 2;
    cout << "Mosaic for " << print_as_color<ansi_color_code::bright_green>(player->getName()) << ":" << "                ";
    cout << "Mosaic for opponent " << print_as_color<ansi_color_code::red>(players->players[otherPlayer]->getName()) << ":" << endl;
    displayMosaic(player);
    cout << endl;

    if(isTurnValid(player))
    {   
        // BREAKING TILE FROM CENTRE FACTORY
        if(factoryNumber == 0 && breakAction == 'B')
        {
            char* breakActionPtr = nullptr;
            breakActionPtr = &breakAction;
            
            // LOOP THROUGH CENTRE FACTORY
            for(int outterLoop = 0; outterLoop < CENTRE_FACTORY_MAX_SIZE; outterLoop++)
            {
                bool actionTaken = false;

                // IF FIRST PLAYER TOKEN AVAILABLE INSERT IN FLOOR LINE
                if(centreFactory->centreFactory[0] != nullptr)
                {
                    if(centreFactory->centreFactory[0]->getTile() == 'F')
                    {
                        for(int floorLineInnerLoop = 0; floorLineInnerLoop < FLOOR_LINE_LENGTH; floorLineInnerLoop++)
                        {
                            if(player->getFloorLine()->deductions[floorLineInnerLoop] == nullptr && !actionTaken)
                            {
                                // INSERT FIRST PLAYER TOKEN INTO FLOOR LINE
                                player->getFloorLine()->deductions[floorLineInnerLoop] = centreFactory->centreFactory[0];
                                
                                // DISPLAY FIRST PLAYER TOKEN HAS BEEN TAKEN
                                cout << "(gets first player token)" << endl;
                                
                                // DELETE TILE FROM CENTRE FACTORY
                                centreFactory->centreFactory[0] = nullptr;
                                actionTaken = true;
                            }
                        }
                    }
                }

                actionTaken = false;
                
                // VALDIATING CENTRE FACTORY POSITION IS NOT NULL
                if(centreFactory->centreFactory[outterLoop] != nullptr)
                {
                    // FIND CORRECT TILE COLOUR AND PLACE IN FLOOR LINE
                    if(centreFactory->centreFactory[outterLoop]->getTile() == tileColour)
                    {
                        // LOOP THROUGH FLOOR LINE
                        for(int floorLineInnerLoop = 0; floorLineInnerLoop < FLOOR_LINE_LENGTH; floorLineInnerLoop++)
                        {
                            // ENSURE FLOOR LINE NOT FULL
                            if(!player->getFloorLine()->isFloorLineFull())
                            {
                                // ENSURE CURRENT POSITION IS NULL
                                if(player->getFloorLine()->deductions[floorLineInnerLoop] == nullptr && !actionTaken)
                                {
                                    // INSERT THE TILE
                                    player->getFloorLine()->deductions[floorLineInnerLoop] = centreFactory->centreFactory[outterLoop];

                                    // DELETE TILE FROM CENTRE FACTORY
                                    centreFactory->centreFactory[outterLoop] = nullptr;
                                    actionTaken = true;
                                }
                            }

                            // IF FLOOR LINE FULL PLACE IN BOX LID
                            else if(actionTaken == false)
                            {
                                // INSERT TILE IN BOX LID
                                boxLid->addTileBack(centreFactory->centreFactory[outterLoop]);

                                // DELETE TILE FROM CENTRE FACTORY
                                centreFactory->centreFactory[outterLoop] = nullptr;
                                actionTaken = true;
                            }
                        }
                        
                    }
                }
            }

            *breakActionPtr = ' ';
        }

        // BREAKING TILE FROM FACTORY
        else if((factoryNumber >= 1 && factoryNumber <= 5) && breakAction == 'B')
        {
            char* breakActionPtr = nullptr;
            breakActionPtr = &breakAction;
            
            // LOOP THROUGH FACTORY
            for(int outterLoop = 0; outterLoop < FACTORY_SIZE; outterLoop++)
            {
                bool actionTaken = false;
                
                // FIND CORRECT COLOUR
                if(factory->factories[factoryNumber - 1][outterLoop]->getTile() == tileColour)
                {
                    // IF FLOOR LINE NOT FULL PLACE TILE IN FLOOR LINE
                    for(int floorLineInnerLoop = 0; floorLineInnerLoop < FLOOR_LINE_LENGTH; floorLineInnerLoop++)
                    {
                        // ENSURE FLOOR LINE NOT FULL
                        if(!player->getFloorLine()->isFloorLineFull())
                        {
                            // ENSURE CURRENT POSITION IS NULL
                            if(player->getFloorLine()->deductions[floorLineInnerLoop] == nullptr && !actionTaken)
                            {
                                // INSERT THE TILE
                                player->getFloorLine()->deductions[floorLineInnerLoop] = factory->factories[factoryNumber - 1][outterLoop];
                                actionTaken = true;
                            }
                        }

                        // IF FLOOR LINE FULL PLACE IN BOX LID
                        else if(actionTaken == false)
                        {
                            // INSERT TILE IN BOX LID
                            boxLid->addTileBack(factory->factories[factoryNumber - 1][outterLoop]);

                            // DELETE TILE FROM CENTRE FACTORY
                            factory->factories[factoryNumber - 1][outterLoop] = nullptr;
                            
                            actionTaken = true;
                        }
                    }
                    
                }

                // IF NOT CORRECT COLOUR PLACE IN CENTRE FACTORY
                else
                {
                    for(int centreFactoryInnerLoop = 0; centreFactoryInnerLoop < CENTRE_FACTORY_MAX_SIZE; centreFactoryInnerLoop++)
                    {
                        if(centreFactory->centreFactory[centreFactoryInnerLoop] == nullptr && !actionTaken)
                        {
                            centreFactory->centreFactory[centreFactoryInnerLoop] = factory->factories[factoryNumber - 1][outterLoop];
                            actionTaken = true;
                        }
                    }
                }    
            }

            // EMPTY FACTORY
            factory->emptyAFactory(factoryNumber);

            *breakActionPtr = ' ';
        }

        // TAKING TILE(S) FROM CENTRE FACTORY
        else if(factoryNumber == 0)
        {
            // LOOP THROUGH CENTRE FACTORY
            for(int outterLoop = 0; outterLoop < CENTRE_FACTORY_MAX_SIZE; outterLoop++)
            {
                bool actionTaken = false;

                // IF FIRST PLAYER TOKEN AVAILABLE INSERT IN FLOOR LINE
                if(centreFactory->centreFactory[0] != nullptr)
                {
                    if(centreFactory->centreFactory[0]->getTile() == 'F')
                    {
                        for(int floorLineInnerLoop = 0; floorLineInnerLoop < FLOOR_LINE_LENGTH; floorLineInnerLoop++)
                        {
                            if(player->getFloorLine()->deductions[floorLineInnerLoop] == nullptr && !actionTaken)
                            {
                                // INSERT FIRST PLAYER TOKEN INTO FLOOR LINE
                                player->getFloorLine()->deductions[floorLineInnerLoop] = centreFactory->centreFactory[0];
                                
                                // DISPLAY FIRST PLAYER TOKEN HAS BEEN TAKEN
                                cout << "(gets first player token)" << endl;
                                
                                // DELETE TILE FROM CENTRE FACTORY
                                centreFactory->centreFactory[0] = nullptr;
                                actionTaken = true;
                            }
                        }
                    }
                }

                actionTaken = false;
                
                // VALDIATING CENTRE FACTORY POSITION IS NOT NULL
                if(centreFactory->centreFactory[outterLoop] != nullptr)
                {
                    // FIND CORRECT TILE COLOUR AND PLACE IN PATTERN LINE
                    if(centreFactory->centreFactory[outterLoop]->getTile() == tileColour)
                    {
                        // ENSURE PATTERN LINE NOT FULL
                        if(!player->getPatternLines()->isPatternLineFull(player->getPatternLines()->getPatternLine(patternLineNumber)))
                        {
                            // LOOP THROUGH PATTERN LINE
                            for(int patternLineInnerLoop = 0; patternLineInnerLoop < player->getPatternLines()->getSize(player->getPatternLines()->getPatternLine(patternLineNumber)); patternLineInnerLoop++)
                            {
                                // FIND NULL POSITION
                                if(player->getPatternLines()->getPatternLine(patternLineNumber)[patternLineInnerLoop] == nullptr && !actionTaken)
                                {
                                    // INSERT CENTRE FACTORY TILE INTO PATTERN LINE TILE
                                    player->getPatternLines()->getPatternLine(patternLineNumber)[patternLineInnerLoop] = centreFactory->centreFactory[outterLoop];
                                    
                                    // DELETE TILE FROM CENTRE FACTORY
                                    centreFactory->centreFactory[outterLoop] = nullptr;
                                    actionTaken = true;
                                }
                            }
                        }

                        // TRY AND PLACE IN FLOOR LINE
                        else
                        {
                            // LOOP THROUGH FLOOR LINE
                            for(int floorLineInnerLoop = 0; floorLineInnerLoop < FLOOR_LINE_LENGTH; floorLineInnerLoop++)
                            {
                                // ENSURE FLOOR LINE NOT FULL
                                if(!player->getFloorLine()->isFloorLineFull())
                                {
                                    // ENSURE CURRENT POSITION IS NULL
                                    if(player->getFloorLine()->deductions[floorLineInnerLoop] == nullptr && !actionTaken)
                                    {
                                        // INSERT THE TILE
                                        player->getFloorLine()->deductions[floorLineInnerLoop] = centreFactory->centreFactory[outterLoop];

                                        // DELETE TILE FROM CENTRE FACTORY
                                        centreFactory->centreFactory[outterLoop] = nullptr;
                                        actionTaken = true;
                                    }
                                }

                                // IF FLOOR LINE FULL PLACE IN BOX LID
                                else if(actionTaken == false)
                                {
                                    // INSERT TILE IN BOX LID
                                    boxLid->addTileBack(centreFactory->centreFactory[outterLoop]);

                                    // DELETE TILE FROM CENTRE FACTORY
                                    centreFactory->centreFactory[outterLoop] = nullptr;

                                    actionTaken = true;
                                }
                            }
                        }
                    }
                }
            }
        }
        
        // TAKING TILE(S) FROM FACTORIES
        else if(factoryNumber >= 1 && factoryNumber <= 5)
        {
            // LOOP THROUGH FACTORY
            for(int outterLoop = 0; outterLoop < FACTORY_SIZE; outterLoop++)
            {
                bool actionTaken = false;
                
                // FIND CORRECT COLOUR
                if(factory->factories[factoryNumber - 1][outterLoop]->getTile() == tileColour)
                {
                    // ENSURE PATTERN LINE NOT FULL
                    if(!player->getPatternLines()->isPatternLineFull(player->getPatternLines()->getPatternLine(patternLineNumber)))
                    {
                        // LOOP THROUGH PATTERN LINE
                        for(int patternLineInnerLoop = 0; patternLineInnerLoop < player->getPatternLines()->getSize(player->getPatternLines()->getPatternLine(patternLineNumber)); patternLineInnerLoop++)
                        {
                            // FIND NULL POSITION
                            if(player->getPatternLines()->getPatternLine(patternLineNumber)[patternLineInnerLoop] == nullptr && !actionTaken)
                            {
                                // INSERT FACTORY TILE INTO PATTERN LINE TILE
                                player->getPatternLines()->getPatternLine(patternLineNumber)[patternLineInnerLoop] = factory->factories[factoryNumber - 1][outterLoop];
                                actionTaken = true;
                            }
                        }
                    }

                    // ELSE LOOP THROUGH FLOOR LINE AND PLACE THERE
                    else
                    {
                        // IF FLOOR LINE NOT FULL PLACE TILE IN FLOOR LINE
                        for(int floorLineInnerLoop = 0; floorLineInnerLoop < FLOOR_LINE_LENGTH; floorLineInnerLoop++)
                        {
                            // ENSURE FLOOR LINE NOT FULL
                            if(!player->getFloorLine()->isFloorLineFull())
                            {
                                // ENSURE CURRENT POSITION IS NULL
                                if(player->getFloorLine()->deductions[floorLineInnerLoop] == nullptr && !actionTaken)
                                {
                                    // INSERT THE TILE
                                    player->getFloorLine()->deductions[floorLineInnerLoop] = factory->factories[factoryNumber - 1][outterLoop];
                                    actionTaken = true;
                                }
                            }

                            // IF FLOOR LINE FULL PLACE IN BOX LID
                            else if(actionTaken == false)
                            {
                                // INSERT TILE IN BOX LID
                                boxLid->addTileBack(factory->factories[factoryNumber - 1][outterLoop]);

                                // DELETE TILE FROM CENTRE FACTORY
                                factory->factories[factoryNumber - 1][outterLoop] = nullptr;

                                actionTaken = true;
                            }
                        }
                    }
                }
                // IF NOT CORRECT COLOUR PLACE IN CENTRE FACTORY
                else
                {
                    for(int centreFactoryInnerLoop = 0; centreFactoryInnerLoop < CENTRE_FACTORY_MAX_SIZE; centreFactoryInnerLoop++)
                    {
                        if(centreFactory->centreFactory[centreFactoryInnerLoop] == nullptr && !actionTaken)
                        {
                            centreFactory->centreFactory[centreFactoryInnerLoop] = factory->factories[factoryNumber - 1][outterLoop];
                            actionTaken = true;
                        }
                    }
                }    
            }

            // EMPTY FACTORY
            factory->emptyAFactory(factoryNumber);
        }
        
        cout << "Turn successful" << endl << endl;
    }
           
}

bool Game::isTurnValid(Player* player)
{
    bool turnValidated = false;
    
    if(getTurn())
    {
        if(action.compare("SAVE") == 0)
        {
            saveGame(fileName);
            cout << "Game successfully save to '" + fileName + "'" << endl << endl;
            isTurnValid(player);
            turnValidated = true;
        }
        else if(action.compare("help") == 0 || action.compare("Help") == 0 || action.compare("HELP")==0)
        {
            cout << "Here are all the possible commands:" << endl;
            if(!centreFactory->isCentreFactoryEmpty())
                {
                    cout << "Centre Factory: ";
                    cout << print_as_color<ansi_color_code::bright_green>("turn <0> <colour> <storage row>") << endl;
                }
            if(!factory->areFactoriesEmpty())
                 {
                    cout << "Factories     : ";
                    cout << print_as_color<ansi_color_code::bright_green>("turn <factory number> <colour> <storage row>") << endl;
                }
                
                cout << "Save Game     : ";
                cout << print_as_color<ansi_color_code::bright_green>("save <file name>") << endl;
                cout << "Break Tile    : ";
                cout << print_as_color<ansi_color_code::bright_green>("turn <factory number> <colour> <b>") << endl;
                isTurnValid(player);
                turnValidated = true;
        }

        else if(action.compare("TURN") == 0)
        {
            
            // VALIDATING CENTRE FACTORY BREAK
            if(factoryNumber == 0 && breakAction == 'B')
            {
                // VALIDATING CENTRE FACTORY IS NOT EMPTY
                if(!centreFactory->isCentreFactoryEmpty())
                {
                    bool actionValidated = false;
                    
                    for(int centreFactoryIndex = 0; centreFactoryIndex < CENTRE_FACTORY_MAX_SIZE; centreFactoryIndex++)
                    {
                        // VALIDATING CENTRE FACTORY CONTAINS CORRECT TILE COLOUR
                        if(centreFactory->centreFactoryContainsTile(tileColour))
                        {
                            turnValidated = true;

                            actionValidated = true;
                        }
                        else if(actionValidated == false)
                        {
                            actionValidated = true;
                            
                            cout << "Invalid Input: (Centre Factory does not contain this colour)" << endl;
                            isTurnValid(player);
                            turnValidated = true;
                        }
                    }
                }
                else
                {
                    cout << "Invalid Input: (Centre Factory is empty)" << endl;
                    isTurnValid(player);
                    turnValidated = true;
                }
            }

            // VALIDATING FACTORY BREAK
            else if((factoryNumber >= 1 && factoryNumber <= 5) && breakAction == 'B')
            {
                // VALIDATING FACTORY IS NOT EMPTY
                if(!factory->isFactoryEmpty(factoryNumber))
                {
                    bool actionValidated = false;
                    
                    for(int factoryIndex = 0; factoryIndex < FACTORY_SIZE; factoryIndex++)
                    {
                        // VALIDATING FACTORY CONTAINS TILE COLOUR
                        if(factory->factoryContainsTile(factoryNumber, tileColour))
                        {
                            turnValidated = true;

                            actionValidated = true;
                        }
                        else if(actionValidated == false)
                        {
                            actionValidated = true;

                            cout << "Invalid Input: (Factory does not contain this colour)" << endl;
                            isTurnValid(player);
                            turnValidated = true;
                        }
                    }
                }
                else
                {
                    cout << "Invalid Input: (Factory is empty)" << endl;
                    isTurnValid(player);
                    turnValidated = true;
                }
            }
            
            // VALIDATING CENTRE FACTORY NUMBER AND PATTERN LINE NUMBER ARE IN RANGE
            else if(factoryNumber == 0 && (patternLineNumber >= 1 && patternLineNumber <= 5))
            {
                // VALIDATING CENTRE FACTORY IS NOT EMPTY
                if(!centreFactory->isCentreFactoryEmpty())
                {
                    bool actionValidated = false;
                    
                    for(int centreFactoryIndex = 0; centreFactoryIndex < CENTRE_FACTORY_MAX_SIZE; centreFactoryIndex++)
                    {
                        
                        // VALIDATING CENTRE FACTORY CONTAINS CORRECT TILE COLOUR
                        if(centreFactory->centreFactoryContainsTile(tileColour))
                        {
                            if(patternLineNumber >= 1 && patternLineNumber <= 5)
                            {
                                // TURN VALID IS CENTRE FACTORY CONTAIN TILE COLOUR && PATTERN LINE IS EMPTY OR NOT FULL AND TILE COLOUR MATCHES
                                if(player->getPatternLines()->isPatternLineEmpty(player->getPatternLines()->getPatternLine(patternLineNumber)) || 
                                (!player->getPatternLines()->isPatternLineFull(player->getPatternLines()->getPatternLine(patternLineNumber)) && 
                                player->getPatternLines()->patternLineTileColour(player->getPatternLines()->getPatternLine(patternLineNumber)) == tileColour))
                                {
                                    // FIND WALL LOCATION FOR TILE
                                    int wallColumn = player->getWall()->getWallPositionForTileColour(patternLineNumber, tileColour);
                                    
                                    // IF WALL POSITION NOT ALREADY FILLED
                                    if(player->getWall()->tile[patternLineNumber - 1][wallColumn] == nullptr)
                                    {
                                        turnValidated = true;

                                        actionValidated = true;
                                    }
                                    
                                    else if(actionValidated == false)
                                    {
                                        actionValidated = true;
                                        
                                        cout << "Invalid Input: (Tile colour already on wall for this pattern line)" << endl;
                                        isTurnValid(player);
                                        turnValidated = true;
                                    }
                                }
                                else if(actionValidated == false)
                                {
                                    actionValidated = true;

                                    cout << "Invalid Input: (Pattern line full or tile colour does not match)" << endl;
                                    isTurnValid(player);
                                    turnValidated = true;
                                }
                            }
                            else if(actionValidated == false)
                            {
                                actionValidated = true;
                                
                                cout << "Invalid Input: (Pattern line number does not exist)" << endl;
                                isTurnValid(player);
                                turnValidated = true;
                            }
                        }
                        else if(actionValidated == false)
                        {
                            actionValidated = true;
                            
                            cout << "Invalid Input: (Centre Factory does not contain this colour)" << endl;
                            isTurnValid(player);
                            turnValidated = true;
                        }
                    }
                }
                else
                {
                    cout << "Invalid Input: (Centre Factory is empty)" << endl;
                    isTurnValid(player);
                    turnValidated = true;
                }
            }

            // VALIDATING FACTORY NUMBER AND PATTERN LINE NUMBER ARE IN RANGE
            else if((factoryNumber >= 1 && factoryNumber <= 5) && (patternLineNumber >= 1 && patternLineNumber <= 5))
            {
                // VALIDATING FACTORY IS NOT EMPTY
                if(!factory->isFactoryEmpty(factoryNumber))
                {
                    bool actionValidated = false;

                    for(int factoryIndex = 0; factoryIndex < FACTORY_SIZE; factoryIndex++)
                    {
                        
                        // VALIDATING FACTORY CONTAINS TILE COLOUR
                        if(factory->factoryContainsTile(factoryNumber, tileColour))
                        {
                            if(patternLineNumber >= 1 && patternLineNumber <= 5)
                            {
                                // PATTERN LINE IS EMPTY OR NOT FULL AND TILE COLOUR MATCHES
                                if(player->getPatternLines()->isPatternLineEmpty(player->getPatternLines()->getPatternLine(patternLineNumber)) || 
                                (!player->getPatternLines()->isPatternLineFull(player->getPatternLines()->getPatternLine(patternLineNumber)) && 
                                player->getPatternLines()->patternLineTileColour(player->getPatternLines()->getPatternLine(patternLineNumber)) == tileColour))
                                {
                                    // FIND WALL LOCATION FOR TILE
                                    int wallColumn = player->getWall()->getWallPositionForTileColour(patternLineNumber, tileColour);
                                    
                                    // IF WALL POSITION NOT ALREADY FILLED
                                    if(player->getWall()->tile[patternLineNumber - 1][wallColumn] == nullptr)
                                    {
                                        turnValidated = true;
                                    }
                                    
                                    else if(actionValidated == false)
                                    {
                                        actionValidated = true;
                                        
                                        cout << "Invalid Input: (Tile colour already on wall for this pattern line)" << endl;
                                        isTurnValid(player);
                                        turnValidated = true;
                                    }
                                }
                                else if(actionValidated == false)
                                {
                                    actionValidated = true;
                                    
                                    cout << "Invalid Input: (Pattern line full or tile colour does not match)" << endl;
                                    isTurnValid(player);
                                    turnValidated = true;
                                }
                            }
                            else if(actionValidated == false)
                            {
                                actionValidated = true;
                                
                                cout << "Invalid Input: (Pattern line doesn't exist)" << endl;
                                isTurnValid(player);
                                turnValidated = true;
                            }
                            
                        }
                        else if(actionValidated == false)
                        {
                            actionValidated = true;
                            
                            cout << "Invalid Input: (Factory does not contain this colour)" << endl;
                            isTurnValid(player);
                            turnValidated = true;
                        }
                    }
                }
                else
                {
                    cout << "Invalid Input: (Factory is empty)" << endl;
                    isTurnValid(player);
                    turnValidated = true;
                }
            }

            // DISPLAY ERROR MESSAGE FOR INCORRECT TURNS
            else
            {
                cout << "Invalid Input: (Breach of valid inputs)" << endl << endl << 
                "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl <<
                "A Turn = \"turn <factory> <colour> <storage row>\"" << endl << 
                "~~~~~~~~~~~~~~~~~~~~~~~ or ~~~~~~~~~~~~~~~~~~~~~~" << endl << 
                "     A Break = \"turn <factory> <colour> <b>\"   " << endl <<
                "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;

                isTurnValid(player);
                turnValidated = true;
            }
        }
    }

    return turnValidated;
}

bool Game::getTurn()
{
    bool turnGot = false;
    
    // POINTERS FOR VALUES
    string* actionPtr = nullptr;
    string* fileNamePtr = nullptr;
    int* factoryNumberPtr = nullptr;
    int* patternLineNumberPtr = nullptr;
    char* tileColourPtr = nullptr;
    char* breakActionPtr = nullptr;

    // POINTER REFERENCE
    actionPtr = &action;
    fileNamePtr = &fileName;
    factoryNumberPtr = &factoryNumber;
    tileColourPtr = &tileColour;
    breakActionPtr = & breakAction;
    patternLineNumberPtr = &patternLineNumber;
    
    // VECTOR AND STRING CREATION
    vector<string> vect;
    string s = "";

    // USER INPUT
    cout << "> ";

    getline(cin, s);
    cout << endl;
    
    // CHECK FOR EXIT CALL
    if(s.compare("^D") == 0)
    {
        cout << "Goodbye!" << endl;
        exit(1);
    }

    if(s.compare("help") == 0 || s.compare("Help") == 0 || s.compare("HELP") == 0)
    {
        *actionPtr = s;
        turnGot = true;
    }
    if(!turnGot){
    // BREAK INPUT INTO PARTS
    string word = ""; 
    for (auto x : s) 
    { 

        if (x == ' ') 
        { 
            vect.push_back(word);
            word = "";
        } 
        else
        { 
            word = word + x; 
        } 
    }  
    
    // ADDING FINAL CHARACTER/STRING TO VECT
    // UPPER CASE TURN ACTION AND TILE COLOUR FOR CONSISTENCY
    if(vect.size() == 3)
    {
        char finalWord = s.back();
        string d(1, finalWord);
        vect.push_back(d);
        
        if(isalpha(vect[0].front()))
        {
            for_each(vect[0].begin(), vect[0].end(), [](char & c)
            {
                c = ::toupper(c);
            });
        }
            
        if(isalpha(vect[2].front()))
        {
            for_each(vect[2].begin(), vect[2].end(), [](char & c)
            {
                c = ::toupper(c);
            });
        }

        if(isalpha(vect[3].front()))
        {
            for_each(vect[3].begin(), vect[3].end(), [](char & c)
            {
                c = ::toupper(c);
            });
        }
    }

    else if(vect.size() == 1)
    {
        vect.push_back(word);
        
        if(isalpha(vect[0].front()))
        {
            for_each(vect[0].begin(), vect[0].end(), [](char & c)
            {
                c = ::toupper(c);
            });
        }
    }

    // ENSURE CORRECT NUMBER OF RESPONSES
    // TODO: POSSIBLE MORE CONSTRAINTS
    if((vect.size() == 4 && vect[0].compare("TURN") == 0 && isdigit(vect[1][0]) && isalpha(vect[2].front()) && (isdigit(vect[3][0]) || vect[3].compare("B") == 0 )) || (vect.size() == 2 && vect[0].compare("SAVE") == 0))
    {
        // INPUTTING TURN VALUES
        if(vect.size() == 4)
        {
            for(int i = 0; i < 4; i ++)
            {
                if(i == 0)
                {
                    *actionPtr = vect[i];
                }
                else if(i == 1)
                {
                    istringstream iss (vect[i]);
                    iss >> *factoryNumberPtr;
                }
                else if(i == 2)
                {
                    *tileColourPtr = vect[i].front();
                } 
                else if(i == 3)
                {
                    if(isdigit(vect[3][0]))
                    {
                        istringstream iss (vect[i]);
                        iss >> *patternLineNumberPtr;
                    }
                    else
                    {
                        *breakActionPtr = vect[i].front();
                    }
                }
            } 
        }
            turnGot = true;
        }

        // INPUTTING SAVE GAME VALUES 
        else if(vect.size() == 2)
        {
            for(int i = 0; i < 2; i++)
            {
                if(i == 0)
                {
                    *actionPtr = vect[i];
                }
                else
                {
                    *fileNamePtr = vect[1];
                }
            }
            
            turnGot = true;
        }
        else if(vect.size() == 1 && vect[0].compare("DISPLAY") == 0)
        {
            *actionPtr = vect[0];
            turnGot = true;
        }
        else if(vect.size() == 1 && vect[0].compare("HELP") == 0)
        {
            *actionPtr = vect[0];
            turnGot = true;
        }

        // DISPLAY ERROR MESSAGE FOR INCORRECT TURN
        else

        {
            cout << "Invalid Input: (Breach of valid inputs)" << endl << endl << 
            "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl <<
            "A Turn = \"turn <factory> <colour> <storage row>\"" << endl << 
            "~~~~~~~~~~~~~~~~~~~~~~~ or ~~~~~~~~~~~~~~~~~~~~~~" << endl << 
            "     A Break = \"turn <factory> <colour> <b>\"   " << endl <<
            "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;

            getTurn();
            turnGot = true;
        }
    }
    return turnGot;
}

void Game::aRound()
{
    if(centreFactory->isCentreFactoryEmpty() && factory->areFactoriesEmpty())
    {
        centreFactory->refreshCentreFactory();
        factory->refillFactories();
    }

    int* playerIteratorPtr = nullptr;
    playerIteratorPtr = &playerIterator;
    
    cout << "=== Start Round ===" << endl;

    while(!factory->areFactoriesEmpty() || !centreFactory->isCentreFactoryEmpty())
    {
        playerTurn(players->players[playerIterator % 2]);
        *playerIteratorPtr = *playerIteratorPtr + 1; 
    }

    // ADDS POINTS & DEDUCTIONS FOR ROUND
    // CHECKS WHO HAS THE FIRST PLAYER TILE 
    // REFRESHES FLOORLINE & CENTRE FACTORY FOR NEXT ROUND
    for(int i = 0; i < 2; i++)
    {
        movePatternLinesToWall(players->players[i]);
        
        players->players[i]->subtractPoints(players->players[i]->getFloorLine()->totalDeductionPoints());
        
        if(players->players[i]->getFloorLine()->hasFirstPlayerToken())
        {
            *playerIteratorPtr = i;
        }

        // REFRESHING FLOORLINE AND ADDING TO TILEBAG
        for(int innerLoop = 0; innerLoop < FLOOR_LINE_LENGTH; innerLoop++)
        {
            if(players->players[i]->getFloorLine()->deductions[innerLoop] != nullptr)
            {
                if(players->players[i]->getFloorLine()->deductions[innerLoop]->getTile() != 'F')
                {
                    boxLid->addTileBack(players->players[i]->getFloorLine()->deductions[innerLoop]);
                }
            }

            players->players[i]->getFloorLine()->deductions[innerLoop] = nullptr;
        } 

    }

    cout << "=== END OF ROUND ===" << endl << endl;

    // DISPLAY POINTS AT END ON THE ROUND
    cout << "~~ Current Points ~~" << endl;
    for(int i = 0; i < 2; i++)
    {
        cout << players->players[i]->getName() << ": " <<players->players[i]->getPoints() << endl;
    }
    cout << "~~~~~~~~~~~~~~~~~~~~" << endl << endl;
}

void Game::displayMosaic(Player* player)
{
    //get opponents number in players array
    int otherPlayer = (playerIterator + 1) % 2;
    for(int outterLoop = 0; outterLoop < 5; outterLoop++)
    {
        // Displaying pattern line number
        cout << (outterLoop + 1);
        cout << ": ";
        
        // Placing extra dots 
        for(int extraSpaces = (4 - outterLoop); extraSpaces > 0; extraSpaces--)
        {
            cout << "  ";
        }

        // Display Pattern Line
        for(int patternLineInnerLoop = 0; patternLineInnerLoop <= outterLoop; patternLineInnerLoop++)
        {
            if(player->getPatternLines()->getPatternLine(outterLoop + 1)[outterLoop - patternLineInnerLoop] != nullptr)
            {
                cout << printTile(player->getPatternLines()->getPatternLine(outterLoop + 1)[outterLoop - patternLineInnerLoop]->getTile()) << " ";
            }
            else
            {
                cout << "\u25A2 ";
            }
        }
        
        // Pattern Line and Wall Separation
        cout << "\u2192 ";
        
        // Display Wall
        for(int wallInnerLoop = 0; wallInnerLoop < WALL_COLUMNS; wallInnerLoop ++)
        {
            if(player->getWall()->tile[outterLoop][wallInnerLoop] != nullptr)
            {
                cout << " " << printTile(player->getWall()->tile[outterLoop][wallInnerLoop]->getTile());
            }
            else
            {
                cout << " " << printTile(player->getWall()->getTileColourForWallPosition(outterLoop + 1, wallInnerLoop));
            }
        }
        //display opponent game stat
        cout << "    \u254F    ";
        //display pattern line
        // Displaying pattern line number
        cout << (outterLoop + 1);
        cout << ": ";
        
        // Placing extra dots 
        for(int extraSpaces = (4 - outterLoop); extraSpaces > 0; extraSpaces--)
        {
            cout << "  ";
        }

        // Display Pattern Line
        for(int patternLineInnerLoop = 0; patternLineInnerLoop <= outterLoop; patternLineInnerLoop++)
        {
            if(players->players[otherPlayer]->getPatternLines()->getPatternLine(outterLoop + 1)[outterLoop - patternLineInnerLoop] != nullptr)
            {
                cout << printTile(players->players[otherPlayer]->getPatternLines()->getPatternLine(outterLoop + 1)[outterLoop - patternLineInnerLoop]->getTile()) << " ";
            }
            else
            {
                cout << "\u25A2 ";
            }
        }
        
        // Pattern Line and Wall Separation
        cout << "\u2192 ";

        // display mosaic
        for(int wallInnerLoop = 0; wallInnerLoop < WALL_COLUMNS; wallInnerLoop++)
            {
                if(players->players[otherPlayer]->getWall()->tile[outterLoop][wallInnerLoop] != nullptr)
                {
                    cout << " " << printTile(players->players[otherPlayer]->getWall()->tile[outterLoop][wallInnerLoop]->getTile());
                }
                else
                {
                    cout << " " << printTile(players->players[otherPlayer]->getWall()->getTileColourForWallPosition(outterLoop + 1, wallInnerLoop));
                }
                
            }
        cout << endl;
    }

    cout << "broken: ";
    player->getFloorLine()->displayFloorLine();
    cout << "       \u254F    ";
    cout << "broken: ";
    players->players[otherPlayer]->getFloorLine()->displayFloorLine();
}

void Game::moveTileToWall(Player* player, int lineNumber)
{
    // CHECK THAT PATTERN LINE IS FULL
    if(player->getPatternLines()->isPatternLineFull(player->getPatternLines()->getPatternLine(lineNumber)))
    {
        // ALLOCATE COLOUR OF TILE TRYING TO FILL ON WALL 
        char colourOfTile = player->getPatternLines()->getPatternLine(lineNumber)[0]->getTile();

        // ALLOCATE CORRESPONDING POSITION ON WALL IN REFERENCE TO COLOUR AND PATTERN LINE
        int wallLinePosition = player->getWall()->getWallPositionForTileColour(lineNumber, colourOfTile);

        // IF WALL POSITION NULL
        if(player->getWall()->tile[lineNumber - 1][wallLinePosition] ==  nullptr)
        {
            // INSERT INTO WALL
            player->getWall()->tile[lineNumber - 1][wallLinePosition] = player->getPatternLines()->getPatternLine(lineNumber)[0];

            // ADD POINTS CORRESPONDING TO TURN AND POSITION OF TILE
            player->addPoints(player->getWall()->pointsToAdd(lineNumber, wallLinePosition));

            // ADD REST ON BOX TILE
            int loopSize = player->getPatternLines()->getSize(player->getPatternLines()->getPatternLine(lineNumber));
            for(int i = 1; i < loopSize; i++)
            {
                boxLid->addTileBack(player->getPatternLines()->getPatternLine(lineNumber)[i]);
            }            
        }
        
        // IF WALL POSITION FILLED ADD ALL TILES TO TILE BAG
        else
        {
            // ADD ALL TILES TO BOX LID
            int loopSize = player->getPatternLines()->getSize(player->getPatternLines()->getPatternLine(lineNumber));

            for(int i = 0; i < loopSize; i++)
            {
                boxLid->addTileBack(player->getPatternLines()->getPatternLine(lineNumber)[i]);
            }
        }
        

        // EMPTY PATTERN LINE
        player->getPatternLines()->emptyPatternLine(lineNumber);
    }
}

void Game::movePatternLinesToWall(Player* player)
{
    moveTileToWall(player, 1);
    moveTileToWall(player, 2);
    moveTileToWall(player, 3);
    moveTileToWall(player, 4);
    moveTileToWall(player, 5);
}

void Game::loadGame(string filename)
{
    bool validGame = true;
    //load file into string array delimited by new line
    ifstream inFile(filename);
    string file[28];
    int count = 0;
    while (getline(inFile, file[count])) {
    count++;
    }
    // load player turn TODO FIX LOAD PLAYER COMPARE
    int* playerIteratorPtr = nullptr;
    playerIteratorPtr = &playerIterator;
    *playerIteratorPtr = 0;
    if(file[1].compare("1") == 0){
        *playerIteratorPtr = 0;
    }
    else{
        *playerIteratorPtr = 1;
    }

    //load both players
    players = new Player;
    int score1 = stoi(file[3]);
    int score2 = stoi(file[5]);
    //checks that score is valid:
    if (score1<0 || score2 < 0){
        validGame = false;
        cout << "invalid score"<< endl;
    }
    //checks if names are valid:
    int player1Length = file[2].length();
    for (int i = 0; i<player1Length;i++){
        if (!isalpha(file[2][i])){
            validGame = false;
            cout << "invalid name for player 1: "<< file[2]<< endl;   
        }
    }
    int player2Length = file[4].length();
     for (int i = 0; i<player2Length;i++){
        if (!(isalpha(file[4][i]))){
            validGame = false;
            cout << "invalid name for player 2: "<< file[4][i] << endl;
        }
    }
    
    Player* playerOne = new Player(file[2], score1);
    Player* playerTwo = new Player(file[4], score2);
    players->players[0] = playerOne;
    players->players[1] = playerTwo;

    //counter used to check if total number of tiles add up to 101 (including F):
    int tileCounter = 0;

    //load centre factory
    centreFactory = new CentreFactory();
    int fileSixLength = file[6].length();
    for(int i = 0; i < fileSixLength; i++ ){
        centreFactory->centreFactory[i] = new Tile(file[6][i]);
        tileCounter ++;
        if (!isTileValid(centreFactory -> centreFactory[i])){
            validGame = false;
        }
    }
    //load factories
    factory = new Factory;
    //empty factories
    for(int outterLoop = 0; outterLoop < NUMBER_OF_FACTORIES;  outterLoop++)
    {
        for(int innerLoop = 0; innerLoop < FACTORY_SIZE;  innerLoop++)
        {
                factory->factories[outterLoop][innerLoop] = nullptr;
        }
    }
    
    //fill factories
    int fileFactoryNumCount = 7;
    for(int factoryNum = 0; factoryNum < NUMBER_OF_FACTORIES; factoryNum++){
        if(file[fileFactoryNumCount].length()>5){
            validGame = false;
            cout <<"Too many tiles in factory " << factoryNum+1 << endl;
        }
        for(int factoryTiles = 0; factoryTiles < FACTORY_SIZE; factoryTiles++){
            if(file[fileFactoryNumCount].length() != 0){
            factory->factories[factoryNum][factoryTiles] = new Tile(file[fileFactoryNumCount][factoryTiles]);
            tileCounter ++;
            if(!isTileValid(factory->factories[factoryNum][factoryTiles])){
                validGame = 0;
                cout << "invalid tile: " << factory->factories[factoryNum][factoryTiles]->getTile() << endl;
            }
            }
        }
        fileFactoryNumCount++;
    }
    //Load Pattern Lines
    //load player 1 pattern line
    int patternLineFileCount = 12;
    for (int i = 1; i < 6; i++){
        for (int j = 0; j < i; j++){
            if(file[patternLineFileCount][j] != '.'){
            players->players[0]->getPatternLines()->getPatternLine(i)[j] = new Tile(file[patternLineFileCount][j]);
            tileCounter ++;

            if(!isTileValid(players->players[0]->getPatternLines()->getPatternLine(i)[j])){
                validGame = false;
                cout << "invalid tile: " << players->players[0]->getPatternLines()->getPatternLine(i)[j]->getTile() << endl;
            }
            } else{
            players->players[0]->getPatternLines()->getPatternLine(i)[j] = nullptr;   
            }
            }
            patternLineFileCount++;
        }
    //load player 2 pattern line(19-23)
    patternLineFileCount = 19;
    for (int i = 1; i < 6; i++){
        for (int j = 0; j < i; j++){
            if(file[patternLineFileCount][j] !='.'){
            players->players[1]->getPatternLines()->getPatternLine(i)[j] = new Tile(file[patternLineFileCount][j]);
            tileCounter++;
            if(!isTileValid(players->players[1]->getPatternLines()->getPatternLine(i)[j])){
                validGame = false;
            }
            } else{
            players->players[1]->getPatternLines()->getPatternLine(i)[j] = nullptr;   
            }
            }
            patternLineFileCount++;
        }
    //load Floor lines
    //load floor line player 1
   int floorLineLength = file[17].length();
   if(floorLineLength != 0){
   for(int i = 0; i < floorLineLength; i++){
            players->players[0]->getFloorLine()->deductions[i] = new Tile(file[17][i]);
            tileCounter++;
            if(players->players[0]->getFloorLine()->deductions[i] != nullptr && !(isTileValid(players->players[0]->getFloorLine()->deductions[i]))){
                validGame = false;
            }
    }
   }
    //load floor line player 2
    floorLineLength = file[24].length();
    if(floorLineLength != 0){
   for(int i = 0; i < floorLineLength; i++){
        players->players[1]->getFloorLine()->deductions[i] = new Tile(file[24][i]);
        tileCounter++;
        if(!(isTileValid(players->players[1]->getFloorLine()->deductions[i]))){
            validGame = false;
        }
    }
    }
    //Load wall
    //load player1 wall
    int wallCount = 0;
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            if(file[18][wallCount] == 'R' || file[18][wallCount] == 'Y' || file[18][wallCount] == 'B' ||
             file[18][wallCount] == 'L' || file[18][wallCount] == 'U'){
            players->players[0]->getWall()->tile[i][j] = new Tile(file[18][wallCount]);
            tileCounter++;
                } else{
                    players->players[0]->getWall()->tile[i][j] = nullptr;
                }
            wallCount++;
        }
    }
    //load player2 wall
    wallCount = 0;
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            if(file[25][wallCount] == 'R' || file[25][wallCount] == 'Y' || file[25][wallCount] == 'B' ||
             file[25][wallCount] == 'L' || file[25][wallCount] == 'U'){
            players->players[1]->getWall()->tile[i][j] = new Tile(file[25][wallCount]);
            tileCounter++;
                } else{
                    players->players[1]->getWall()->tile[i][j] = nullptr;
                }
            wallCount++;
        }
    }
    //Load Box Lid
    boxLid = new BoxLid;
    boxLid->clear();
    int boxLidLength = file[26].length();
    for(int i = 0; i < boxLidLength; i++){
        Tile* newTileBoxLid = new Tile(file[26][i]);
        boxLid -> addTileBack(newTileBoxLid);
       // boxLid->addTileBack(new Tile(file[26][i]));
        tileCounter++;
        if(!isTileValid(newTileBoxLid)){
            validGame = false;
        }
    }
    //load tilebag
    int tileBagLoadLength = file[27].length();
    factory->getTileBag()->tileBagVector.clear();
    for(int i =0; i < tileBagLoadLength; i++){
        Tile* newTileTileBag = new Tile(file[27][i]);
        factory -> getTileBag() -> tileBagVector.push_back(newTileTileBag);
        //factory->getTileBag()->tileBagVector.push_back(new Tile(file[27][i]));
        tileCounter++;
        if(!isTileValid(newTileTileBag)){
            validGame = false;
        }
    }
    //checks if number of tiles are correct:
    if(tileCounter!=101){
        cout << "invalid number of valid tiles: " << tileCounter << endl;
        validGame = false;
    }

    if(validGame){

        while(!players->players[0]->getWall()->rowFilled() || !players->players[1]->getWall()->rowFilled())
        {
            aRound();
        }

        for(int i = 0; i < 2; i++)
        {
            players->players[i]->addPoints(players->players[i]->getWall()->horizontalBonusPoints());
            players->players[i]->addPoints(players->players[i]->getWall()->verticalBonusPoints());
            players->players[i]->addPoints(players->players[i]->getWall()->sameColourbonusPoints());
        }

        cout << "=== GAME OVER ===" << endl << endl;

        cout << players->isWinning(players->players[0], players->players[1]) << endl << endl;
    }
    else{
        cout << "Invalid game in file, try with another file name:" << endl;
        string filename = "";
        cin >> filename;
        loadGame(filename);

    }
}

void Game::saveGame(string filename)
{
    ofstream outFile;
    outFile.open(filename);
    
    //turn
    outFile << "" << endl;
    int* playerIteratorPtr = nullptr;
    playerIteratorPtr = &playerIterator;
    
    //if player 1 turn write 1, else write 0
    if(*playerIteratorPtr == 0)
    {
        outFile << "1" << endl;
    }
    else if (*playerIteratorPtr % 2 == 0)
    {
        outFile << "1" << endl;
    }
    else
    {
       outFile << "0" << endl;
    }
    
    //player1 name
    outFile << players->players[0]->getName() << endl;
    //player1 score
    outFile << players->players[0]->getPoints() << endl;
    //player2 name
    outFile << players->players[1]->getName() << endl;
    //player2 score
    outFile << players->players[1]->getPoints() << endl;
    //centre factory
    string centreFactoryString = centreFactory->getCentreFactoryString();
    outFile << centreFactoryString << endl;
    
    //factory 1-5
    outFile << factory->factoryToString(0) << endl;
    outFile << factory->factoryToString(1) << endl;
    outFile << factory->factoryToString(2) << endl;
    outFile << factory->factoryToString(3) << endl;
    outFile << factory->factoryToString(4) << endl;
    
    //player1 pattern line
    outFile << players->players[0]->getPatternLines()->patternLineOneToString() << endl;
    outFile << players->players[0]->getPatternLines()->patternLineTwoToString() << endl;
    outFile << players->players[0]->getPatternLines()->patternLineThreeToString() << endl;
    outFile << players->players[0]->getPatternLines()->patternLineFourToString() << endl;
    outFile << players->players[0]->getPatternLines()->patternLineFiveToString() << endl;
    
    //player1 floor line
    outFile << players->players[0]->getFloorLine()->floorLineToString() << endl;
    
    //player 1 wall
    outFile << players->players[0]->getWall()->wallToString() << endl;
    //player2 pattern line
    outFile << players->players[1]->getPatternLines()->patternLineOneToString() << endl;
    outFile << players->players[1]->getPatternLines()->patternLineTwoToString() << endl;
    outFile << players->players[1]->getPatternLines()->patternLineThreeToString() << endl;
    outFile << players->players[1]->getPatternLines()->patternLineFourToString() << endl;
    outFile << players->players[1]->getPatternLines()->patternLineFiveToString() << endl;
    //player2 floor line
    outFile << players->players[1]->getFloorLine()->floorLineToString() << endl;
    
    //player2 wall
    outFile << players->players[1]->getWall()->wallToString() << endl;
    //lid
    outFile << boxLid->printBoxLid() << endl;
    //tileBag
    outFile << factory->getTileBag()->tileBagToString();
    
    outFile.close();

}

void Game::deleteGame()
{
       
    // DECONSTRUCTING PLAYERS ELEMENTS
    for(int outterLoop = 0; outterLoop < 2; outterLoop++)
    {
        // DECONSTRUCTING FLOORLINE
        for(int innerLoop = 0; innerLoop < FLOOR_LINE_LENGTH; innerLoop++)
        {
            if(players->players[outterLoop]->getFloorLine()->deductions[innerLoop] != nullptr)
            {
                players->players[outterLoop]->getFloorLine()->deductions[innerLoop]->~Tile();
            }
        }
        players->players[outterLoop]->getFloorLine()->~FloorLine();
    
        // DECONSTRUCTING PATTERN LINE
        for(int patternLine = 1; patternLine < 5; patternLine++)
        {
            int patternLineSize = players->players[outterLoop]->getPatternLines()->getSize(players->players[outterLoop]->getPatternLines()->getPatternLine(patternLine));

            for(int innerLoop = 0; innerLoop < patternLineSize; innerLoop++)
            {
                if(players->players[outterLoop]->getPatternLines()->getPatternLine(patternLine)[innerLoop] != nullptr)
                {
                    players->players[outterLoop]->getPatternLines()->getPatternLine(patternLine)[innerLoop]->~Tile();
                }
            }
            
        }
        players->players[outterLoop]->getPatternLines()->~PatternLines();

        // DECONSTRUCTING WALL
        for(int wallRows = 0; wallRows < WALL_ROWS; wallRows++)
        {
            for(int wallColumns = 0; wallColumns < WALL_COLUMNS; wallColumns++)
            {
                if(players->players[outterLoop]->getWall()->tile[wallRows][wallColumns] != nullptr)
                {
                    players->players[outterLoop]->getWall()->tile[wallRows][wallColumns]->~Tile();
                }
            }
        }
        players->players[outterLoop]->getWall()->~Wall();
        
    }
    players->~Player();

    // DECONSTRUCTING CENTRE FACTORY 
    for(int i = 0; i < CENTRE_FACTORY_MAX_SIZE; i++)
    {
        if(centreFactory->centreFactory[i] != nullptr)
        {
            centreFactory->centreFactory[i]->~Tile();
        }
    }
    centreFactory->~CentreFactory();

    // DECONSTRUCTING TILEBAG
    int tileBagSize = factory->getTileBag()->tileBagVector.size();

    for(int i = 0; i < tileBagSize; i ++)
    {
        factory->getTileBag()->tileBagVector[i]->~Tile();
    }
    factory->getTileBag()->tileBagVector.clear();
    factory->getTileBag()->~TileBag();
    
    // DECONSTRUCTING FACTORY
    for(int outterLoop = 0; outterLoop < NUMBER_OF_FACTORIES; outterLoop++)
    {
        for(int innerLoop = 0; innerLoop < NUMBER_OF_FACTORIES; innerLoop++)
        {
            if(factory->factories[outterLoop][innerLoop] != nullptr)
            {
                factory->factories[outterLoop][innerLoop]->~Tile();
            }
        }    
    }
    factory->~Factory();

    // DECONSTRUCTING BOXLID
    boxLid->clear();
    boxLid->~BoxLid();
}

bool Game::isTileValid(Tile* tile)
{
    //valid tiles:
    string validTiles = "FBLRUY";
    bool valid = true;
    
    //checks if tile value is in valid tiles:
    if((validTiles.find(tile->getTile())==string::npos))
    {
        valid = false;
        cout << "invalid tile: " << tile -> getTile()<<endl;
    }
    return valid;
}