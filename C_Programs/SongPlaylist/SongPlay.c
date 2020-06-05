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
/***********************************************************************************************************************************
 *  Include
 **********************************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SongPlay.h"

/***********************************************************************************************************************************
 *  Public Function Bodies
 **********************************************************************************************************************************/
/***************************************************************************/ /**
 * @brief           SongList_AllocateSong
 *                  Allocates memory for Song and can only be deleted via Delete.
 * 
 * @param           pSongName: Pointer to the Song Name.
 *                  popularity: Popularity of the Song.
 * 
 * @return          Pointer to the Song memory to be added into list.
 ******************************************************************************/
Song_ts *SongList_AllocateSong(char *pSongName, int popularity)
{
    /* Allocate for the memory */
    Song_ts *pSong = (Song_ts *)malloc(sizeof(Song_ts));
    pSong->name = (char *)malloc(strlen(pSongName)+1);

    /* Set the name and the popularity in the struct and null terminate the string. */
    strcpy(pSong->name, pSongName);
    pSong->name[strlen(pSongName)] = '\0';
    pSong->popularity = popularity;
}
/***********************************************************************************************************************************
 *  Public Function Bodies
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
SongList_ts *SongList_Init(Song_ts *pArrOfSongs, int SizeOfList)
{
    SongList_ts *pSongList_head = NULL;

    /* Loop all the elements of array*/
    while (SizeOfList--)
    {
        /* Safety Check */
        if (pArrOfSongs == NULL)
            break;

        /* Allocate Memory for Each item and also for name + 1 to include null termination */
        Song_ts *pSong = SongList_AllocateSong(pArrOfSongs->name, pArrOfSongs->popularity);

        /* Add to the list */
        SongList_AddSong(&pSongList_head, pSong);

        pArrOfSongs++;
    }

    return pSongList_head;
}

/***************************************************************************/ /**
 * @brief           SongList_AddSong
 *                  Add Song into the Song Playlist.
 * 
 * @param           ppSongList_head: Pointer to pointer of the Song List.
 *                  pSong: Dynamically Allocated Structure.
 * 
 * @return          True if song successfully added otherwise false.
 ******************************************************************************/
bool SongList_AddSong(SongList_ts **ppSongList_head, Song_ts *pSong)
{
    /* Allocate new song */
    SongList_ts *new_song = (SongList_ts *)malloc(sizeof(SongList_ts));
    if (new_song == NULL)
        return false;

    /* Put in the Song  */
    new_song->Song = pSong;

    /* Make next of new song as head of the list since we are pushing songs to the list */
    new_song->next = (*ppSongList_head);

    /* Move the head to point to the new song added */
    (*ppSongList_head) = new_song;
    return true;
}
/***************************************************************************/ /**
 * @brief           SongList_DeleteSong
 *                  Delete Song from the Song Playlist.
 * 
 * @param           ppSongList_head: Pointer to pointer of the Song List.
 *                  pSongName: Pointer to name of the Song to be Deleted. 
 * 
 * @return          True if song successfully deleted otherwise false.
 ******************************************************************************/
bool SongList_DeleteSong(SongList_ts **ppSongList_head, char *pSongName)
{
    if (ppSongList_head == NULL)
        return false;

    /* Store head to the list */
    SongList_ts *temp = *ppSongList_head, *prev;

    /* If head pointer itself holds the song to be deleted */
    if (temp != NULL && (!strcmp(temp->Song->name, pSongName)))
    {
        *ppSongList_head = temp->next; // Changed head pointer
        free(temp->Song->name);
        free(temp->Song);
        free(temp); // free old head
        return true;
    }

    /* Lookup for the song in the list and keep track of the previous pointer */
    while (temp != NULL && (strcmp(temp->Song->name, pSongName)))
    {
        prev = temp;
        temp = temp->next;
    }

    /* If song was not present in playlist */
    if (temp == NULL)
        return false;

    /* Detach the song from playlist */
    prev->next = temp->next;
    free(temp->Song->name);
    free(temp->Song);
    free(temp); // Free memory
    return true;
}

/***************************************************************************/ /**
 * @brief           SongList_PrintList
 *                  Print Songs from the Song Playlist.
 * 
 * @param           pSongList_head: Pointer to the Song List.
 * 
 * @return          None
 ******************************************************************************/
void SongList_PrintList(SongList_ts *pSongList_head)
{
    printf("Song PlayList :\n\r");

    while (pSongList_head != NULL)
    {
        printf("Song name: %s, Popularity: %d\n",
               pSongList_head->Song->name,
               pSongList_head->Song->popularity);

        pSongList_head = pSongList_head->next;
    }
    printf("-------------\n\r");
}

/***************************************************************************/ /**
 * @brief           SongList_PlaySong
 *                  Play Song from the Song Playlist and delete it.
 * 
 * @param           ppSongList_head: Pointer to pointer of the Song List.
 *                  rSongName: Pointer to buffer to store Name of the Song.
 * 
 * @return          Pointer to the Song name.
 ******************************************************************************/
char *SongList_PlaySong(SongList_ts **ppSongList_head, char *rSongName)
{

    /* Check Presence of Playlist */
    if (*ppSongList_head == NULL)
        return NULL;

    /* Save pointer to list */
    SongList_ts *curr = *ppSongList_head;
    
    int TotalWeight = 0;
    int NumOfSongs = 0;

    /* Calculate total Weight and number of songs in the list */
    while (curr != NULL)
    {
        TotalWeight += curr->Song->popularity;
        NumOfSongs++;
        curr = curr->next;
    }

    /* Update the pointer back to head */
    curr = *ppSongList_head;
    int rnd = rand() % TotalWeight;

    /* Apply random number to the weighted list */
    while (curr != NULL)
    {
        if (rnd < (curr->Song->popularity))
            break;
        rnd -= curr->Song->popularity;
        curr = curr->next;
    }

    if(curr == NULL)
        return NULL;

    /* Copy the Song name to return buffer */
    strcpy(rSongName, curr->Song->name);

    /* Delete the song from the playlist */
    SongList_DeleteSong(ppSongList_head, curr->Song->name);

    return rSongName;
}

//E.O.F
