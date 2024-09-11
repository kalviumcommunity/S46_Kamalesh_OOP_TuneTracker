#include <iostream>
#include <string>
using namespace std;

class Song
{
private:
    string title;
    string artist;
    string genre;
    bool isFavorite;

public:
    void setData(string t, string a, string g)
    {
        this->title = t;
        this->artist = a;
        this->genre = g;
        this->isFavorite = false;
    }

    string getTitle() const
    {
        return title;
    }

    string getArtist() const
    {
        return artist;
    }

    string getGenre() const
    {
        return genre;
    }

    bool getIsFavorite() const
    {
        return isFavorite;
    }

    void markAsFavorite()
    {
        isFavorite = true;
    }

    void unmarkAsFavorite()
    {
        isFavorite = false;
    }
};

class Playlist
{
private:
    string name;
    Song** songs;
    int songCount;

public:
    Playlist() : songCount(0) {
        songs = new Song*[10];
    }

    void setName(string n)
    {
        this->name = n;
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
            cout << "Playlist is full!" << endl;
        }
    }

    void removeSong(string title)
    { 
        for (int i = 0; i < songCount; i++)
        {
            if (songs[i]->getTitle() == title)
            {
                delete songs[i];
                for (int j = i; j < songCount - 1; j++)
                {
                    songs[j] = songs[j + 1];
                }
                songCount--;
                break;
            }
        }
    }

    void displaySongs() const
    {
        for (int i = 0; i < songCount; i++)
        {
            cout << songs[i]->getTitle() << " by " << songs[i]->getArtist() << endl;
        }
    }

    string getName() const
    {
        return name;
    }
};

class Library
{
private:
    Song** songs;        // Fixed array of songs
    Playlist** playlists; // Fixed array of playlists
    int songCount;
    int playlistCount;

public:
    Library()
    {
        songCount = 0;
        playlistCount = 0;
        songs = new Song*[100];
        playlists = new Playlist*[10];
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
            cout << songs[i]->getTitle() << " by " << songs[i]->getArtist() << " [" << songs[i]->getGenre() << "]" << endl;
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

    return 0;
}
