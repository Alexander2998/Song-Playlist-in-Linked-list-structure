// ====================================================================
// Name: Alex Chen
// Date  : 09 Nov 2020
// file name : PlayList.cpp
// ====================================================================
#include "PlayList.h"

PlayList* PlayList::master_playlist = NULL;
PlayList* PlayList::playlists[MAX_PLAYLISTS];
int PlayList::n_playlists = 0;


// ====================================================================
PlayList::PlayList( string name_ ) : name(name_), head(NULL), n_songs(0)
{

}


// ====================================================================
PlayList::~PlayList()
{
    Song* node = head;

    while (node != NULL)
    {
        Song* temp = node->getNext();
        delete node;
        node = temp;
    }
}


// ====================================================================
string PlayList::getName()
{
    return name;
}


// ====================================================================
void PlayList::insertSong( Song* song, int position = -1 )
{
    Song* node = head;
    Song* temp;

    if (position == -1) position = n_songs + 1;

    if (position < 1 || position > n_songs + 1)
    {
        cerr << "Error: incorrect song position for the playlist "
             << name << endl;
        return;
    }

    n_songs++;


    if (position == 1)
    {
        temp = head;
        head = song;
        song->setNext( temp );
        return;
    }

    for (int i = 0;  i < position - 2; i++)
        node = node->getNext();


    temp = node->getNext();

    node->setNext( song );
    song->setNext( temp );
}


// ====================================================================
void PlayList::deleteSong( int position )
{
    if (position < 1 || position > n_songs )
    {
        cerr << "Error: incorrect song position for the playlist "
             << name << endl;
        return;
    }

    Song* node = head;
    Song* temp;

    n_songs--;

    if (position == 1)
    {
        temp = head->getNext();
        delete head;
        head = temp;
        return;
    }

    for (int i = 0;  i < position - 2; i++)
        node = node->getNext();


    temp = node->getNext()->getNext();
    delete node->getNext();
    node->setNext( temp );
}


// ====================================================================
Song* PlayList::getSongByRank( int rank )
{
    Song* song = head;

    while (true)
    {
        if (song == NULL)
            break;

        if (song->getRank() == rank)
            return song;

        song = song->getNext();
    }

    return NULL;
}


// ====================================================================
void PlayList::display()
{
    Song* node = head;
    int i = 1;

    while (node != NULL)
    {
        cout << i << ") ";
        node->printDetails();
        cout << endl;
        i++;
        node = node->getNext();
    }
}


// ====================================================================
int PlayList::count()
{
    return n_songs;
}


// ====================================================================
void PlayList::init()
{
    createMasterPlayList( "billboard_200.txt" );
    n_playlists = 0;

    // go to each playlist and delete
    for (int i = 0; i < MAX_PLAYLISTS; i++)
        playlists[i] = NULL;
}


// ====================================================================
void PlayList::clear()
{
    // delete master playlist
    if (master_playlist != NULL)
        delete master_playlist;

    // go to each playlist and delete
    for (int i = 0; i < MAX_PLAYLISTS; i++)
        if (playlists[i] != NULL)
            delete playlists[i];
}


// ====================================================================
void PlayList::createMasterPlayList( string file_path )
{
    assert( master_playlist == NULL);

    master_playlist = new PlayList( "Master" );

    ifstream fs(file_path);
    string line, name, artist_name, genre;
    char performer_type;
    int year, rank;
    Song* song;
    int i = 0;

    if (fs.is_open())
    {
        // read the file line by line and get the relevent data
        // (name, artist name)
        while (getline(fs, line))
        {
            // determine the field by i
            switch (i)
            {
                case 0:
                    name = line;
                    break;

                case 1:
                    artist_name = line;
                    break;

                case 2:
                    rank = stoi( line );
                    break;

                case 3:
                    year = stoi( line );
                    break;

                case 4:
                    performer_type = line[0];
                    break;

                case 5:
                    genre = line;
                    // create and add the song to the playlist
                    song = new Song( name, artist_name, rank, year,
                                      genre, performer_type );
                    master_playlist->insertSong( song );
                    i = -1;
                    break;

                default:
                    break;

            }
            i++;
        }

        fs.close();
    }
    else
    {
        cerr << "Error: could not open the file." << endl;
    }

}


// ====================================================================
PlayList* PlayList::getPlaylistByName( string name )
{
    // get the master playlist
    if (master_playlist != NULL && name == "Master")
        return master_playlist;

    // linear search for the playlist name
    for (int i = 0; i < MAX_PLAYLISTS; i++)
    {
        if (playlists[i] != NULL)
        {
            if (playlists[i]->getName() == name )
            {
                return playlists[i];
            }
        }
    }

    return NULL;
}


