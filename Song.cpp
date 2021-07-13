// ====================================================================
// Name: Alex Chen
// Date  : 09 Nov 2020
// file name : Song.cpp
// ====================================================================
#include "Song.h"

Song::Song() :
    song_name(""),
    artist_name(""),
    rank(-1),
    year(0),
    genre("pop"),
    performer_type('M'),
    next(NULL),
    decade(0)
{

}


// ====================================================================
Song::Song( string song_name_, string artist_name_, int rank_,
            int year_, string genre_, char performer_type_ ) :
        song_name(song_name_),
        artist_name(artist_name_),
        rank(rank_),
        year(year_),
        genre(genre_),
        performer_type(performer_type_),
        next(NULL)
{
    decade = getDecade( year );
}


// ====================================================================
Song::~Song()
{
    // do nothing
}

// ====================================================================
Song* Song::copy()
{
    Song* song = new Song();
    *song = *this;
    return song;
}

// ====================================================================
void Song::printDetails()
{
    string performer_type_str;
    switch (performer_type)
    {
        case 'M':
            performer_type_str = "Male";
            break;

        case 'F':
            performer_type_str = "Female";
            break;

        case 'D':
            performer_type_str = "Duo or Group";
            break;

        default:
            break;
    }

    cout << "(" << rank << ") " << song_name << "(" << genre << ")"
            << " by " << artist_name <<
            "(" << performer_type_str << ")" <<  " in " << year;
}

// ====================================================================
int Song::getDecade( int year )
{
    if (year >= 1920 && year < 2000)
        return 10 * ((year - 1900) / 10);

    else if( year >= 2000 && year < 2020)
        return 10 * ((year - 2000) / 10);

    return -1;
}


// ====================================================================
string Song::getSongName()
{
    return song_name;
}

// ====================================================================
string Song::getArtistName()
{
    return artist_name;
}

// ====================================================================
int Song::getRank()
{
    return rank;
}

// ====================================================================
int Song::getYear()
{
    return year;
}

// ====================================================================
string Song::getGenre()
{
    return genre;
}

// ====================================================================
char Song::getPerformerType()
{
    return performer_type;
}

// ====================================================================
int Song::getDecade()
{
    return decade;
}


// ====================================================================
Song* Song::getNext()
{
    return next;
}


// ====================================================================
void Song::setSongName( string song_name_ )
{
    song_name = song_name_;
}


// ====================================================================
void Song::setArtistName( string artist_name_ )
{
    artist_name = artist_name_;
}


// ====================================================================
void Song::setRank( int rank_ )
{
    rank = rank_;
}


// ====================================================================
void Song::setYear( int year_ )
{
    year = year_;
}


// ====================================================================
void Song::setGenre( string genre_ )
{
    genre = genre_;
}


// ====================================================================
void Song::setPerformerType( char performer_type_ )
{
    performer_type = performer_type_;
}


// ====================================================================
void Song::setDecade( int decade_ )
{
    decade = decade_;
}

// ====================================================================
void Song::setNext( Song* next_ )
{
    next = next_;
}


