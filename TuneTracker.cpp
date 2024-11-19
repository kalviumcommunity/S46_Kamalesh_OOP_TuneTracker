#include <iostream>
#include <string>
using namespace std;

// Base class
class Media {
protected:
    string name;

public:
    string getName() const {
        return name;
    }
    void setName(string n) {
        name = n;
    }
};

// Derived class Song
class Song : public Media {
private:
    string title;
    string artist;
    string genre;
    bool isFavorite;
    
    static int totalSongs;

public:
    // Default constructor
    Song() {
        totalSongs++;
    }

    // Parameterized constructor
    Song(string t, string a, string g) : title(t), artist(a), genre(g), isFavorite(false) {
        totalSongs++;
        setName(t); // from the base class
    }

    // Destructor
    ~Song() {
        cout << "Destructor called for Song: " << title << endl;
    }

    static int getTotalSongs() {
        return totalSongs;
    }

    void setData(string t, string a, string g) {
        this->title = t;
        this->artist = a;
        this->genre = g;
        this->isFavorite = false;
        setName(t); //from the base class
    }

    string getTitle() const {
        return title;
    }

    string getArtist() const {
        return artist;
    }

    string getGenre() const {
        return genre;
    }

    bool getIsFavorite() const {
        return isFavorite;
    }

    void markAsFavorite() {
        isFavorite = true;
    }

    void unmarkAsFavorite() {
        isFavorite = false;
    }
};

int Song::totalSongs = 0;  // Initialize the static variable

// Derived class Playlist
class Playlist : public Media {
private:
    Song** songs;
    int songCount;
    
    static int totalPlaylists; 

public:
    // Default constructor
    Playlist() : songCount(0) {
        songs = new Song*[10];
        totalPlaylists++;
    }

    // Parameterized constructor
    Playlist(string n) : songCount(0) {
        setName(n); // Using the base class method
        songs = new Song*[10];
        totalPlaylists++;
    }

    // Destructor
    ~Playlist() {
        for (int i = 0; i < songCount; i++) {
            delete songs[i];
        }
        delete[] songs;
        cout << "Destructor called for Playlist: " << getName() << endl;
    }

    static int getTotalPlaylists(){
        return totalPlaylists;
    }

    void addSong(Song* song) {
        if (songCount < 100) {
            songs[songCount] = song;
            songCount++;
        } else {
            cout << "Playlist is full!" << endl;
        }
    }

    void removeSong(string title) { 
        for (int i = 0; i < songCount; i++) {
            if (songs[i]->getTitle() == title) {
                delete songs[i];
                for (int j = i; j < songCount - 1; j++) {
                    songs[j] = songs[j + 1];
                }
                songCount--;
                break;
            }
        }
    }

    void displaySongs() const {
        for (int i = 0; i < songCount; i++) {
            cout << songs[i]->getTitle() << " by " << songs[i]->getArtist() << endl;
        }
    }
};

int Playlist::totalPlaylists = 0;  // Initialize the static variable

class Library
{
private:
    Song** songs;        // Fixed array of songs
    Playlist** playlists; // Fixed array of playlists
    int songCount;
    int playlistCount;
    
    static int totalLibraries;

public:

    //Default Constructor
    Library()
    {
        songCount = 0;
        playlistCount = 0;
        songs = new Song*[100];
        playlists = new Playlist*[10];
        totalLibraries++;
    }

    // Destructor
    ~Library() {
        for (int i = 0; i < songCount; i++) {
            delete songs[i];
        }
        delete[] songs;

        for (int i = 0; i < playlistCount; i++) {
            delete playlists[i];
        }
        delete[] playlists;

        cout << "Destructor called for Library" << endl;
    }
    
    static int getTotalLibraries(){
        return totalLibraries;
    }

    void addSong(Song* song)
    { 
        if (songCount < 100)
        {
            songs[songCount] = song;
            songCount++;
        }
        else
        {
            cout << "Library is full!" << endl;
        }
    }

    void createPlaylist(string name)
    { 
        if (playlistCount < 10)
        {
            playlists[playlistCount] = new Playlist();
            playlists[playlistCount]->setName(name);
            playlistCount++;
        }
        else
        {
            cout << "Cannot create more playlists!" << endl;
        }
    }

    void addSongToPlaylist(string playlistName, Song* song)
    { 
        for (int i = 0; i < playlistCount; i++)
        {
            if (playlists[i]->getName() == playlistName)
            {
                playlists[i]->addSong(song);
                break;
            }
        }
    }

    void displayLibrary() const
    {
        for (int i = 0; i < songCount; i++)
        {
            cout << songs[i]->getName() << " by " << songs[i]->getArtist() << " [" << songs[i]->getGenre() << "]" << endl;
        }
    }

    void displayPlaylists() const
    {
        for (int i = 0; i < playlistCount; i++)
        {
            cout << "Playlist: " << playlists[i]->getName() << endl;
            playlists[i]->displaySongs();
        }
    }

    void displayFavorites() const
    {
        for (int i = 0; i < songCount; i++)
        {
            if (songs[i]->getIsFavorite())
            {
                cout << songs[i]->getTitle() << " by " << songs[i]->getArtist() << endl;
            }
        }
    }
};

int Library::totalLibraries = 0;  // Initialize the static variable

int main()
{
    Library library;

    Song* song1 = new Song();
    Song* song2 = new Song();
    Song* song3 = new Song();
    
    song1->setData("Song 1", "Artist 1", "Rock");
    song2->setData("Song 2", "Artist 2", "Pop");
    song3->setData("Song 3", "Artist 1", "Jazz");

    song1->markAsFavorite();

    library.addSong(song1);
    library.addSong(song2);
    library.addSong(song3);

    library.createPlaylist("Playlist1");
    library.addSongToPlaylist("Playlist1", song1);

    cout << "Music Library:\n";
    library.displayLibrary();

    cout << "\nPlaylists:\n";
    library.displayPlaylists();

    cout << "\nFavorites:\n";
    library.displayFavorites();
    

    cout << "\nTotal Songs: " << Song::getTotalSongs() << endl;
    cout << "Total Playlists: " << Playlist::getTotalPlaylists() << endl;
    cout << "Total Libraries: " << Library::getTotalLibraries() << endl;

    return 0;
}