// ====================================================================
PlayList* PlayList::createPlaylist( string name )
{
     // check for maximum number of playlists
    if (n_playlists == MAX_PLAYLISTS)
    {
        cout << "Error: Number of maximum playlist has reached." << endl;
        return NULL;
    }

    // name of the playlist must be unique
    if (getPlaylistByName( name ) != NULL)
    {
        cout << "Error: Playlist name " << name << " already exist." << endl;
        return NULL;
    }

    int empty = -1;

    // find an empty slot in the playlists array
    for (int i = 0; i < MAX_PLAYLISTS; i++)
    {
        if (playlists[i] == NULL)
        {
            empty = i;
            break;
        }
    }

#ifdef DEBUG
    assert( empty >= 0 && empty < MAX_PLAYLISTS );
#endif

    playlists[empty] = new PlayList( name );
    n_playlists++;

    return playlists[empty];
}


// ====================================================================
void PlayList::deletePlaylist( string name )
{
    if (name == "Master" )
    {
        cout << "Error: Cannot delete the master playlist" << endl;
        return;
    }

    for (int i = 0; i < MAX_PLAYLISTS; i++)
    {
        if (playlists[i] != NULL)
        {
            if (playlists[i]->getName() == name)
            {
                delete playlists[i];
                playlists[i] = NULL;
                n_playlists--;
                return;
            }
        }
    }

    cout << "Error: Playlist " << name << " cannot be found" << endl;
}

// ====================================================================
void PlayList::createPlaylistByRanks( string name )
{
    // create the playlist
    PlayList* playlist;

    if ((playlist = createPlaylist( name )) == NULL)
        return;

    int rank;

    // get user input ranks one by one
    while (true)
    {
        cout << "Enter the rank of the song: " << endl;
        cin >> rank;

        if (rank == -1)
            break;

        // check for the range
        if(rank > 0 && rank <= 200)
        {
            Song* song = master_playlist->getSongByRank( rank );

            // chekc if the song alread in the play list
            if (playlist->getSongByRank( rank ) == NULL)
                playlist->insertSong( song->copy() );

            else
                cout << "Error: Song already exists." << endl;

        }
        else
            cout << "Error: Invalid rank" << endl;

    }
}


// ====================================================================
void PlayList::createPlaylistByDecade( string name, int decade )
{
    assert( master_playlist != NULL );

    // create the playlist
    PlayList* playlist;

    if ((playlist = createPlaylist( name )) == NULL)
        return;

    Song* node = master_playlist->head;

    // search the master play list and add the song of the decade
    while(true)
    {
        if (node == NULL)
            break;

        if (node->getDecade() == decade)
            playlist->insertSong( node->copy() );

        node = node->getNext();
    }
}


// ====================================================================
void PlayList::createPlaylistByPerformerType( string name,
                                              char performer_type )
{
    assert( master_playlist != NULL );

    // create the playlist
    PlayList* playlist;

    if ((playlist = createPlaylist( name )) == NULL)
        return;

    Song* node = master_playlist->head;


    while(true)
    {
        if (node == NULL)
            break;

        if (node->getPerformerType() == performer_type)
            playlist->insertSong( node->copy() );

        node = node->getNext();
    }
}


// ====================================================================
void PlayList::createPlaylistByGenre( string name, string genre )
{
    assert( master_playlist != NULL );

    // create the playlist
    PlayList* playlist;

    if ((playlist = createPlaylist( name )) == NULL)
        return;

    Song* node = master_playlist->head;


    while(true)
    {
        if (node == NULL)
            break;

        if (node->getGenre() == genre)
            playlist->insertSong( node->copy() );

        node = node->getNext();
    }
}

void PlayList::createPlaylistByDecadePerformer( string name, int decade,
                                                char performer_type )
{

    assert( master_playlist != NULL );

    // create the playlist
    PlayList* playlist;

    if ((playlist = createPlaylist( name )) == NULL)
        return;

    Song* node = master_playlist->head;


    while(true)
    {
        if (node == NULL)
            break;

        if (node->getDecade() == decade &&
            node->getPerformerType() == performer_type)

            playlist->insertSong( node->copy() );

        node = node->getNext();
    }
}


// create a playlist for given decade and genre
void PlayList::createPlaylistByDecadeGenre( string name, int decade,
                                            string genre )
{
    assert( master_playlist != NULL );

    // create the playlist
    PlayList* playlist;

    if ((playlist = createPlaylist( name )) == NULL)
        return;

    Song* node = master_playlist->head;


    while(true)
    {
        if (node == NULL)
            break;

        if (node->getDecade() == decade &&
            node->getGenre() == genre)

            playlist->insertSong( node->copy() );

        node = node->getNext();
    }
}

// create a playlist for  performer type and genre
void PlayList::createPlaylistByPerformerGenre( string name, char performer_type,
                                                    string genre )
{
    assert( master_playlist != NULL );

    // create the playlist
    PlayList* playlist;

    if ((playlist = createPlaylist( name )) == NULL)
        return;

    Song* node = master_playlist->head;


    while(true)
    {
        if (node == NULL)
            break;

        if (node->getPerformerType() == performer_type &&
            node->getGenre() == genre)

            playlist->insertSong( node->copy() );

        node = node->getNext();
    }
}

