/**
 * @file Game.cpp
 * @author your name (you@domain.com)
 * @brief Engine that allows new Qwirkle games, saving of games,
 * loading of saved games.
 * @version 0.1
 * @date 2022-08-07
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "Game.h"

Game::Game()
{
    this->itIsPlayer1s_turn = new bool(true);
    this->player1 = new Player();
    this->player2 = new Player();
    this->player3 = new Player();
    this->player4 = new Player();
    this->currentPlayer = new Player();
    this->board = new Board(ROW_COUNT, COL_COUNT);
    this->bag = new LinkedList();
    this->validation = new Validation();
    this->scoringSystem = new ScoringSystem();
}

Game::~Game()
{
    delete itIsPlayer1s_turn;
    itIsPlayer1s_turn = nullptr;
    delete player1;
    player1 = nullptr;
    delete player2;
    player2 = nullptr;
    delete currentPlayer;
    currentPlayer = nullptr;
    delete board;
    board = nullptr;
    delete bag;
    bag = nullptr;
    delete validation;
    validation = nullptr;
    delete scoringSystem;
    scoringSystem = nullptr;
}

// Labeled board, as string
std::string Game::getBoardAsString()
{
    std::string boardLayout = "";
    std::string columnHeader = "" + std::string(1, SPACE);
    std::string horizontalLine = "" + std::string(1, DASH);
    int CUI_column_width = 3;
    int index_zero = 0;
    int once = 1;
    std::string rowHeadersAndTiles = "";

    // Look at each Tile at each row/column
    for (int row = 0; row < ROW_COUNT; row++)
    {
        // Prepend row names (e.g. A - Z)
        char row_name = row + ASCII_ALPHABET_OFFSET;
        std::string row_contents = "";
        row_contents.push_back(PIPE);
        row_contents.insert(index_zero, once, row_name);

        for (int column = 0; column < COL_COUNT; column++)
        {
            // Column names
            if (row == 0)
            {
                std::string column_name = std::to_string(column);
                int i_width = column_name.length();
                int prefixSpacesCount = i_width % CUI_column_width;
                int prefixCount = CUI_column_width - prefixSpacesCount;
                column_name.insert(index_zero, CUI_column_width - prefixSpacesCount, SPACE);
                columnHeader.append(column_name);
                horizontalLine.insert(index_zero, CUI_column_width, DASH);
            }

            // Append tile ColourShape per column
            Tile *tile = board->getTileAt(row, column);
            std::string tileText = "";

            if (tile == nullptr)
            {
                tileText.push_back(SPACE);
                tileText.push_back(SPACE);
            }
            else if (tile != nullptr)
            {
                Colour colour = tile->getColour();
                Shape shape = tile->getShape();
                tileText = "";
                tileText.insert(index_zero, once, shape + ASCII_NUMERIC_OFFSET);
                tileText.insert(index_zero, once, colour);
            }

            // Adding each column's contents to the current row's string
            row_contents.append(tileText);
            row_contents.push_back(PIPE);
        } // for (columns)

        // Adding each row to a combined string
        rowHeadersAndTiles.append(row_contents);
        rowHeadersAndTiles.append("\n");
    } // for (rows)

    // Bring together headers and board rows
    boardLayout.append(columnHeader);
    boardLayout.append("\n");
    boardLayout.append(horizontalLine);
    boardLayout.append("\n");
    boardLayout.append(rowHeadersAndTiles);

    return boardLayout;
}

// Setup bag, player1 and player2
bool Game::newGame()
{
    // New Tiles
    fillBagAndShuffle();
    setupNewPlayers();

    std::cout << "Let's Play!" << std::endl;
    std::cout << std::endl;

    nextTurn = play();
    return nextTurn;
}

bool Game::loadGame()
{
    std::cout << "Enter the filename from which to load a game" << std::endl;
    std::cout << "> ";

    std::string filename = "";
    filename = getUserInput();
    if (validation->checkFileExists(filename))
    {
        // Parse data from file
        DataHandler dataHandler;
        dataHandler.loadData(filename);

        // Get Player1 and Player2 info
        player1->setName(dataHandler.getPlayer1Name());
        player1->setScore(dataHandler.getPlayer1Score());
        LinkedList *player1Hand = player1->getHand();
        dataHandler.fillPlayer1HandWithSavedTiles(player1Hand);

        player2->setName(dataHandler.getPlayer2Name());
        player2->setScore(dataHandler.getPlayer2Score());
        LinkedList *player2Hand = player2->getHand();
        dataHandler.fillPlayer2HandWithSavedTiles(player2Hand);

        // Get tiles for bag
        dataHandler.fillBagWithSavedTiles(bag);

        // Get board
        int rowCount = dataHandler.getBoardHeight();
        int columnCount = dataHandler.getBoardWidth();
        delete board;
        board = nullptr;
        board = new Board(rowCount, columnCount);
        *board = dataHandler.getBoard();

        // Get itIsPlayer1s_turn bool
        if (player1->getName() == dataHandler.getCurrentPlayerName())
        {
            *itIsPlayer1s_turn = true;
        }
        else if (player2->getName() == dataHandler.getCurrentPlayerName())
        {
            *itIsPlayer1s_turn = false;
        }
        else
        {
            *itIsPlayer1s_turn = true;
        }

        std::cout << std::endl;

        nextTurn = play();
    }
    else
    {
        std::cout << "Filename " << filename << " wasn't found." << std::endl;
    }
    return nextTurn;
}

bool Game::play()
{
    bool exiting = false;

    // Play until:
    // 1. User types EOF (Control+D on unix/Mac; Control+Z on Windows), or,
    // 2. Tiles depleted
    do
    {

        printCurrentPlayer(currentPlayer);
        printScores();
        printBoard();
        printHand(currentPlayer);
        printBagTileCount();
        promptForPlayInput();
        nextTurn = takeTurn(currentPlayer);
        exiting = checkEndGameConditions(currentPlayer);

        if (exiting)
        {
            // End of game.
            currentPlayer->addToScore(50); // what was the bonus for finishing tiles?
            std::cout << "WINNER IS ? " << std::endl;
            printScores();
        }
        else
        {
            // Switch player turns
            *itIsPlayer1s_turn = !*itIsPlayer1s_turn;
        }

    } while (!exiting && nextTurn);

    return nextTurn;
}

void Game::prompt_invalidInput()
{
    printBoard();
    // 20220724
    // https://www.geeksforgeeks.org/tokenizing-a-string-cpp/
    // https://stackoverflow.com/questions/27706443/c-spliting-string-by-delimiters-and-keeping-the-delimiters-in-result

    std::cout << "I'm sorry, " << currentPlayer->getName() << ". I'm afraid I can't do that." << std::endl;
    std::cout << "You may replace a tile, place a tile, or save the game" << std::endl;
    std::cout << "> replace P6" << std::endl;
    std::cout << "> place G5 at C4" << std::endl;
    std::cout << "> save savedGame" << std::endl;
}

void Game::fillBagAndShuffle()
{
    Colour colours[] = {RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE};
    Shape shapes[] = {CIRCLE, STAR_4, DIAMOND, SQUARE, STAR_6, CLOVER};
    LinkedList *tempBag = new LinkedList();

    int coloursCount = sizeof(colours) / sizeof(Colour);
    int shapesCount = sizeof(shapes) / sizeof(Shape);

    // Add new Tile objects to the game.
    for (int i = 0; i < coloursCount; i++)
    {
        for (int j = 0; j < shapesCount; j++)
        {
            Tile *tileA = new Tile(colours[i], shapes[j]);
            Tile *tileB = new Tile(colours[i], shapes[j]);
            tempBag->addEnd(tileA);
            tempBag->addEnd(tileB);
        }
    }

    // Lottery redraw
    // 20220801
    // https://stackoverflow.com/questions/13445688/how-to-generate-a-random-number-in-c
    // https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution

    int tileCount = tempBag->getLength();

    // Int RNG between 0 and tileCount-1, inclusive
    std::random_device seedFetcher;
    std::mt19937 randomiser(seedFetcher());
    std::uniform_int_distribution<> intRNG(0, tileCount - 1);

    for (int i = 0; i < tileCount; i++)
    {
        bool testingWhetherTileAllowed = true;
        while (testingWhetherTileAllowed)
        {
            int randomInt = intRNG(randomiser);
            Node *node = tempBag->getNodeByIndex(randomInt);
            Tile *tile = node->getData();
            int frequency = bag->frequency(tile);
            if (frequency < 2)
            {
                // Allowed. Testing finished.
                bag->addEnd(tile);
                testingWhetherTileAllowed = false;
            }
        }
    }
    delete tempBag;
    tempBag = nullptr;
}

void Game::printHand(Player *&player)
{
    // Print hand
    std::cout
        << "Your hand is" << std::endl;

    std::string handAsString = "";
    LinkedList *hand = nullptr;
    if (player->getHand() != nullptr)
    {
        player->getHand()->printAll();
    }
    else
    {
        std::cout << "WHY is Player::getHand() a nullptr?" << std::endl;
    }
}

void Game::printScores()
{
    std::cout << "Score for " << player1->getName() << ": "
              << player1->getScore() << std::endl;
    std::cout << "Score for " << player2->getName() << ": "
              << player2->getScore() << std::endl;
    if (numToPlay == '3')
    {
        std::cout << "Score for " << player3->getName() << ": "
                  << player3->getScore() << std::endl;
    }
    else if (numToPlay == '4')
    {
        std::cout << "Score for " << player3->getName() << ": "
                  << player3->getScore() << std::endl;
        std::cout << "Score for " << player4->getName() << ": "
                  << player4->getScore() << std::endl;
    }
}

void Game::printBoard()
{
    // Print board
    std::cout << getBoardAsString() << std::endl;
}

void Game::promptForPlayInput()
{
    // Print example turn text
    std::cout << "Example turn is:\n"
              << "> replace P6\n"
              << "> place G5 at C4\n"
              << "> save savedGame\n"
              << "or\n"
              << "> EOF (Control+D on unix/Mac; Control+Z on Windows)" << std::endl;

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "> ";
}

// 20220802
// https : // stackoverflow.com/questions/16276176/can-i-modify-the-target-of-a-pointer-passed-as-parameter
void Game::printCurrentPlayer(Player *&whoseTurnItIs)
{

    if (nextPlayer == 1)
    {
        whoseTurnItIs = this->player1;
        nextPlayer = 2;
    }
    else if (nextPlayer == 2)
    {
        whoseTurnItIs = this->player2;
        nextPlayer = 3;
    }
    else if (nextPlayer == 3)
    {
        whoseTurnItIs = this->player3;
        nextPlayer = 4;
    }
    else if (nextPlayer == 4)
    {
        whoseTurnItIs = this->player4;
        nextPlayer = 1;
    }
    std::cout << whoseTurnItIs->getName() << ", it's your turn" << std::endl;
}

bool Game::takeTurn(Player *&whoseTurnItIs)
{

    bool inputIsInvalid = true;
    bool takeTurn = true;
    do
    {

        std::vector<std::string> inputTokens = tokeniseInput();

        if (inputTokens.at(0)[1] == '0' && inputTokens.at(0)[0] == '/')
        {
            takeTurn = false;
        }
        else if (inputTokens.at(0) == "help")
        {
            std::cout << "-----------------HELP-----------------\nThe tiles you can play are listed as \"Your hand\"\nYou can play a tile matching its letter or number to the letter and number of a tile on the board\nThe letters and numbers represent their described colour or shape\nThe point is to make a string of matching colours or shapes in order to gain points by adding to the string, though there can only be one of each combination in any given sequence\nIf you achieve a complete sequence of all available types you get a quirkle and extra points\n";
            play();
        }
        else if (validation->validateInputLength(inputTokens.size()))
        {

            if (inputTokens.size() != 4 && inputTokens.size() != 2)
            {
                prompt_invalidInput();
            }
            else if (inputTokens.size() == 4)
            {
                std::string place = "place";
                std::string firstWord = inputTokens.at(0);

                if (firstWord == place)
                {
                    std::string board_coord = inputTokens.at(3);
                    std::transform(board_coord.begin(), board_coord.end(), board_coord.begin(), ::toupper);

                    int row = board_coord.at(0) - ASCII_ALPHABET_OFFSET;

                    std::string columnString = board_coord.substr(1);
                    std::transform(columnString.begin(), columnString.end(), columnString.begin(), ::toupper);

                    int column = std::stoi(columnString);
                    std::string tile_colour_shape = inputTokens.at(1);

                    // 20220807
                    // https://stackoverflow.com/questions/60578429/converting-strings-to-uppercase-c
                    std::transform(tile_colour_shape.begin(), tile_colour_shape.end(), tile_colour_shape.begin(), ::toupper);

                    Colour colour = tile_colour_shape.at(0);
                    Shape shape = tile_colour_shape.at(1) - ASCII_NUMERIC_OFFSET;

                    tempTile = new Tile(colour, shape);
                    LinkedList *hand = whoseTurnItIs->getHand();
                    if (hand->nodeExists(*tempTile))
                    {
                        // 20220802
                        // https://stackoverflow.com/questions/53208715/assigning-values-to-a-vector-of-pointers
                        // https://stackoverflow.com/questions/53774495/how-to-change-elements-of-a-pointer-to-a-vector                        board->placeTileAt(tempTile, row, column);

                        if (validation->validateInputProposed(tempTile, board, board_coord))
                        {
                            board->placeTileAt(tempTile, row, column);

                            hand->removeNodeContaining(tempTile);

                            whoseTurnItIs->getHand()->addEnd(bag->removeFront());

                            int playerScore = scoringSystem->countPoints(board, row, column);
                            std::cout << "playerScore: " << playerScore << std::endl;
                            whoseTurnItIs->addToScore(playerScore);

                            inputIsInvalid = false;
                        }
                        else
                        {
                            std::cout << "INPUT NOT RECOGNISED AS VALID\n"
                                      << "NOTE: \nTiles must match colour or shape in a vertical or a horizontal line.\n"
                                      << "Tile placement must be within board bounds e.g. A0 to Z25"
                                      << "\n\n> ";
                            prompt_invalidInput();
                        }
                    }
                    else
                    {
                        Colour colour = tempTile->getColour();
                        Shape shape = tempTile->getColour();
                        std::string tileAsString = "";
                        tileAsString.push_back(colour);
                        tileAsString.push_back(shape + ASCII_NUMERIC_OFFSET);
                        prompt_invalidInput();
                        std::cout << "TILE " << tile_colour_shape << " ISN'T IN HAND\n";
                    }
                } // if words entered were parsed within expectations
                else
                {
                    // Else, invalid
                    prompt_invalidInput();
                }
            }
            else if (inputTokens.size() == 2)
            {
                std::string firstWord = inputTokens.at(0);
                std::string secondWord = inputTokens.at(1);
                if (firstWord != "replace" && firstWord != "save")
                {
                    prompt_invalidInput();
                }
                else if (firstWord == "replace")
                {
                    std::cout << "YOU TYPED: replace " << secondWord << std::endl;
                    std::transform(secondWord.begin(), secondWord.end(), secondWord.begin(), ::toupper);
                    Colour colour = secondWord.at(0);
                    Shape shape = secondWord.at(1) - ASCII_NUMERIC_OFFSET;
                    tempTile = new Tile(colour, shape);
                    hand = whoseTurnItIs->getHand();
                    if (hand->nodeExists(*tempTile))
                    {

                        hand->removeNodeContaining(tempTile);
                        hand->addEnd(bag->removeFront());
                        bag->addEnd(tempTile);
                        inputIsInvalid = false;
                    }
                    else
                    {

                        std::cout << "That tile is not in your hand\n";
                        inputIsInvalid = true;
                        prompt_invalidInput();
                    }
                }

                else if (firstWord == "save")
                {
                    // display menu
                    std::string *ouputFilename = new std::string(secondWord);
                    ouputFilename->append(".txt");
                    saveGame(ouputFilename);
                    std::cout << "saved " << *ouputFilename << std::endl;
                    inputIsInvalid = false;
                }
            }
        } // valid inputTokens.size()
        else
        {
            // Invalid wordcount
            prompt_invalidInput();
        }

    } while (inputIsInvalid && takeTurn);

    return takeTurn;
}

bool Game::getCharacter(char c)
{

    if (std::cin.eof())
    {
        return true;
    }
    else
    {
        return false;
    }
};

bool Game::checkEndGameConditions(Player *&player)
{
    bool exiting = false;
    int hand_size = player->getHand()->getLength();
    int bag_count = bag->getLength();
    if (hand_size == 0 && bag_count == 0)
    {
        exiting = true;
    }
    return exiting;
}

void Game::printBagTileCount()
{

    std::cout << std::endl;
}

void Game::saveGame(std::string *&filename)
{
    DataHandler dataHandler;
    std::string *currentPlayerName = new std::string("");
    if (*itIsPlayer1s_turn)
    {
        *currentPlayerName = this->player1->getName();
    }
    else
    {
        *currentPlayerName = this->player2->getName();
    }
    dataHandler.setPlayer1(player1);
    dataHandler.setPlayer2(player2);
    dataHandler.setBoard(board);
    dataHandler.setBag(bag);
    dataHandler.setCurrentPlayerName(currentPlayerName);
    dataHandler.setFilename(filename);
    dataHandler.saveData();
}

// Get a sentence worth of user input. Returns nullptr if EOF.
std::string Game::getUserInput()
{
    std::string input_text = "";

    // Vector of string to save tokens/words
    std::vector<std::string> tokenisedInput;
    std::string word;

    // Parsing sentence input using streams
    std::string usersInput;
    std::cin >> std::ws;

    std::getline(std::cin, usersInput);
    std::stringstream ss(usersInput);

    if (!std::cin)
    {
        // When std::cin fails, short circuit
        if (std::cin.eof())
        {
            // 20220807
            // https://stackoverflow.com/questions/2251433/checking-for-eof-in-stringgetline
            // https://stackoverflow.com/questions/14305722/c-fstream-throwing-exception-when-reaching-eof
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "EOF\n";
            std::cin.clear();
            std::cin.ignore();
            std::cin >> std::ws;
            input_text = "EOF";
        }
        else
        {
            std::cout << "I/O error" << std::endl;
        }
    }
    else
    {
        // When std::cin succeeds, parse away
        while (ss >> word)
        {
            tokenisedInput.push_back(word);
        }
        int wordCount = 0;
        wordCount = tokenisedInput.size();

        for (int i = 0; i < tokenisedInput.size(); i++)
        {
            input_text.append(tokenisedInput.at(i));
        }
    }

    return input_text;
}

void Game::setupNewPlayers()
{
    int playerNamesEntered = 0;
    int playersCount = 2;
    Player *currentPlayer = player1;

    std::string playerPseudonym = "";

    do
    {

        if (playerNamesEntered == 0)
        {
            currentPlayer = player1;
            playerPseudonym = "player 1";
        }
        else if (playerNamesEntered == 1)
        {
            currentPlayer = player2;
            playerPseudonym = "player 2";
        }
        else if (playerNamesEntered == 2)
        {
            currentPlayer = player3;
            playerPseudonym = "player 3";
        }
        else if (playerNamesEntered == 3)
        {

            currentPlayer = player4;
            playerPseudonym = "player 4";
        }
        if (numToPlay == '0')
        {
            std::cout
                << "How many people will play? (2-4)"
                << std::endl;
            std::cout << "> ";
            numToPlay = tokeniseInput().at(0)[0];
        }
        else if (numToPlay == '2')
        {
            playersCount = 2;

            // Prompt for username
            std::cout
                << "Enter a name for " << playerPseudonym << " (uppercase characters only)"
                << std::endl;
            std::cout << "> ";

            std::string player_name = "DEFAULT";
            player_name = getUserInput();
            if (player_name == "help")
            {
                std::cout << "---------HELP---------\nPlease enter a name for the first player and then press enter\nThen do the same for the second player\nAll names must be ALL CAPS not sure why but thats what we did and I dont have time to mess around fixing it\n";
            }
            else
            {
                bool nameIsValid = validation->playerNameValid(player_name);
                if (nameIsValid)
                {
                    currentPlayer->setName(player_name);
                    LinkedList *player_hand = currentPlayer->getHand();
                    for (int i = 0; i < handTilecount; i++)
                    {
                        player_hand->addEnd(bag->removeFront());
                    }

                    *itIsPlayer1s_turn = !*itIsPlayer1s_turn;
                    playerNamesEntered++;
                }
                else
                {
                    std::cout << "Username must be UPPERCASE characters, A to Z only" << std::endl;
                }
                std::cout << std::endl;
                std::cout << std::endl;
            }
        }
        else if (numToPlay == '3')
        {
            playersCount = 3;

            // Prompt for username
            std::cout
                << "Enter a name for " << playerPseudonym << " (uppercase characters only)"
                << std::endl;
            std::cout << "> ";

            std::string player_name = "DEFAULT";
            player_name = getUserInput();
            if (player_name == "help")
            {
                std::cout << "---------HELP---------\nPlease enter a name for the first player and then press enter\nThen do the same for the second player\nAll names must be ALL CAPS not sure why but thats what we did and I dont have time to mess around fixing it\n";
            }
            else
            {
                bool nameIsValid = validation->playerNameValid(player_name);
                if (nameIsValid)
                {
                    currentPlayer->setName(player_name);
                    LinkedList *player_hand = currentPlayer->getHand();
                    for (int i = 0; i < handTilecount; i++)
                    {
                        player_hand->addEnd(bag->removeFront());
                    }

                    *itIsPlayer1s_turn = !*itIsPlayer1s_turn;
                    playerNamesEntered++;
                }
                else
                {
                    std::cout << "Username must be UPPERCASE characters, A to Z only" << std::endl;
                }
                std::cout << std::endl;
                std::cout << std::endl;
            }
        }
        else if (numToPlay == '4')
        {

            playersCount = 4;

            // Prompt for username
            std::cout
                << "Enter a name for " << playerPseudonym << " (uppercase characters only)"
                << std::endl;
            std::cout << "> ";

            std::string player_name = "DEFAULT";
            player_name = getUserInput();
            if (player_name == "help")
            {
                std::cout << "---------HELP---------\nPlease enter a name for the first player and then press enter\nThen do the same for the second player\nAll names must be ALL CAPS not sure why but thats what we did and I dont have time to mess around fixing it\n";
            }
            else
            {

                bool nameIsValid = validation->playerNameValid(player_name);

                if (nameIsValid)
                {
                    std::cout << player_name << std::endl;
                    currentPlayer->setName(player_name);
                    LinkedList *player_hand = currentPlayer->getHand();

                    for (int i = 0; i < handTilecount; i++)
                    {
                        player_hand->addEnd(bag->removeFront());
                    }

                    *itIsPlayer1s_turn = !*itIsPlayer1s_turn;

                    playerNamesEntered++;
                }
                else
                {
                    std::cout << "Username must be UPPERCASE characters, A to Z only" << std::endl;
                }
                std::cout << std::endl;
                std::cout << std::endl;
            }
        }
    } while (playerNamesEntered < playersCount);
}
std::vector<std::string> Game::tokeniseInput()
{

    int wordCount = 0;
    std::string user_input = "";

    std::cin >> std::ws;
    std::getline(std::cin, user_input);

    std::vector<std::string> tokenisedInput;
    std::string word;
    std::stringstream ss(user_input);
    int count = 0;
    while (ss >> word)
    {
        tokenisedInput.push_back(word);
        count++;
    }
    wordCount = tokenisedInput.size();
    return tokenisedInput;
}