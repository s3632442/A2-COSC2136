#include "DataHandler.h"

// Constructors
DataHandler::DataHandler()
{
    filename = nullptr;
    currentPlayerName = nullptr;
    bag = nullptr;
    board = nullptr;
    player1 = nullptr;
    player2 = nullptr;
}

// Destructor
DataHandler::~DataHandler()
{

    // TODO
}

// loads data from a file & assigns it to relevent variables
//  assumtion is that the input file is in a valid format
//  file needs to exist & able to be opened
bool DataHandler::loadData(std::string filename)
{

    this->filename = &filename;
    currentPlayerName = new std::string("");
    bag = new LinkedList;
    board = new Board();
    player1 = new Player();
    player2 = new Player();

    std::string line;
    std::vector<std::string> gameData;
    std::ifstream inputFile(filename);

    // read each line
    while (getline(inputFile, line))
    {
        gameData.push_back(line);
    }


    for (int i = 0; i < gameData.size(); i++)
    {
        if (i == 0)
        {
            player1->setName(gameData.at(i));
        }
        else if (i == 1)
        {
            player1->setScore(std::stoi(gameData.at(i)));
        }
        else if (i == 2)
        {
            // 20220807
            // https://stackoverflow.com/questions/236129/how-do-i-iterate-over-the-words-of-a-string
            // https://developer.mozilla.org/en-US/docs/Web/JavaScript/Guide/Regular_Expressions
            // https://stackoverflow.com/questions/60350745/c-getline-extracting-a-substring-using-regex
            // https://www.geeksforgeeks.org/tokenizing-a-string-cpp/

            std::vector<std::string> tilesInHandAsStrings;
            char *str = const_cast<char *>(gameData.at(i).c_str());

            // Returns first token
            char *token = strtok(str, ", ");

            // Keep printing tokens while one of the
            // delimiters present in str[].
            while (token != NULL)
            {
                // printf("%s\n", token);
                // printf("%s ", token);
                tilesInHandAsStrings.push_back(token);
                // std::cout << "tilesInHandAsStrings size: " << tilesInHandAsStrings.size() << std::endl;
                token = strtok(NULL, ", ");
            }

            int tileCount = tilesInHandAsStrings.size();
            LinkedList *player1_hand = player1->getHand();

            for (int i = 0; i < tileCount; i++)
            {
                Colour colour = tilesInHandAsStrings.at(i).at(0);
                Shape shape = tilesInHandAsStrings.at(i).at(1);
                Tile *tile = new Tile(colour, shape);
                player1_hand->addEnd(tile);
            }
        }
        else if (i == 3)
        {
            player2->setName(gameData.at(i));
        }
        else if (i == 4)
        {
            player2->setScore(std::stoi(gameData.at(i)));
        }
        else if (i == 5)
        {
            // To Do. Parse player2 hand
            std::vector<std::string> tilesInHandAsStrings;
            char *str = const_cast<char *>(gameData.at(i).c_str());

            // Returns first token
            char *token = strtok(str, ", ");

            // Keep printing tokens while one of the
            // delimiters present in str[].
            while (token != NULL)
            {
                // printf("%s\n", token);
                // printf("%s ", token);
                tilesInHandAsStrings.push_back(token);
                // std::cout << "tilesInHandAsStrings size: " << tilesInHandAsStrings.size() << std::endl;
                token = strtok(NULL, ", ");
            }

            int tileCount = tilesInHandAsStrings.size();
            LinkedList *player1_hand = player2->getHand();

            for (int i = 0; i < tileCount; i++)
            {
                Colour colour = tilesInHandAsStrings.at(i).at(0);
                Shape shape = int(tilesInHandAsStrings.at(i).at(1) - '0');
                Tile *tile = new Tile(colour, shape);
                player1_hand->addEnd(tile);
            }
            player1_hand->printAll();
            // player2->setHand(player1_hand);
        }
        else if (i == 6)
        {
            // To Do. Board height and width.
            board = new Board(getBoardHeight(), getBoardWidth());
        }
        else if (i == 7)
        {
            // ToDo: Parse boardstate.

            // TODO 20220807

            std::vector<std::string> tilesInHandAsStrings;
            char *str = const_cast<char *>(gameData.at(i).c_str());

            // Returns first token
            char *token = strtok(str, ", ");

            // Keep printing tokens while one of the
            // delimiters present in str[].
            while (token != NULL)
            {
                // printf("%s\n", token);
                // printf("%s ", token);
                tilesInHandAsStrings.push_back(token);

                token = strtok(NULL, ", ");
            }

            int tileCount = tilesInHandAsStrings.size();
            LinkedList *player2_hand = player2->getHand();

            for (int i = 0; i < tileCount; i++)
            {
                Colour colour = tilesInHandAsStrings.at(i).at(0);
                Shape shape = int(tilesInHandAsStrings.at(i).at(1) - '0');
                Tile *tile = new Tile(colour, shape);
                player2_hand->addEnd(tile);
            }
            player2_hand->printAll();
            // player2->setHand(player2_hand);
        }
        else if (i == 8)
        {
            // ToDo: bag.addEnd(everyParsedTile)
            std::vector<std::string> tilesInBagAsStrings;
            char *str = const_cast<char *>(gameData.at(i).c_str());

            // Returns first token
            char *token = strtok(str, ", ");

            // Keep printing tokens while one of the
            // delimiters present in str[].
            while (token != NULL)
            {
                // printf("%s\n", token);
                // printf("%s ", token);
                tilesInBagAsStrings.push_back(token);

                token = strtok(NULL, ", ");
            }

            int tileCount = tilesInBagAsStrings.size();
            // LinkedList *player2_hand = player2->getHand();

            for (int i = 0; i < tileCount; i++)
            {
                Colour colour = tilesInBagAsStrings.at(i).at(0);
                Shape shape = tilesInBagAsStrings.at(i).at(1);
                Tile *tile = new Tile(colour, shape);
                bag->addEnd(tile);
            }
        }
        else if (i == 9)
        {
            currentPlayerName = &gameData.at(i);
        }
        else
        {
            // The rent is too damn high!
        }
    }

    inputFile.close();
    return true;
}

