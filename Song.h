// ====================================================================
// Name: Alex Chen
// Date  : 09 Nov 2020
// file name : Song.h
// ====================================================================
#ifndef SONG_H
#define SONG_H


#include <string>
#include <iostream>
using namespace std;

// ====================================================================
// the song class declarations
class Song
{
    public: // public funtions

        // constructor
        Song();

        // constructor
        Song( string song_name_, string artist_name_, int rank_,
              int year_, string genre_, char performer_type_ );

        // destructor
        ~Song();

        // create a copy of object
        Song* copy();

        // print the details of the object
        void printDetails();

        // getters
        string getSongName();
        string getArtistName();
        int getRank();
        int getYear();
        string getGenre();
        char getPerformerType();
        int getDecade();
        Song* getNext();

        // setters
        void setSongName( string song_name_ );
        void setArtistName( string artist_name_ );
        void setRank( int rank_ );
        void setYear( int year_ );
        void setGenre( string genre_ );
        void setPerformerType( char performer_type );
        void setDecade( int decade );
        void setNext( Song* next_ );


    private: // private functions

        // return the decade of the year
        static int getDecade( int year );


    private: // private variables
        // name of the song
        string song_name;

        // name of the artist
        string artist_name;

        // rank on the top 200 list
        int rank;

        // the year released
        int year;

        // the decade released
        int decade;

        // latin-jazz
        // country
        // hip-hop
        // dance
        // r&b
        // pop
        // rock
        string genre;

        // M = male
        // F = female
        // D = duet / group
        char performer_type;

        // the next song of the play list
        // null if the end of the playlist
        Song* next;
};

#endif // SONG_H
