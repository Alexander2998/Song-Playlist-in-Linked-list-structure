// ====================================================================
// Name: Alex Chen
// Date  : 09 Nov 2020
// file name : PlayList.h
// ====================================================================

#ifndef _PLAYLIST_H
#define _PLAYLIST_H

#include "Song.h"
#include <cassert>
#include <fstream>

using namespace std;

// ====================================================================
class PlayList
{
    public: // public functions

        // constructor
        PlayList( string name_ );

        // destructor
        ~PlayList();

        // getter of name
        string getName();

        // add an song to a list (at the end)
        // position = -1 means inster at the end
        void insertSong( Song* song, int position );

        // delete the song at the given position
        void deleteSong( int position );

        // get the reference to the song of by rank
        Song* getSongByRank( int rank );

        // display details of all the songs
        void display();

        // get the number of the songs in the list
        int count();

        // initialize the master playlist
        static void init();

        // clear all the playlist including master play list
        static void clear();

        // get the play list by the name
        // return NULL if not found
        static PlayList* getPlaylistByName( string name );

        // create a playlist return null if if cannot created
        static PlayList* createPlaylist( string name );

        // delete the playlist of given name
        static void deletePlaylist( string name );

        // create the playlist by the getting rank inputs from the user
        // name = name of the play list
        static void createPlaylistByRanks( string name );

        // creates a play list of given decade
        static void createPlaylistByDecade( string name, int decade );

        // create a playlist songs from the given decades
        static void createPlaylistByPerformerType( string name,
                                                   char performer_type );

        // create a play list of songs for the give genre
        static void createPlaylistByGenre( string name, string genre );

        // create a playlist for given decade and performer type
        static void createPlaylistByDecadePerformer( string name, int decade,
                                                    char performer_type );

        // create a playlist for given decade and genre
        static void createPlaylistByDecadeGenre( string name, int decade,
                                                 string genre );

        // create a playlist for  performer type and genre
        static void createPlaylistByPerformerGenre( string name, char performer_type,
                                                    string genre );




    private: // pirvate functions

         // create a master playlist from the given file
        // only calls once
        static void createMasterPlayList( string file_path );


    public: // public variables

        // number of maximum play lists
        static const int MAX_PLAYLISTS = 5;



    private: // private variables

        // the name of the playlist
        string name;

        // head of the liked list
        Song* head;

        // number of songs in the list
        int n_songs;

        // the master playlist
        static PlayList* master_playlist;

        // the array of play lists
        static PlayList* playlists[MAX_PLAYLISTS];

        // number of current playlists (excluding master playlist)
        static int n_playlists;
};
#endif
