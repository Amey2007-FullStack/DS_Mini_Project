#include<iostream>
#include<string>
using namespace std;

class Node
{
    private:
        int songID;
        string songName;

        Node* next;
        Node* prev;

    public:
        // Parameterized Constructor
        Node(int id, string name)
        {
            songID = id;
            songName = name;
            next = NULL;
            prev = NULL;
        }

        // Allow Playlist class to access private members
        friend class Playlist;
};

class Playlist
{
    private:
        Node* head;
        Node* tail;
        Node* current;

    public:
    
        Playlist()
        {
            head = nullptr;
            tail = nullptr;
            current = nullptr;
        }

        
        void addSong()
        {
            int id;
            string name;

            cout << "Enter Song ID: ";
            cin >> id;

            cout << "Enter Song Name: ";
            cin.ignore();
            getline(cin, name);

            // Check for duplicate Song ID
            Node* temp = head;
            while(temp != nullptr)
            {
                if(temp->songID == id)
                {
                    cout << "Song ID already exists!" << endl;
                    return;
                }
                temp = temp->next;
            }

            
            Node* newNode = new Node(id, name);

            // If playlist is empty
            if(head == nullptr)
            {
                head = newNode;
                tail = newNode;
                current = newNode;
            }
            else
            {
                tail->next = newNode;
                newNode->prev = tail;
                tail = newNode;
            }

            cout << "Song added successfully!" << endl;
        }

        void displayPlaylist()
        {
            
            if(head == nullptr)
            {
                cout << "\nPlaylist is empty!" << endl;
                return;
            }

            Node* temp = head;

            cout << "\n========== PLAYLIST ==========" << endl;

            while(temp != nullptr)
            {
                cout << "Song ID   : " << temp->songID << endl;
                cout << "Song Name : " << temp->songName << endl;
                cout << "-----------------------------" << endl;

                temp = temp->next;
            }
        }

        void deleteSong()
        {
            if(head == nullptr)
            {
                cout << "Playlist is empty!" << endl;
                return;
            }

            int id;
            cout << "Enter Song ID to delete: ";
            cin >> id;

            Node* temp = head;

            while(temp != nullptr && temp->songID != id)
            {
                temp = temp->next;
            }

            if(temp == nullptr)
            {
                cout << "Song not found!" << endl;
                return;
            }

            // Case 1: Only one song
            if(head == tail)
            {
                head = nullptr;
                tail = nullptr;
                current = nullptr;
            }

            // Case 2: First song
            else if(temp == head)
            {
                head = head->next;
                head->prev = nullptr;

                if(current == temp)
                    current = head;
            }

            // Case 3: Last song
            else if(temp == tail)
            {
                tail = tail->prev;
                tail->next = nullptr;

                if(current == temp)
                    current = tail;
            }

            // Case 4: Middle song
            else
            {
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;

                if(current == temp)
                    current = temp->next;
            }

            delete temp;

            cout << "Song deleted successfully!" << endl;
        }

        void playMusic()
        {
            if(head == nullptr)
            {
                cout << "Playlist is empty!" << endl;
                return;
            }

            int choice;

            do
            {
                cout << "\n====== NOW PLAYING ======" << endl;
                cout << "Song: " << current->songName << endl;
                cout << "(ID: " << current->songID <<")" << endl;
                
                cout << "\n1. Next Song";
                cout << "\n2. Previous Song";
                cout << "\n3. Exit Player";
                cout << "\nEnter your choice: ";
                cin >> choice;

                switch(choice)
                {
                    case 1:
                        if(current->next != nullptr)
                        {
                            current = current->next;
                        }
                        else
                        {
                            cout << "This is the last song." << endl;
                        }
                        break;

                    case 2:
                        if(current->prev != nullptr)
                        {
                            current = current->prev;
                        }
                        else
                        {
                            cout << "This is the first song." << endl;
                        }
                        break;

                    case 3:
                        cout << "Exiting Music Player..." << endl;
                        break;

                    default:
                        cout << "Invalid Choice!" << endl;
                }

            } while(choice != 3);
        }
};


int main()
{
    Playlist playlist;
    int n, choice;

    cout << "=========================================" << endl;
    cout << "     MUSIC PLAYLIST MANAGEMENT SYSTEM    " << endl;
    cout << "=========================================" << endl;

    cout << "\nCreate Your Playlist" << endl;
    cout << "Enter the number of songs: ";
    cin >> n;

    for(int i = 1; i <= n; i++)
    {
        cout << "\nEnter details of Song " << i << endl;
        playlist.addSong();
    }

    cout << "\nPlaylist created successfully!" << endl;

    do
    {
        cout << "\n=========================================" << endl;
        cout << "              MAIN MENU                  " << endl;
        cout << "=========================================" << endl;
        cout << "1. Add Song" << endl;
        cout << "2. Delete Song" << endl;
        cout << "3. Display Playlist" << endl;
        cout << "4. Play Music" << endl;
        cout << "5. Exit" << endl;

        cout << "\nEnter your choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1:
                playlist.addSong();
                break;

            case 2:
                playlist.deleteSong();
                break;

            case 3:
                playlist.displayPlaylist();
                break;

            case 4:
                playlist.playMusic();
                break;

            case 5:
                cout << "\nThank you for using Music Playlist Management System!" << endl;
                break;

            default:
                cout << "\nInvalid Choice! Please try again." << endl;
        }

    } while(choice != 5);

    return 0;
}