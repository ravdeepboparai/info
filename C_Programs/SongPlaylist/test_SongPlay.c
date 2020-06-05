/*******************************************************************************************************************************/ /**
 *
 *  @file       test_SongPlay.h
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

void test1()
{
    printf("TEST 1: Normal Scenerio with C has highest weight\n\r");
    Song_ts ArrOfSongs[] = {{"A", 2}, {"B", 1}, {"C", 5}, {"D", 1},{"E", 2}, {"F", 1}, {"G", 5}, {"H", 1}};

    /* PlayList Generation */
    SongList_ts *pSongList_head = NULL;
    pSongList_head = SongList_Init(ArrOfSongs, sizeof(ArrOfSongs) / sizeof(ArrOfSongs[0]));
    
    /* Print the List */
    SongList_PrintList(pSongList_head);

    /* Play 3 songs from the list */
    printf("Play three songs\n\r");
    char r_SongName[36];
    printf("Song Name: %s\n\r", SongList_PlaySong(&pSongList_head, r_SongName));
    printf("Song Name: %s\n\r", SongList_PlaySong(&pSongList_head, r_SongName));
    printf("Song Name: %s\n\r", SongList_PlaySong(&pSongList_head, r_SongName));
    printf("-------------\n\r");
    
    /* Print the List */
    SongList_PrintList(pSongList_head);

}

void test2()
{
    printf("TEST 2: Adding Song in the Middle\n\r");
    Song_ts ArrOfSongs[] = {{"A", 2},{"B",1},{"C",1}};

    /* PlayList Generation */
    SongList_ts *pSongList_head = NULL;
    pSongList_head = SongList_Init(ArrOfSongs, sizeof(ArrOfSongs) / sizeof(ArrOfSongs[0]));
    
    /* Print the List */
    SongList_PrintList(pSongList_head);

    /* Play 3 songs from the list */
    printf("Play one song\n\r");
    char r_SongName[36];
    printf("Song Name: %s\n\r", SongList_PlaySong(&pSongList_head, r_SongName));

    
    Song_ts *pSong = SongList_AllocateSong("Rav",5);
    SongList_AddSong(&pSongList_head,pSong);
    SongList_PrintList(pSongList_head);

    printf("Play another song\n\r");
    printf("Song Name: %s\n\r", SongList_PlaySong(&pSongList_head, r_SongName));
    printf("-------------\n\r");
    
    /* Print the List */
    SongList_PrintList(pSongList_head);
    SongList_DeleteSong(&pSongList_head, "Rav");
}

void test3()
{
    printf("TEST 3 : Play More then capacity and even delete older (Test for memory)\n\r");
    Song_ts ArrOfSongs[] = {{"A", 2}, {"B", 1}};
    /* PlayList Generation */
    SongList_ts *pSongList_head = NULL;
    pSongList_head = SongList_Init(ArrOfSongs, sizeof(ArrOfSongs) / sizeof(ArrOfSongs[0]));
    
    /* Print the List */
    SongList_PrintList(pSongList_head);

    /* Play 3 songs from the list */
    printf("Play three songs\n\r");
    char r_SongName[36];
    printf("Song Name: %s\n\r", SongList_PlaySong(&pSongList_head, r_SongName));
    printf("Song Name: %s\n\r", SongList_PlaySong(&pSongList_head, r_SongName));
    printf("Song Name: %s\n\r", SongList_PlaySong(&pSongList_head, r_SongName));
    printf("-------------\n\r");
    
    /* Print the List */
    SongList_DeleteSong(&pSongList_head, "A");
    SongList_PrintList(pSongList_head);

}

int main()
{
    printf("==========================================\n\r");
    test1();
    printf("==========================================\n\r");
    test2();
    printf("==========================================\n\r");
    test3();
    printf("==========================================\n\r");
    return 0;
}