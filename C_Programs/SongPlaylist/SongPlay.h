/*******************************************************************************************************************************/ /**
 *
 *  @file       SongPlay.h
 *  @version    0.0.1
 *  @author     Ravdeep Singh Boparai
 *  @date       2020-05-21
 *  @brief      API to handle songs using Dynamic List
 *
 ***********************************************************************************************************************************
 *  @note  
 *  Playlist REQUIREMENTS
 * -----------------------------------------------------
 *  init songs  --> arr with name + popularity
 *  add song    --> name +  popularity
 *  delete song --> name 
 *  next song   --> random song from the list and delete it
 *
 *  Algorthim 
 * -----------------------------------------------------
 *  Probability is proportional to popularity.
 *  A - popularity 5
 *  B - popularity 1
 *  [A,A,A,A,A,B]
 *  Method 1:
 *  PICK RANDOMLY WITH WEIGTH
 *  A
 *  A
 *  B
 *  A
 *  A
 *  A
 * Method 2:
 * a) Sum all the weights
 * b) Compute random number between 0 to weights
 * c) subtracting popularity of each song from random till it is less than popularity of that song (weight random algorthm)
 * 
 * 
 * 
 *
 **********************************************************************************************************************************/
#ifndef SONG_PLAYLIST_H
#define SONG_PLAYLIST_H

/***********************************************************************************************************************************
 *  Include
 **********************************************************************************************************************************/
#include "stdbool.h"
/***********************************************************************************************************************************
 *  Public Constants and Macros
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *  Public Data Declarations
 **********************************************************************************************************************************/
// Struct for holding Song information
typedef struct Song_s
{
    char *name;
    int popularity;
} Song_ts;

// Linked list for holding list of songs
typedef struct SongList_s
{
    Song_ts *Song;
    struct SongList_s *next;
} SongList_ts;
/***********************************************************************************************************************************
 *  Public Functions Prototypes
 **********************************************************************************************************************************/

/***************************************************************************/ /**
 * @brief           SongPlaylist_Init
 *                  Dynamically allocate for songs and call AddSong.
 * 
 * @param           pArrOfSongs: Pointer to Array Struct of each song.
 *                  SizeOfList:  Size of the song list.
 * 
 * @return           Pointer to the Song List.
 ******************************************************************************/
SongList_ts *SongList_Init(Song_ts *pArrOfSongs, int SizeOfList);

/***************************************************************************/ /**
 * @brief           SongList_AddSong
 *                  Add Song into the Song Playlist.
 * 
 * @param           ppSongList_head: Pointer to pointer of the Song List.
 *                  pSong: Dynamically Allocated Structure.
 * 
 * @return          True if song successfully added otherwise false.
 ******************************************************************************/
bool SongList_AddSong(SongList_ts **ppSongList_head, Song_ts *pSong);

/***************************************************************************/ /**
 * @brief           SongList_DeleteSong
 *                  Delete Song from the Song Playlist.
 * 
 * @param           ppSongList_head: Pointer to pointer of the Song List.
 *                  pSongName: Pointer to name of the Song to be Deleted. 
 * 
 * @return          True if song successfully deleted otherwise false.
 ******************************************************************************/
bool SongList_DeleteSong(SongList_ts **ppSongList_head, char *pSongName);

/***************************************************************************/ /**
 * @brief           SongList_PrintList
 *                  Print Songs from the Song Playlist.
 * 
 * @param           pSongList_head: Pointer to the Song List.
 * 
 * @return          None
 ******************************************************************************/
void SongList_PrintList(SongList_ts *pSongList_head);

/***************************************************************************/ /**
 * @brief           SongList_PlaySong
 *                  Play Song from the Song Playlist and delete it.
 * 
 * @param           ppSongList_head: Pointer to pointer of the Song List.
 *                  rSongName: Pointer to buffer to store Name of the Song.
 * 
 * @return          Pointer to the Song name.
 ******************************************************************************/
char *SongList_PlaySong(SongList_ts **ppSongList_head, char *rSongName);

/***************************************************************************/ /**
 * @brief           SongList_AllocateSong
 *                  Allocates memory for Song and can only be deleted via Delete.
 * 
 * @param           pSongName: Pointer to the Song Name.
 *                  popularity: Popularity of the Song.
 * 
 * @return          Pointer to the Song memory to be added into list.
 ******************************************************************************/
Song_ts *SongList_AllocateSong(char *pSongName, int popularity);

#endif //SONG_PLAYLIST_H
