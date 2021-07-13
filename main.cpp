// ====================================================================
// Name: Alex Chen
// Date  : 09 Nov 2020
// file name : main.cpp
// ====================================================================

#include "Playlist.h"
using namespace std;

// handle creation of the playlists
// display the create menu
void create();

// handle the modification or the playlists
// display the modify menu
void modify();


// ====================================================================
int main()
{
    int i;
    string s;

    PlayList::init();   // creat master playlist and init

    // the main loop
    while (true)
    {
        // the main memu
        cout << "MainMenu -----------------------" << endl;
        cout << "1 Create" << endl;
        cout << "2 Display" << endl;
        cout << "3 Modify" << endl;
        cout << "4 Delete" << endl;
        cout << "(Enter the number of the item. Any other number to quit)" << endl;
        cin >> i;

        if (i == 1) // the create menu
        {
            create();
        }
        else if (i == 2)    // to display a plalist
        {
            cout << "Enter Playlist Name:" << endl;
            cin >> s;

            // get the playlist
            PlayList* playlist = PlayList::getPlaylistByName( s );

            if (playlist != NULL)
                playlist->display();

            else
                cout << "Error: Playlist " << s << " cannot be found" << endl;
        }
        else if (i == 3)    // modify menu
        {
            modify();
        }
        else if (i == 4)  // delete a playlist
        {
            cout << "Enter Playlist Name:" << endl;
            cin >> s;
            PlayList::deletePlaylist( s );
        }
        else
        {
            break;
        }


    }

    PlayList::clear();  // delete all the playlists

#ifdef DEBUG
    cout << "programm successfully finished!" << endl;
#endif

    return 0;
}


// ====================================================================
void create()
{
    int i, j;
    char c;
    string s, s1;


    // display create menu
    cout << "1 Create Playlist by Rank" << endl;
    cout << "2 Create Playlist by Decade" << endl;
    cout << "3 Create Playlist by Performer type" << endl;
    cout << "4 Create Playlist by Genre" << endl;
    cout << "5 Create Playlist by Decade and Performer type" << endl;
    cout << "6 Create Playlist by Decade and the Genre" << endl;
    cout << "7 Create Playlist by Performer type and Genre" << endl;

    cout << "(Enter the number of the item. Any other number to go back)" << endl;
    cin >> i;

    if (i < 1 || i > 7) // go back
        return;

    cout << "Enter Playlist Name:" << endl;
    cin >> s;

    // handle the each case
    switch (i)
    {
        case 1:
            PlayList::createPlaylistByRanks( s );
            break;

        case 2:
            cout << "Enter the decade:" << endl;
            cin >> j;
            PlayList::createPlaylistByDecade( s, j );
            break;

        case 3:
            cout << "Enter the performer type:" << endl;
            cin >> c;
            PlayList::createPlaylistByPerformerType( s, c);
            break;

        case 4:
            cout << "Enter the genre:" << endl;
            cin >> s1;
            PlayList::createPlaylistByGenre( s, s1 );
            break;

        case 5:
            cout << "Enter the decade:" << endl;
            cin >> j;
            cout << "Enter the performer type:" << endl;
            cin >> c;
            PlayList::createPlaylistByDecadePerformer( s, j, c );
            break;

        case 6:
            cout << "Enter the decade:" << endl;
            cin >> j;
            cout << "Enter the genre:" << endl;
            cin >> s1;
            PlayList::createPlaylistByDecadeGenre( s, j, s1 );
            break;

        case 7:
            cout << "Enter the performer type:" << endl;
            cin >> c;
            cout << "Enter the genre:" << endl;
            cin >> s1;
            PlayList::createPlaylistByPerformerGenre( s, c, s1 );
            break;

        default:
            break;
    }
}


// ====================================================================
void modify()
{
    int i, j, k;
    char c;
    string s, s1;

    // the modify menu
    cout << "1 Insert song" << endl;
    cout << "2 delete song" << endl;

    cout << "(Enter the number of the item. Any other number to go back)" << endl;
    cin >> i;

    if (i < 1 || i > 2)
        return;

    cout << "Enter Playlist Name:" << endl;
    cin >> s;

    // get the play list
    PlayList* playlist = PlayList::getPlaylistByName( s );

    // playlist not valid
    if (playlist == NULL)
    {
        cout << "Error: Playlist " << s << " cannot be found" << endl;
        return;
    }

    if (i == 1) // to insert song to the playlist
    {
        cout << "Enter the rank of the song:" << endl;
        cin >> j;

        cout << "Enter the position of the song" << endl;
        cin >> k;

        if ( j < 1 || j > 200)  // check for the rank
        {
            cout << "Error: Invalid rank" << endl;
            return;
        }

        Song* song = PlayList::getPlaylistByName( "Master" )->getSongByRank( j );

        playlist->insertSong( song->copy(), k );
    }
    else    // to delete a song from the playlist
    {
        cout << "Enter the position of the song" << endl;
        cin >> k;

        playlist->deleteSong( k );
    }
}
