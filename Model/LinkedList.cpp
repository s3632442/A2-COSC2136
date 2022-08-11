#include "LinkedList.h"

LinkedList::LinkedList()
{
    this->head = nullptr;
    this->tail = nullptr;
    this->length = 0;
}
LinkedList::~LinkedList()
{
    delete head;
    delete tail;
}

int LinkedList::getLength()
{
    return this->length;
};

void LinkedList::printAll()
{
    Node *temp = head;

    if (temp == NULL)
    {
        std::cout << "the list is empty\n";
    }
    else
    {
        while (temp != NULL)
        {
            temp->printData();
            std::cout << std::endl;
            temp = temp->getNext();
        }
    }
}
void LinkedList::addEnd(Tile *n)
{

    Node *temp = new Node(n);

    if (this->head == NULL)
    {

        this->head = temp;
        this->tail = temp;
    }
    else
    {
        this->tail->setNext(temp);
        tail = tail->getNext();
    };
    this->length++;
};

void LinkedList::removeEnd()
{
    if (this->head == NULL)
    {
        return;
    }
    Node *temp = head;
    // try with a for
    while (temp->getNext() != tail)
    {
        temp = temp->getNext();
    }

    delete this->tail;
    temp->setNext(NULL);
    this->tail = temp;
    this->length--;
}

void LinkedList::addFront(Tile *n)
{
    Node *temp = new Node(n);

    if (this->head == NULL)
    {
        this->head = temp;
        this->tail = temp;
    }
    else
    {
        temp->setNext(this->head);
        this->head = temp;
    }
    this->length++;
}

Tile *LinkedList::removeFront()
{
    Tile *front;
    if (this->head == NULL)
    {
    }
    else if (head == tail)
    {
        front = head->getData();
        this->head = NULL;
        this->tail = NULL;
    }
    else
    {
        Node *temp = head;
        front = head->getData();
        head = head->getNext();
        delete temp;
    }
    this->length--;
    return front;
}

bool LinkedList::nodeExists(Tile i)
{
    Node *temp = head;
    bool *exists = new bool(false);

    if (temp != NULL)
    {

        while (temp != NULL)
        {
            if (temp->getData()->getColour() != i.getColour() || temp->getData()->getShape() != i.getShape())
            {
                temp = temp->getNext();
                *exists = false;
            }
            else
            {
                temp = NULL;
                *exists = true;
            }
        }
    }
    return *exists;
}

Node *LinkedList::getNodeByData(Tile d)
{
    Node *temp = head;
    bool *found = new bool(false);

    if (temp != NULL)
    {
        while (temp != NULL && !*found)
        {
            if (temp->getData()->getColour() != d.getColour() || temp->getData()->getShape() != d.getShape())
            {

                temp = temp->getNext();
            }
            else
            {

                *found = true;
            }
        }
    }
    return temp;
}

Node *LinkedList::getNodeByIndex(int i)
{

    int Count = 0;

    Node *temp = head;
    Node *r = new Node();

    if (temp != NULL)
    {
        while (temp != NULL)
        {
            if (Count != i)
            {

                temp = temp->getNext();
            }
            else if (Count == i)
            {

                *r = *temp;
            }
            Count++;
        }
    }
    return r;
}

void LinkedList::removeNodeAtIndex(int n)
{
    Node *temp1 = head;
    Node *temp2;
    int i;

    for (i = 0; i < n - 2; i++)
    {
        temp1 = temp1->getNext();
    }
    if (n > 0)
    {
        temp2 = temp1->getNext();
        temp1->setNext(temp2->getNext());
        delete temp2;
    }
    else
    {
        removeFront();
    }
    length--;
}

// Note by Karl: Something allowed imperfect removal
/*
void LinkedList::removeNodeContaining(Tile d)
{
    Node *temp = head;

    if (temp != NULL)
    {
        int count = 0;
        while (temp != NULL)
        {
            if (temp->getData()->getColour() != d.getColour() || temp->getData()->getShape() != d.getShape())
            {

                temp = temp->getNext();
            }
            else
            {

                Node *temp1 = head;
                Node *temp2;
                int i;

                for (i = 0; i < count - 1; i++)
                {

                    temp1 = temp1->getNext();
                }
                if (count > 0)
                {
                    temp2 = temp1->getNext();
                    temp1->setNext(temp2->getNext());
                    delete temp2;
                }
                else
                {
                    removeFront();
                }
                return;
            }
            count++;
        }
    }
    length--;
}
*/

void LinkedList::removeNodeContaining(Tile *&tile)
{
    // 20220806
    // https://www.geeksforgeeks.org/linked-list-set-3-deleting-node/
    Node *temp = head;
    Node *prior = nullptr;

    if (temp != nullptr &&
        temp->getData()->getColour() == tile->getColour() &&
        temp->getData()->getShape() == tile->getShape())
    {
        // If head node's data matches tile data
        head = temp->getNext();
        delete temp;
        length--;
    }
    else
    {
        int count = 0;
        while (temp != nullptr &&
               (temp->getData()->getColour() != tile->getColour() ||
               temp->getData()->getShape() != tile->getShape()))
        {
            // Searching while either colour or shape mismatches
            count++;
            prior = temp;
            temp = temp->getNext();
        }

        if (temp == nullptr)
        {
            // Wasn't found
        }
        else
        {
            // You are the weakest link. Goodbye.
            prior->setNext(temp->getNext());
            delete temp;
            length--;
        }
    }
}

// 20220801
// https://www.geeksforgeeks.org/write-a-function-that-counts-the-number-of-times-a-given-int-occurs-in-a-linked-list/
int LinkedList::frequency(Tile *tile)
{
    int count = 0;
    Node *temp = head;
    Colour tileColour = tile->getColour();
    Shape tileShape = tile->getShape();

    while (temp != NULL)
    {
        Colour tempColour = temp->getData()->getColour();
        Shape tempShape = temp->getData()->getShape();

        if (tempColour == tileColour && tempShape == tileShape)
        {
            count++;
        }
        temp = temp->getNext();
    }
    return count;
}

Node *LinkedList::getHead()
{
    return head;
};