// Saves data to a file & from relevent variables
//  assumtion is that the data is in the correct format file is in a valid format
// file needs to be opened or created
bool DataHandler::saveData()
{
    std::ofstream outputFile(*filename);
    outputFile << player1->getName() << std::endl;
    outputFile << player1->getScore() << std::endl;
    outputFile << handAsString(player1) << std::endl;
    outputFile << player2->getName() << std::endl;
    outputFile << player2->getScore() << std::endl;
    outputFile << handAsString(player2) << std::endl;
    outputFile << boardShapeAsString(board) << std::endl;
    outputFile << setBoardStateAsString(board) << std::endl;
    outputFile << bagContentsAsString(bag) << std::endl;
    outputFile << *currentPlayerName << std::endl;

    outputFile.close();

    loadData(*filename);
    return true;
}

void DataHandler::setPlayer1(Player *&player1)
{
    this->player1 = player1;
}

void DataHandler::setPlayer2(Player *&player2)
{
    this->player2 = player2;
}

void DataHandler::setBoard(Board *&board)
{
    this->board = board;
}

void DataHandler::setBag(LinkedList *&bag)
{
    this->bag = bag;
}

void DataHandler::setCurrentPlayerName(std::string *&currentPlayerName)
{
    this->currentPlayerName = currentPlayerName;
}

void DataHandler::setFilename(std::string *&filename)
{
    this->filename = filename;
}

std::string DataHandler::handAsString(Player *&player)
{
    std::string handAsString = "";
    LinkedList *hand = nullptr;
    if (player->getHand() != nullptr)
    {
        hand = player->getHand();
    }
    else
    {
        std::cout << "WHY is Player::getHand() a nullptr?" << std::endl;
    }

    int count = 0;
    int hand_size = hand->getLength();
    for (int i = 0; i < hand_size; i++)
    {
        Node *node = hand->getNodeByIndex(i);
        Tile *tile = node->getData();
        if (tile != nullptr)
        {
            // std::cout << "tile != nullptr" << std::endl;

            Colour colour = tile->getColour();
            Shape shape = tile->getShape();
            handAsString.push_back(colour);
            handAsString.push_back(shape + ASCII_NUMERIC_OFFSET);

            count++;
        }
        else
        {
            // std::cout << "tile == nullptr" << std::endl;
        }

        if (count < hand_size)
        {
            handAsString.append(",");
        }
    }
    return handAsString;
}

std::string DataHandler::boardShapeAsString(Board *&board)
{
    std::string boardShape = "";
    std::string heightAsString = std::to_string(ROW_COUNT);
    std::string widthAsString = std::to_string(COL_COUNT);

    boardShape.append(heightAsString);
    boardShape.append(",");
    boardShape.append(widthAsString);

    return boardShape;
}

std::string DataHandler::setBoardStateAsString(Board *&board)
{
    std::string boardState = "";

    // Build string tokens of <Colour><Shape>@<Row><Column>
    std::vector<std::string> tilesWithCoords;
    for (int row = 0; row < ROW_COUNT; row++)
    {
        for (int column = 0; column < COL_COUNT; column++)
        {
            Tile *tile = board->getTileAt(row, column);
            if (tile != nullptr)
            {
                // Building a ColourShape@RowColumn string
                Colour colour = tile->getColour();
                Shape shape = tile->getShape();
                char rowAsChar = row + ASCII_ALPHABET_OFFSET;
                std::string columnAsString = std::to_string(column);
                std::string tileText = "";
                tileText.push_back(colour);
                tileText.push_back(shape + ASCII_NUMERIC_OFFSET);
                tileText.push_back('@');
                tileText.push_back(rowAsChar);
                // tileText.push_back(columnAsChar);
                tileText.append(columnAsString);

                // Append to local vector<string>
                tilesWithCoords.push_back(tileText);
            }
        }
    }

    int tileCount = tilesWithCoords.size();
    int count = 0;

    for (int i = 0; i < tileCount; i++)
    {
        boardState.append(tilesWithCoords.at(i));
        count++;
        if (count < tileCount)
        {
            boardState.append(", ");
        }
    }

    return boardState;
}

std::string DataHandler::bagContentsAsString(LinkedList *&bag)
{
    std::string bagContents = "";
    if (bag != nullptr)
    {
        int count = 0;
        int bag_size = bag->getLength();
        for (int i = 0; i < bag_size; i++)
        {
            Node *node = bag->getNodeByIndex(i);
            Tile *tile = node->getData();
            if (tile != nullptr)
            {
                // std::cout << "tile != nullptr" << std::endl;

                Colour colour = tile->getColour();
                Shape shape = tile->getShape();
                bagContents.push_back(colour);
                bagContents.push_back(shape + ASCII_NUMERIC_OFFSET);

                count++;
            }
            else
            {
                // std::cout << "tile == nullptr" << std::endl;
            }

            if (count < bag_size)
            {
                bagContents.append(",");
            }
        }
    }
    else
    {
        std::cout << "WHY is bag a nullptr?" << std::endl;
    }

    return bagContents;
}

std::string DataHandler::getPlayer1Name()
{
    std::string player1name = "";
    if (player1 != nullptr)
    {
        player1name = player1->getName();
    }

    return player1name;
}

std::string DataHandler::getPlayer2Name()
{
    std::string player2name = "";
    if (player2 != nullptr)
    {
        player2name = player2->getName();
    }

    return player2name;
}

void DataHandler::fillBagWithSavedTiles(LinkedList *&bag)
{
}

void DataHandler::fillPlayer1HandWithSavedTiles(LinkedList *&hand)
{
    Node *temp = player1->getHand()->getHead();

    if (temp != NULL)
    {
        while (temp != NULL)
        {
            temp = temp->getNext();

            hand->addEnd(player1->getHand()->removeFront());
        }
    }
}

void DataHandler::fillPlayer2HandWithSavedTiles(LinkedList *&hand)
{
    Node *temp = player2->getHand()->getHead();

    if (temp != NULL)
    {
        while (temp != NULL)
        {
            temp = temp->getNext();

            hand->addEnd(player2->getHand()->removeFront());
        }
    }
}

int DataHandler::getPlayer1Score()
{
    int player1_score = this->player1->getScore();
    return player1_score;
}

int DataHandler::getPlayer2Score()
{
    int player2_score = this->player2->getScore();
    return player2_score;
}

int DataHandler::getBoardHeight()
{
    int boardHeight;
    boardHeight = 26;

    return boardHeight;
}

int DataHandler::getBoardWidth()
{
    int boardWidth;
    boardWidth = 26;

    return boardWidth;
}

int getBoardState() {}

std::string DataHandler::getCurrentPlayerName()
{
    std::string playername = "";
    if (currentPlayerName != nullptr)
    {
        playername = *currentPlayerName;
    }
    else
    {
    }
    return playername;
}
